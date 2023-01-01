# Dive

Dive is forked off NW `v0.69.x`.

Major Goals:

- Patch Chromium, Node and V8 to simplify development
- Build in GitHub Actions and release to GitHub Releases
- Set upstreams to stable channels

## References

## Releases

- [Chromium updates](https://chromereleases.googleblog.com/search/label/Desktop%20Update)
- [V8 updates](https://v8.dev/blog)
- [Node updates](https://nodejs.org/en/blog/)


`106-18-10` refers to the different versions of upstream.
 - 106 refers to Chromium's latest 106 release branch
 - 18 refers to Node's latest 18 release branch
 - 10 refers to V8's latest 10 release branch

 This way, it will be easier to support legacy versions like Windows 7.

## Notes

Split patches
```shell
splitdiff -a -d -p 1 -D ./patches/chromium patch/nw_chromium.patch
```
