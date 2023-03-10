# NW

- [x] Diff NW against Chromium, Node and V8 to understand how NW changes upstream behaviour
- [ ] Release (Linux/MacOS/Windows/Android/iOS)-(AMD/ARM)-(32/64) versions

## Updating patches

1. Verify that the new versions are in sync with the [`manifest`](https://nwjs.io/version).
1. Open a PR and update the versions (`*_VER` variables) in `scripts/patch`. You can find the V8 version in `include/v8-version.h`.
1. The patches will be updated after the PR is merged!

