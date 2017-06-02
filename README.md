C++ Html Builder
----------------

[![Travis CI Linux Build Status](https://travis-ci.org/SRombauts/HtmlBuilder.svg)](https://travis-ci.org/SRombauts/HtmlBuilder "Travis CI Linux Build Status")
[![AppVeyor Windows Build status](https://ci.appveyor.com/api/projects/status/github/SRombauts/HtmlBuilder?svg=true)](https://ci.appveyor.com/project/SbastienRombauts/HtmlBuilder "AppVeyor Windows Build status")

A simple C++ HTML Generator.

Copyright (c) 2017 Sébastien Rombauts (sebastien.rombauts@gmail.com)

## Building & testing with CMake

### Get Google Test submodule

```bash
git submodule init
git submodule update
```

### Typical generic build (see also "build.bat" or "./build.sh")

```bash
mkdir build
cd build
cmake ..        # cmake .. -G "Visual Studio 10"    # for Visual Studio 2010
cmake --build . # make
ctest .         # make test
```

### Debug build for Unix Makefiles

```bash
mkdir Debug
cd Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug   # -G "Unix Makefiles"
cmake --build . # make
ctest .         # make test
```

### Release build

```bash
mkdir Release
cd Release
cmake .. -DCMAKE_BUILD_TYPE=Release  # -G "Unix Makefiles"
cmake --build . # make
ctest .         # make test
```

### Continuous Integration

This project is continuously tested under Ubuntu Linux with the gcc and clang compilers
using the Travis CI community service with the above CMake building and testing procedure.
It is also tested in the same way under Windows Server 2012 R2 with Visual Studio 2013 compiler
using the AppVeyor countinuous integration service.

Detailed results can be seen online:
 - https://travis-ci.org/SRombauts/HtmlBuilder
 - https://ci.appveyor.com/project/SbastienRombauts/HtmlBuilder

