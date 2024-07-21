# Pixel-Craft

### Building the Project
Once you have cloned this repository, building the project is as simple as running these two commands in its root directory:

#### macOS & Linux
```console
$ make setup
$ make
```

#### Windows
```console
> mingw32-make setup
> mingw32-make
```

The first command will clone in the lastest C++ bindings and targeted version of raylib, copy across any relevant header files into `/includes`, and build a static library file from them, placing it in `/lib`. The second command then compiles, runs and cleans up your project using the source code in `/src/main.cpp`.


### Specifying a Non-Default Compiler
If you want to use a compiler for your platform that isn't the default for your system, you can make use of the system-implicit `CXX` variable like so:

#### macOS & Linux

```console
$ make CXX=g++
```

#### Windows

```console
> mingw32-make CXX=g++
```

## Licence

This project is licenced under an unmodified zlib/libpng licence, which is an OSI-certified, BSD-like licence that allows static linking with closed source software. Check [`LICENCE`](LICENCE) for further details.
