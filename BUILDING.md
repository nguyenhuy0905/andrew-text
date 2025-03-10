# Building

## Required tools

- CMake >= 3.24 (>=3.28 for modules, >= 3.30 for import std).
- A build system (Makefile or Ninja or XCode or Visual Studio... you name it).
- A compiler and a standard library implementation that supports C++20. Module
support not required.
- conan (not required if you install packages on your own).
  - For now, the project doesn't have any dependency save for GTest (if you
  want to build testing) and spdlog.

## Release build

> [!INFO]
> Wait until the project actually has something to show off :)

## Development build

### Extra requirements

- Doxygen and graphviz.
  - In the future, we may change the CMake so that these are not required
  dependencies.

### Nice stuff

> [!NOTE]
> Most of the following only applies to Unix systems.

- ccache/sccache (speed up build time).
- mold (better link time than ld/lld).
- Some kind of flame graph visualizer (help analyze build time and performance).

### Building the thing

> [!NOTE]
> If you build using Visual Studio generator, replace any mention of `unix` with
> `windows`.
>
> Other multi-config generators not tested yet, but the process should be
> similar.
> Maybe we should change `unix` or `windows` to `single` and `multi`.

- If you use conan:

```sh
conan install . -s build_type=Debug -b missing
# if you're on Windows but don't use Visual Studio, you will need to specify
# the generator. Something like, "Ninja" or "Unix Makefiles"
# conan install . -s build_type=Debug -b missing \
#   -c tools.cmake.cmaketoolchain:generator="Ninja"
cmake --preset=dev-conan-unix
# if you instead want to build with modules enabled.
# you probably need to set CC=clang CXX=clang++
# cmake --preset=dev-conan-unix-module
cmake --build build/Debug
# or, module build:
# cmake --build build/Debug-module
```

- If you don't:

```sh
cmake --preset=dev-unix
# if you instead want to build with modules enabled.
# you probably need to set CC=clang CXX=clang++
# cmake --preset=dev-unix-module
cmake --build build/Debug
# or, module build:
# cmake --build build/Debug-module
```

### Running tests

```sh
ctest --test-dir build/Debug
# or, module build:
# ctest --test-dir build/Debug-module
```

### Generate docs

- If you are writing documentation for your code and want a preview of the
stuff that will go onto the GitHub page:

```sh
cmake --build build/Debug --target docs
# the generated docs should be in build/Debug/docs/html/index.html.
# so, if you're on Linux, you can open it in your browser using:
# xdg-open build/Debug/docs/html/index.html
```

### Generate coverage info

- Only works on gcc/clang for now.

```sh
cmake --build build/Debug --target coverage
# the generated info should be in build/Debug/docs/coverage.html.
# so, if you're on Linux, you can open it in your browser using:
# xdg-open build/Debug/docs/coverage.html
```
