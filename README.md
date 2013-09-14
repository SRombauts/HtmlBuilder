cpp-skeleton
------------

![cpp-skeleton build status](https://api.travis-ci.org/SRombauts/cpp-skeleton.png "cpp-skeleton build status")

A simple skeleton for C++ development with CMake and Google Test.

Copyright (c) 2013 Sébastien Rombauts (sebastien.rombauts@gmail.com)

## Building & testing with CMake

### Typical generic build (see also "build.bat" or "./build.sh")

```bash
mkdir build
cd build
cmake ..        # cmake .. -G "Visual Studio 10"    # for Visual Studio 2010
cmake --build . # make
ctest .         # make test
```

### Debug build

```bash
mkdir Debug
cd Debug
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build . # make
ctest .         # make test
```

### Release build

```bash
mkdir Release
cd Release
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . # make
ctest .         # make test
```

### Continuous Integration

This project is continuously tested under Ubuntu Linux with the gcc and clang compilers
using the Travis CI community service with the above CMake building and testing procedure.

Detailed results can be seen online: https://travis-ci.org/SRombauts/cpp-skeleton

