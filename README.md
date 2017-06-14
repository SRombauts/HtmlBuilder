HtmlBuilder
-----------

A simple C++ header-only HTML 5 Generator library, using a Document Object Model.

Copyright (c) 2017 Sébastien Rombauts (sebastien.rombauts@gmail.com)

## Current status

Currently in active development, for use in a new small open source application.

### Missing features

1. [ ] Encoding of HTML Entities
2. [ ] More HTML 5 Elements or common Attributes
3. [ ] Support for HTML Comments
4. [ ] Support for CSS inline style (this is probably easy)

Javascript inline script is currently out of scope.

## Building with CMake

This is a header only library, so just include the include folder and go on.

### Get cpplint submodule

```bash
git submodule init
git submodule update
```

### Typical generic build (see also "build.bat" or "./build.sh")

```bash
mkdir build
cd build
cmake ..        # cmake .. -G "Visual Studio 10"    # for Visual Studio 2010
cmake --build . # make
```

### Debug build for Unix Makefiles

```bash
mkdir Debug
cd Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug   # -G "Unix Makefiles"
cmake --build . # make
```

### Release build

```bash
mkdir Release
cd Release
cmake .. -DCMAKE_BUILD_TYPE=Release  # -G "Unix Makefiles"
cmake --build . # make
```
