// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/gpu/v4l2/test/vp8_decoder.h"

// ChromeOS specific header; does not exist upstream
#if BUILDFLAG(IS_CHROMEOS)
#include <linux/media/vp8-ctrls-upstream.h>
#endif

#include <linux/v4l2-controls.h>

#include "base/memory/ptr_util.h"
#include "base/notreached.h"
#include "media/base/video_types.h"
#include "media/filters/ivf_parser.h"
#include "media/gpu/macros.h"
#include "media/gpu/v4l2/test/v4l2_ioctl_shim.h"
#include "media/parsers/vp8_parser.h"

namespace {
// Section 9.4. Loop filter type and levels syntax in VP8 specs.
// https://datatracker.ietf.org/doc/rfc6386/
struct v4l2_vp8_loop_filter FillV4L2VP8LoopFilterHeader(
    const media::Vp8LoopFilterHeader& vp8_lf_hdr) {
  struct v4l2_vp8_loop_filter v4l2_lf = {};

  v4l2_lf.sharpness_level = vp8_lf_hdr.sharpness_level;
  v4l2_lf.level = vp8_lf_hdr.level;
  if (vp8_lf_hdr.type == 1)
    v4l2_lf.flags |= V4L2_VP8_LF_FILTER_TYPE_SIMPLE;
  if (vp8_lf_hdr.loop_filter_adj_enable)
    v4l2_lf.flags |= V4L2_VP8_LF_ADJ_ENABLE;
  if (vp8_lf_hdr.mode_ref_lf_delta_update)
    v4l2_lf.flags |= V4L2_VP8_LF_DELTA_UPDATE;

  static_assert(
      std::size(decltype(v4l2_lf.ref_frm_delta){}) == media::kNumBlockContexts,
      "Invalid size of ref_frm_delta");

  static_assert(
      std::size(decltype(v4l2_lf.mb_mode_delta){}) == media::kNumBlockContexts,
      "Invalid size of mb_mode_delta");

  media::SafeArrayMemcpy(v4l2_lf.ref_frm_delta, vp8_lf_hdr.ref_frame_delta);
  media::SafeArrayMemcpy(v4l2_lf.mb_mode_delta, vp8_lf_hdr.mb_mode_delta);

  return v4l2_lf;
}

// Section 9.6. Dequantization indices.
struct v4l2_vp8_quantization FillV4L2Vp8QuantizationHeader(
    const media::Vp8QuantizationHeader& vp8_quantization_hdr) {
  struct v4l2_vp8_quantization v4l2_quant = {};

  v4l2_quant.y_ac_qi = base::checked_cast<__u8>(vp8_quantization_hdr.y_ac_qi);
  v4l2_quant.y_dc_delta =
      base::checked_cast<__s8>(vp8_quantization_hdr.y_dc_delta);
  v4l2_quant.y2_dc_delta =
      base::checked_cast<__s8>(vp8_quantization_hdr.y2_dc_delta);
  v4l2_quant.y2_ac_delta =
      base::checked_cast<__s8>(vp8_quantization_hdr.y2_ac_delta);
  v4l2_quant.uv_dc_delta =
      base::checked_cast<__s8>(vp8_quantization_hdr.uv_dc_delta);
  v4l2_quant.uv_ac_delta =
      base::checked_cast<__s8>(vp8_quantization_hdr.uv_ac_delta);

  return v4l2_quant;
}

// Section 9.9.  DCT Coefficient Probability Update
struct v4l2_vp8_entropy FillV4L2VP8EntropyHeader(
    const media::Vp8EntropyHeader& vp8_entropy_hdr) {
  struct v4l2_vp8_entropy v4l2_entr = {};

  static_assert(
      std::size(decltype(v4l2_entr.coeff_probs){}) == media::kNumBlockTypes,
      "Invalid size of coeff_probs");

  static_assert(
      std::size(decltype(v4l2_entr.y_mode_probs){}) == media::kNumYModeProbs,
      "Invalid size of y_mode_probs");

  static_assert(
      std::size(decltype(v4l2_entr.uv_mode_probs){}) == media::kNumUVModeProbs,
      "Invalid size of uv_mode_probs");

  static_assert(
      std::size(decltype(v4l2_entr.mv_probs){}) == media::kNumMVContexts,
      "Invalid size of mv_probs");

  media::SafeArrayMemcpy(v4l2_entr.coeff_probs, vp8_entropy_hdr.coeff_probs);
  media::SafeArrayMemcpy(v4l2_entr.y_mode_probs, vp8_entropy_hdr.y_mode_probs);
  media::SafeArrayMemcpy(v4l2_entr.uv_mode_probs,
                         vp8_entropy_hdr.uv_mode_probs);
  media::SafeArrayMemcpy(v4l2_entr.mv_probs, vp8_entropy_hdr.mv_probs);
  return v4l2_entr;
}

// Section 9.3. Segment-Based Adjustments
struct v4l2_vp8_segment FillV4L2VP8SegmentationHeader(
    const media::Vp8SegmentationHeader& vp8_segmentation_hdr) {
  struct v4l2_vp8_segment v4l2_segment = {};
  if (vp8_segmentation_hdr.segmentation_enabled)
    v4l2_segment.flags |= V4L2_VP8_SEGMENT_FLAG_ENABLED;
  if (vp8_segmentation_hdr.update_mb_segmentation_map)
    v4l2_segment.flags |= V4L2_VP8_SEGMENT_FLAG_UPDATE_MAP;
  if (vp8_segmentation_hdr.update_segment_feature_data)
    v4l2_segment.flags |= V4L2_VP8_SEGMENT_FLAG_UPDATE_FEATURE_DATA;
  if (vp8_segmentation_hdr.segment_feature_mode)
    v4l2_segment.flags |= V4L2_VP8_SEGMENT_FLAG_DELTA_VALUE_MODE;

  static_assert(
      std::size(decltype(v4l2_segment.quant_update){}) == media::kMaxMBSegments,
      "Invalid size of quant_update");

  static_assert(
      std::size(decltype(v4l2_segment.lf_update){}) == media::kMaxMBSegments,
      "Invalid size of lf_update");

  static_assert(std::size(decltype(v4l2_segment.segment_probs){}) ==
                    media::kNumMBFeatureTreeProbs,
                "Invalid size of segment_probs");

  media::SafeArrayMemcpy(v4l2_segment.quant_update,
                         vp8_segmentation_hdr.quantizer_update_value);
  media::SafeArrayMemcpy(v4l2_segment.lf_update,
                         vp8_segmentation_hdr.lf_update_value);
  media::SafeArrayMemcpy(v4l2_segment.segment_probs,
                         vp8_segmentation_hdr.segment_prob);
  v4l2_segment.padding = 0;

  return v4l2_segment;
}

// Sets up per frame parameters |v4l2_frame_headers| needed for VP8 decoding
// with VIDIOC_S_EXT_CTRLS ioctl call.
// Syntax from VP8 specs: https://datatracker.ietf.org/doc/rfc6386/
struct v4l2_ctrl_vp8_frame SetupFrameHeaders(
    const media::Vp8FrameHeader& frame_hdr,
    std::array<scoped_refptr<media::v4l2_test::MmapedBuffer>,
               media::kNumVp8ReferenceBuffers> ref_frames_) {
  struct v4l2_ctrl_vp8_frame v4l2_frame_headers = {};

  v4l2_frame_headers.lf = FillV4L2VP8LoopFilterHeader(frame_hdr.loopfilter_hdr);
  v4l2_frame_headers.quant =
      FillV4L2Vp8QuantizationHeader(frame_hdr.quantization_hdr);

  v4l2_frame_headers.coder_state.range = frame_hdr.bool_dec_range;
  v4l2_frame_headers.coder_state.value = frame_hdr.bool_dec_value;
  v4l2_frame_headers.coder_state.bit_count = frame_hdr.bool_dec_count;

  v4l2_frame_headers.width = frame_hdr.width;
  v4l2_frame_headers.height = frame_hdr.height;

  v4l2_frame_headers.horizontal_scale = frame_hdr.horizontal_scale;
  v4l2_frame_headers.vertical_scale = frame_hdr.vertical_scale;

  v4l2_frame_headers.version = frame_hdr.version;
  v4l2_frame_headers.prob_skip_false = frame_hdr.prob_skip_false;
  v4l2_frame_headers.prob_intra = frame_hdr.prob_intra;
  v4l2_frame_headers.prob_last = frame_hdr.prob_last;
  v4l2_frame_headers.prob_gf = frame_hdr.prob_gf;
  v4l2_frame_headers.num_dct_parts = frame_hdr.num_of_dct_partitions;

  v4l2_frame_headers.first_part_size = frame_hdr.num_of_dct_partitions;
  // https://lwn.net/Articles/793069/: macroblock_bit_offset is renamed to
  // first_part_header_bits
  v4l2_frame_headers.first_part_header_bits = frame_hdr.macroblock_bit_offset;

  if (frame_hdr.frame_type == media::Vp8FrameHeader::KEYFRAME)
    v4l2_frame_headers.flags |= V4L2_VP8_FRAME_FLAG_KEY_FRAME;
  if (frame_hdr.show_frame)
    v4l2_frame_headers.flags |= V4L2_VP8_FRAME_FLAG_SHOW_FRAME;
  if (frame_hdr.mb_no_skip_coeff)
    v4l2_frame_headers.flags |= V4L2_VP8_FRAME_FLAG_MB_NO_SKIP_COEFF;
  if (frame_hdr.sign_bias_golden)
    v4l2_frame_headers.flags |= V4L2_VP8_FRAME_FLAG_SIGN_BIAS_GOLDEN;
  if (frame_hdr.sign_bias_alternate)
    v4l2_frame_headers.flags |= V4L2_VP8_FRAME_FLAG_SIGN_BIAS_ALT;

  static_assert(std::size(decltype(v4l2_frame_headers.dct_part_sizes){}) ==
                    media::kMaxDCTPartitions,
                "Invalid size of dct_part_sizes");

  for (size_t i = 0; i < frame_hdr.num_of_dct_partitions &&
                     i < std::size(v4l2_frame_headers.dct_part_sizes);
       ++i) {
    v4l2_frame_headers.dct_part_sizes[i] =
        static_cast<size_t>(frame_hdr.dct_partition_sizes[i]);
  }

  v4l2_frame_headers.entropy = FillV4L2VP8EntropyHeader(frame_hdr.entropy_hdr);
  v4l2_frame_headers.segment =
      FillV4L2VP8SegmentationHeader(frame_hdr.segmentation_hdr);

  constexpr uint64_t kInvalidSurface = std::numeric_limits<uint32_t>::max();
  // We need to convert a reference frame's frame_number() (in  microseconds)
  // to reference ID (in nanoseconds). Technically, v4l2_timeval_to_ns() is
  // suggested to be used to convert timestamp to nanoseconds, but multiplying
  // the microseconds part of timestamp |tv_usec| by |kTimestampToNanoSecs| to
  // make it nanoseconds is also known to work. This is how it is implemented
  // in v4l2 video decode accelerator tests as well as in gstreamer.
  // https://www.kernel.org/doc/html/v5.10/userspace-api/media/v4l/dev-stateless-decoder.html#buffer-management-while-decoding
  constexpr size_t kTimestampToNanoSecs = 1000;
  v4l2_frame_headers.last_frame_ts =
      ref_frames_[media::VP8_FRAME_LAST]
          ? (ref_frames_[media::VP8_FRAME_LAST]->frame_number() *
             kTimestampToNanoSecs)
          : kInvalidSurface;
  v4l2_frame_headers.golden_frame_ts =
      ref_frames_[media::VP8_FRAME_GOLDEN]
          ? (ref_frames_[media::VP8_FRAME_GOLDEN]->frame_number() *
             kTimestampToNanoSecs)
          : kInvalidSurface;
  v4l2_frame_headers.alt_frame_ts =
      ref_frames_[media::VP8_FRAME_ALTREF]
          ? (ref_frames_[media::VP8_FRAME_ALTREF]->frame_number() *
             kTimestampToNanoSecs)
          : kInvalidSurface;

  return v4l2_frame_headers;
}
}  // namespace
namespace media {
namespace v4l2_test {

// TODO(b/256252128): Find optimal number of CAPTURE buffers
constexpr uint32_t kNumberOfBuffersInCaptureQueue = 10;
constexpr uint32_t kNumberOfBuffersInOutputQueue = 1;

constexpr uint32_t kOutputQueueBufferIndex = 0;

constexpr uint32_t kNumberOfPlanesInOutputQueue = 1;

static_assert(kNumberOfBuffersInCaptureQueue <= 16,
              "Too many CAPTURE buffers are used. The number of CAPTURE "
              "buffers is currently assumed to be no larger than 16.");

static_assert(kNumberOfBuffersInOutputQueue == 1,
              "Too many buffers in OUTPUT queue. It is currently designed to "
              "support only 1 request at a time.");

static_assert(kNumberOfPlanesInOutputQueue == 1,
              "Number of planes is expected to be 1 for OUTPUT queue.");

Vp8Decoder::Vp8Decoder(std::unique_ptr<IvfParser> ivf_parser,
                       std::unique_ptr<V4L2IoctlShim> v4l2_ioctl,
                       std::unique_ptr<V4L2Queue> OUTPUT_queue,
                       std::unique_ptr<V4L2Queue> CAPTURE_queue)
    : VideoDecoder::VideoDecoder(std::move(v4l2_ioctl),
                                 std::move(OUTPUT_queue),
                                 std::move(CAPTURE_queue)),
      ivf_parser_(std::move(ivf_parser)),
      vp8_parser_(std::make_unique<Vp8Parser>()) {
  DCHECK(v4l2_ioctl_);
  DCHECK(v4l2_ioctl_->QueryCtrl(V4L2_CID_STATELESS_VP8_FRAME));
}

Vp8Decoder::~Vp8Decoder() = default;

// static
std::unique_ptr<Vp8Decoder> Vp8Decoder::Create(
    const base::MemoryMappedFile& stream) {
  constexpr uint32_t kDriverCodecFourcc = V4L2_PIX_FMT_VP8_FRAME;

  VLOG(2) << "Attempting to create decoder with codec "
          << media::FourccToString(kDriverCodecFourcc);

  // Set up video parser.
  auto ivf_parser = std::make_unique<media::IvfParser>();
  media::IvfFileHeader file_header{};

  if (!ivf_parser->Initialize(stream.data(), stream.length(), &file_header)) {
    LOG(ERROR) << "Couldn't initialize IVF parser";
    return nullptr;
  }

  const auto driver_codec_fourcc =
      media::v4l2_test::FileFourccToDriverFourcc(file_header.fourcc);

  if (driver_codec_fourcc != kDriverCodecFourcc) {
    VLOG(2) << "File fourcc (" << media::FourccToString(driver_codec_fourcc)
            << ") does not match expected fourcc("
            << media::FourccToString(kDriverCodecFourcc) << ").";
    return nullptr;
  }

  // MM21 is an uncompressed opaque format that is produced by MediaTek
  // video decoders.
  // TODO(b/256174196): Extend decoder format options to support non-MTK devices
  const uint32_t kMm21Fourcc = v4l2_fourcc('M', 'M', '2', '1');

  auto v4l2_ioctl = std::make_unique<V4L2IoctlShim>();

  if (!v4l2_ioctl->VerifyCapabilities(kDriverCodecFourcc, kMm21Fourcc)) {
    LOG(ERROR) << "Device doesn't support the provided FourCCs.";
    return nullptr;
  }

  LOG(INFO) << "Ivf file header: " << file_header.width << " x "
            << file_header.height;

  // TODO(b/256251694): might need to consider using more than 1 file descriptor
  // (fd) & buffer with the output queue for 4K60 requirement.
  // https://buganizer.corp.google.com/issues/202214561#comment31
  auto OUTPUT_queue = std::make_unique<V4L2Queue>(
      V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE, kDriverCodecFourcc,
      gfx::Size(file_header.width, file_header.height), /*num_planes=*/1,
      V4L2_MEMORY_MMAP, /*num_buffers=*/kNumberOfBuffersInOutputQueue);

  // TODO(b/256543928): enable V4L2_MEMORY_DMABUF memory for CAPTURE queue.
  // |num_planes| represents separate memory buffers, not planes for Y, U, V.
  // https://www.kernel.org/doc/html/v5.10/userspace-api/media/v4l/pixfmt-v4l2-mplane.html#c.V4L.v4l2_plane_pix_format
  auto CAPTURE_queue = std::make_unique<V4L2Queue>(
      V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE, kMm21Fourcc,
      gfx::Size(file_header.width, file_header.height), /*num_planes=*/2,
      V4L2_MEMORY_MMAP, /*num_buffers=*/kNumberOfBuffersInCaptureQueue);

  return base::WrapUnique(
      new Vp8Decoder(std::move(ivf_parser), std::move(v4l2_ioctl),
                     std::move(OUTPUT_queue), std::move(CAPTURE_queue)));
}

Vp8Decoder::ParseResult Vp8Decoder::ReadNextFrame(
    Vp8FrameHeader& vp8_frame_header) {
  IvfFrameHeader ivf_frame_header{};
  const uint8_t* ivf_frame_data;
  if (!ivf_parser_->ParseNextFrame(&ivf_frame_header, &ivf_frame_data))
    return kEOStream;

  const bool result = vp8_parser_->ParseFrame(
      ivf_frame_data, ivf_frame_header.frame_size, &vp8_frame_header);

  return result ? Vp8Decoder::kOk : Vp8Decoder::kError;
}

VideoDecoder::Result Vp8Decoder::DecodeNextFrame(std::vector<char>& y_plane,
                                                 std::vector<char>& u_plane,
                                                 std::vector<char>& v_plane,
                                                 gfx::Size& size,
                                                 const int frame_number) {
  Vp8FrameHeader frame_hdr{};

  Vp8Decoder::ParseResult parser_res = ReadNextFrame(frame_hdr);
  switch (parser_res) {
    case Vp8Decoder::kEOStream:
      return VideoDecoder::kEOStream;
    case Vp8Decoder::kError:
      return VideoDecoder::kError;
    case Vp8Decoder::kOk:
      break;
  }

  // Copies the frame data into the V4L2 buffer of OUTPUT |queue|.
  scoped_refptr<MmapedBuffer> OUTPUT_queue_buffer =
      OUTPUT_queue_->GetBuffer(kOutputQueueBufferIndex);
  OUTPUT_queue_buffer->mmaped_planes()[0].CopyIn(frame_hdr.data,
                                                 frame_hdr.frame_size);
  OUTPUT_queue_buffer->set_frame_number(frame_number);

  if (!v4l2_ioctl_->QBuf(OUTPUT_queue_, 0))
    LOG(FATAL) << "VIDIOC_QBUF failed for OUTPUT queue.";

  struct v4l2_ctrl_vp8_frame v4l2_frame_headers =
      SetupFrameHeaders(frame_hdr, ref_frames_);

  // Set controls required by the OUTPUT format to enumerate the CAPTURE formats
  struct v4l2_ext_control ext_ctrl = {.id = V4L2_CID_STATELESS_VP8_FRAME,
                                      .size = sizeof(v4l2_frame_headers),
                                      .ptr = &v4l2_frame_headers};

  struct v4l2_ext_controls ext_ctrls = {.count = 1, .controls = &ext_ctrl};

  if (!v4l2_ioctl_->SetExtCtrls(OUTPUT_queue_, &ext_ctrls))
    LOG(FATAL) << "VIDIOC_S_EXT_CTRLS failed.";

  if (!v4l2_ioctl_->MediaRequestIocQueue(OUTPUT_queue_))
    LOG(FATAL) << "MEDIA_REQUEST_IOC_QUEUE failed.";

  return VideoDecoder::kOk;
}

}  // namespace v4l2_test
}  // namespace media
