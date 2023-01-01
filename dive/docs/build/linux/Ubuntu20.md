# NW

NW.js SDK for local development

> Last tested on v0.70.x

## Initial Setup

Create a new user

> `depot_tools` does not work on root

```shell
sudo adduser username
```

Login using that user

```shell
sudo login
```

Install `depot_tools`

```shell
cd $HOME
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
```

Add `depot_tools` to your PATH:

```shell
export PATH=$PATH:$PWD/depot_tools
```

Create a folder and change directory into the folder to store the NW.js codebase

```shell
mkdir $HOME/chromium && cd $HOME/chromium
```

Configure Chromium for NW.js codebase

```shell
gclient config --name=src https://github.com/nwjs/chromium.src.git
```

Pull Chromium for NW.js codebase. If you’re running Linux for the first time then run this command:

```shell
gclient sync --with_branch_heads --nohooks --no-history
```

After completion, run the script
```shell
./build/install-build-deps.sh
```

Build `debian_bullseye_amd64-sysroot` since it doesn't get built with the above command:
```shell
./build/linux/sysroot_scripts/install-sysroot.py --arch=amd64
```

Create a [`LASTCHANGE`](https://magpcss.org/ceforum/viewtopic.php?t=16292#p39907) file:
```shell
cd /build/util && python lastchange.py -o LASTCHANGE
```

> This command usually doesn't work if the depth=1 or a similar small amount. Here's a quick fix:

```shell
vim /build/util/LASTCHANGE
```

```patch
+ LASTCHANGE=0000000000000000000000000000000000000000-0000000000000000000000000000000000000000
+ LASTCHANGE_YEAR=1970
```

Run `gclient sync`: 
```shell
gclient sync
```

You may have to add your newly created user to the sudoers list.

```shell
sudo usermod -a -G sudo <user_name>
```

For example if my username is `localghost`, then the command is

```shell
sudo usermod -a -G sudo localghost
```

Clone NW.js, Node for NW.js and V8 for NW.js

```shell
git clone https://github.com/nwjs/nw.js.git /content/nw --depth=1
git clone https://github.com/nwjs/node.git /third_party/node-nw --depth=1
git clone https://github.com/nwjs/v8.git v8 --depth=1
```

# Building NW.js

Generate ninja build files

```shell
gn gen out/nw '--args=is_debug=true target_os="linux" target_cpu="x64" is_clang=true use_lld=false is_component_build=true'
```

Build NW.js

```shell
ninja -C out/nw nwjs
```

You may run into a [duplicate symbol error](https://gist.github.com/ayushmxn/a9996f80325512af123015a5e49f8562#file-nw69_chromium_build_error). After applying the [patch](https://gist.github.com/ayushmxn/a9996f80325512af123015a5e49f8562#file-nw69_chromium_patch-patch) for the above error, run the build NW.js command again.

# Building Node

Before generating Node build files, set some environment variables:

```shell
export GYP_CHROMIUM_NO_ACTION=0
export GYP_DEFINES="target_arch=x64 building_nw=1 clang=1 nwjs_sdk=1 disable_nacl=0 buildtype=Official"
export GYP_GENERATORS=ninja
export GYP_GENERATOR_FLAGS=output_dir=out
# export C_INCLUDE_PATH=$PWD/build/linux/debian_bullseye_amd64-sysroot/usr/include/x86_64-linux-gnu:$PWD/build/linux/debian_bullseye_amd64-sysroot/usr/include
# export CPLUS_INCLUDE_PATH=$PWD/build/linux/debian_bullseye_amd64-sysroot/usr/include/x86_64-linux-gnu:$PWD/build/linux/debian_bullseye_amd64-sysroot/usr/include
```

Generate Node ninja build files

```shell
python3 ./third_party/node-nw/tools/gyp/gyp_main.py -I ./third_party/node-nw/common.gypi -D build_type=Release ./third_party/node-nw/node.gyp
```

Build Node

```shell
ninja -C ./out/Release node
```

Copy Node into NW.js folder

```shell
ninja -C out/nw copy_node
```

> TBD...

DONEZO.