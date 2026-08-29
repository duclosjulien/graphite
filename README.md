# Graphite

[![Verify](https://github.com/duclosjulien/graphite/actions/workflows/verify.yml/badge.svg?branch=main)](https://github.com/duclosjulien/graphite/actions/workflows/verify.yml)

Graphite is a small terminal function grapher written in C++.

It lets you create and display different types of curves directly in the terminal, then modify their parameters interactively.

![Graphite screenshot](assets/graphite.png)

## Features

* Plot multiple curves at the same time
* Supports sine, cosine, tangent, polynomial, exponential, and logarithmic functions
* Modify curve parameters interactively
* Built with C++20 and CMake
* Tests with Catch2

## Supported platforms

Graphite supports macOS and Linux terminals with POSIX `termios` support.

Windows is not currently supported.

## Build

```bash
git clone https://github.com/duclosjulien/graphite.git
cd graphite

cmake -S . -B build
cmake --build build
```

Then run:

```bash
./build/graphite
```

## Tests

Configure, build, and run the tests with:

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Requirements

* C++20 compatible compiler
* CMake 3.19+
- macOS or Linux
- ANSI-compatible terminal
- Minimum terminal size: 118 × 29

## Terminal

Graphite supports terminals that are at least 118 columns by 29 rows**.

The layout adapts to the terminal size when the app starts. If you resize the terminal while Graphite is running, restart the app to update the layout.

## Development

Graphite is tested with Catch2 and CTest. GitHub Actions verifies warning-clean builds with GCC and Clang and runs AddressSanitizer and UndefinedBehaviorSanitizer checks.

## License

Graphite is available under the [MIT License](LICENSE).
