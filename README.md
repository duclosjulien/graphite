# Graphite

Graphite is a small terminal function grapher written in C++.

It lets you create and display different types of curves directly in the terminal, then modify their parameters interactively.

![Graphite screenshot](assets/graphite.png)

## Features

* Plot multiple curves at the same time
* Supports sine, cosine, tangent, polynomial, exponential, and logarithmic functions
* Modify curve parameters interactively
* Built with C++20 and CMake
* Tests with Catch2

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

## Requirements

* C++20 compatible compiler
* CMake 3.19+
* macOS or Linux
* ANSI-compatible terminal

## Development

Graphite is tested with Catch2 and CTest. GitHub Actions verifies warning-clean builds with GCC and Clang and runs AddressSanitizer and UndefinedBehaviorSanitizer checks.


