# auto

A build system using Bash to generate Ninja files.

## Installation

Download `auto.sh`:
```shell
wget https://github.com/tharatau/idea-maze/blob/main/auto/auto.sh -O $HOME/auto.sh
```

Add to `PATH`:
```shell
export PATH="${PATH}:${HOME}/auto.sh"
```

## Usage

Install platform specific packages.

> Currently only `apt` package manager is supported.

Auto update `auto.sh`.

```shell
auto meta
```

```shell
auto pkg
```

Download dependencies.

> Currently only GitHub repos are supported.

```shell
auto dep
```

Run hooks to build dependencies.

```shell
auto hook
```

Run all the above commands in order.

```shell
auto all
```

`auto.sh` tries to do as little work as possible by caching and reusing . You can add a `--force` flag to override that.

> Currently this flag is only applied to `dep`.

## Contributing

Contributions welcome! I made this for my specific use case so a lot of features may be missing.

## License

MIT
