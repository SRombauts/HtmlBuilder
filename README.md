HtmlBuilder
-----------

A simple C++ header-only HTML 5 Generator library, using a Document Object Model (DOM).

Copyright (c) 2017-2019 Sébastien Rombauts (sebastien.rombauts@gmail.com)

## Current status

Deployed in production in a small application.

### Missing features

1. [ ] Encoding of **HTML Entities** *(special chars)*
2. [ ] Support for HTML Comments
3. [ ] Support for CSS inline style (this is probably easy)

Javascript inline script is currently out of scope.

## Example

The following example is provided in src/Main.cpp.

```
    HTML::Document document("Welcome to HTML");
	document.addAttribute("lang", "en");
    document << HTML::Header1("Welcome to HTML");
    document.body() << "Text directly in the body. ";
    document << HTML::Text("Text directly in the body. ") << HTML::Text("Text directly in the body.") << HTML::Break()
        << HTML::Text("Text directly in the body.");
    document << HTML::Paragraph("This is the way to go for a big text in a multiline paragraph.");
    document << HTML::Link("Google", "http://google.com").cls("my_style");
    document << (HTML::Paragraph("A paragraphe. ").addAttribute("style", "font-family:arial")
        << HTML::Text("Text child.") << HTML::Break() << HTML::Text("And more text."));

    document << (HTML::List()
        << (HTML::ListItem("Text item"))
        << (HTML::ListItem() << HTML::Link("Github Link", "http://srombauts.github.io").title("SRombaut's Github home page"))
        << (HTML::ListItem() << (HTML::List()
                << HTML::ListItem("val1")
                << HTML::ListItem("val2"))));

    document << (HTML::Table()
        << (HTML::Row() << HTML::ColHeader("A") << HTML::ColHeader("B"))
        << (HTML::Row() << HTML::Col("Cell_11") << HTML::Col("Cell_12"))
        << (HTML::Row() << HTML::Col("Cell_21") << HTML::Col("Cell_22"))
        << (HTML::Row() << HTML::Col("") << HTML::Col("Cell_32")));
```

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
