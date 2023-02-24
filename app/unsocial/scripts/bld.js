import nwbuild from "nw-builder";

nwbuild({
  srcDir: "./out/website/**/*",
  mode: "build",
  version: "latest",
  flavor: "sdk",
  platform: "linux",
  arch: "x64",
  outDir: "./out/desktop",
});