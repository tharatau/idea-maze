## 7958

This is expected behaviour from a Chromium standpoint. The [`FileList API`](https://developer.mozilla.org/en-US/docs/Web/API/FileList) is read only and it does not have the `append()` anymore.  See https://stackoverflow.com/questions/74630989/why-use-domstringlist-rather-than-an-array/74641156#74641156 for more context.

Stack Trace:
```shell
[7300:7320:0119/131207.720287:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/user/1001/bus: Permission denied
[7300:7320:0119/131207.725951:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/user/1001/bus: Permission denied
[7300:7320:0119/131207.764419:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/user/1001/bus: Permission denied
[7300:7320:0119/131207.764764:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/user/1001/bus: Permission denied
[7300:7334:0119/131207.859984:ERROR:object_proxy.cc(623)] Failed to call method: org.freedesktop.DBus.Properties.Get: object_path= /org/freedesktop/UPower: org.freedesktop.DBus.Error.ServiceUnknown: The name org.freedesktop.UPower was not provided by any .service files
[7300:7334:0119/131207.861687:ERROR:object_proxy.cc(623)] Failed to call method: org.freedesktop.UPower.GetDisplayDevice: object_path= /org/freedesktop/UPower: org.freedesktop.DBus.Error.ServiceUnknown: The name org.freedesktop.UPower was not provided by any .service files
[7300:7334:0119/131207.863416:ERROR:object_proxy.cc(623)] Failed to call method: org.freedesktop.UPower.EnumerateDevices: object_path= /org/freedesktop/UPower: org.freedesktop.DBus.Error.ServiceUnknown: The name org.freedesktop.UPower was not provided by any .service files
WARNING: lavapipe is not a conformant vulkan implementation, testing use only.
libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)
[7327:7327:0119/131208.133609:ERROR:viz_main_impl.cc(186)] Exiting GPU process due to errors during initialization
WARNING: lavapipe is not a conformant vulkan implementation, testing use only.
libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)
[7409:7409:0119/131208.392666:ERROR:viz_main_impl.cc(186)] Exiting GPU process due to errors during initialization
libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)
[7434:7434:0119/131208.632248:ERROR:gpu_memory_buffer_support_x11.cc(49)] dri3 extension not supported.
[0119/131208.979711:ERROR:file_io_posix.cc(144)] open /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq: No such file or directory (2)
[0119/131208.979880:ERROR:file_io_posix.cc(144)] open /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq: No such file or directory (2)
Received signal 11 SEGV_MAPERR 0000000023fd
#0 0x7f7e4e8c7093 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x626c092)
#1 0x7f7e4e969f21 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x630ef20)
#2 0x7f7e48437520 (/usr/lib/x86_64-linux-gnu/libc.so.6+0x4251f)
#3 0x7f7e52af175b (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0xa49675a)
#4 0x7f7e4bc2293c (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x35c793b)
#5 0x7f7e4bc21cdd (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x35c6cdc)
#6 0x7f7ddff17978 <unknown>
#7 0x7f7ddfe8b86c <unknown>
#8 0x7f7ddfec808f <unknown>
#9 0x7f7ddfe89fdc <unknown>
#10 0x7f7ddfe89d07 <unknown>
#11 0x7f7e4bcf7936 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x369c935)
#12 0x7f7e4bcf84ee (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x369d4ed)
#13 0x7f7e4bcf86d7 v8::internal::Execution::TryCall()
#14 0x7f7e4c0429fd (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x39e79fc)
#15 0x7f7e4c042091 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x39e7090)
#16 0x7f7e4c041a76 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x39e6a75)
#17 0x7f7e4bbc581c v8::Module::Evaluate()
#18 0x7f7e518a5590 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x924a58f)
#19 0x7f7e52453984 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x9df8983)
#20 0x7f7e52454c5e (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x9df9c5d)
#21 0x7f7e52454d0d (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x9df9d0c)
#22 0x7f7e524549b3 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x9df99b2)
#23 0x7f7e5245478f (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x9df978e)
#24 0x7f7e52446053 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x9deb052)
#25 0x7f7e5290e3e7 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0xa2b33e6)
#26 0x7f7e5290fbe5 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0xa2b4be4)
#27 0x7f7e5290e603 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0xa2b3602)
#28 0x7f7e5290e91b (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0xa2b391a)
#29 0x7f7e4e923e01 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x62c8e00)
#30 0x7f7e4e939d17 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x62ded16)
#31 0x7f7e4e9395ff (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x62de5fe)
#32 0x7f7e4e93a495 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x62df494)
#33 0x7f7e4e8e3b66 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x6288b65)
#34 0x7f7e4e93a81b (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x62df81a)
#35 0x7f7e4e9052fd (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x62aa2fc)
#36 0x7f7e53fc5f60 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0xb96af5f)
#37 0x7f7e4e414a8b (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x5db9a8a)
#38 0x7f7e4e41592a (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x5dba929)
#39 0x7f7e4e412854 (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x5db7853)
#40 0x7f7e4e41318a (/home/ayushmxn/tharatau/idea-maze/repro/nw/node_modules/nw/nwjs/lib/libnw.so+0x5db8189)
#41 0x7f7e4a8971bb ChromeMain
#42 0x7f7e4841ed90 (/usr/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)
  r8: ffffffffffff3280  r9: 000000000000008b r10: 00000000000076b1 r11: 00000487010ade71
 r12: 00007f7e545b5898 r13: 00005640788dbd30 r14: 000004a900102a60 r15: 00007f7e546d3ea0
  di: 00000000000023f1  si: 000004a900102a60  bp: 00007ffc3a3fcfe0  bx: 00000000000023e1
  dx: 00000487010ae401  ax: 0000048700313241  cx: 0000000000000001  sp: 00007ffc3a3fcfd0
  ip: 00007f7e5188e561 efl: 0000000000010202 cgf: 002b000000000033 erf: 0000000000000004
 trp: 000000000000000e msk: 0000000000000000 cr2: 00000000000023fd
[end of stack trace]
```