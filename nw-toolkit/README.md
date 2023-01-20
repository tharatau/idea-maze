# NW Toolkit

- [x] Diff NW with Chromium, Node and V8 to understand how upstream behaviour is changed
- [ ] Simplify development environment using bootstrap script
- [ ] Release (Linux/MacOS/Windows)-(AMD/ARM)-(32/64) versions
- [ ] Experiment with Android and iOS support

## Updating patches

1. Verify that the new versions are in sync with the [`manifest`](https://nwjs.io/version).
1. Open a PR and update the versions in `scripts/patch`. You can find the V8 version in `include/v8-version.h`.
1. The patches will be updated once the PR is merged!
