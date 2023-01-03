import esbuild from "esbuild";

esbuild.build({
  entryPoints: ["./src.css"],
  bundle: true,
  minify: true,
  platform: "node",
  loader: {
    ".eot": "dataurl",
  },
  outfile: "./out.css",
});
