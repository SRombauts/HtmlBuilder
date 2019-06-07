HtmlBuilder
-----------

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/SRombauts/HtmlBuilder/blob/master/LICENSE.txt)
[![Travis CI Linux Build Status](https://travis-ci.org/SRombauts/HtmlBuilder.svg)](https://travis-ci.org/SRombauts/HtmlBuilder "Travis CI Linux Build Status")
[![AppVeyor Windows Build status](https://ci.appveyor.com/api/projects/status/github/SRombauts/HtmlBuilder?svg=true)](https://ci.appveyor.com/project/SbastienRombauts/HtmlBuilder "AppVeyor Windows Build status")

A simple C++ header-only HTML 5 Generator library, using a Document Object Model (DOM).

Copyright (c) 2017-2019 Sébastien Rombauts (sebastien.rombauts@gmail.com)

## Current status

Deployed in production in a small application.

### Support

- Windows 10 - VS2015 / 2017
- Linux Ubuntu 16.04 Clang 7 / GCC 5.4

### Features

1. DOM Model
2. Example featuring Bootstrap's navigation bar

### Missing features

1. [ ] Encoding of **HTML Entities** *(special chars)*
2. [ ] Support for HTML Comments
3. [ ] Support for CSS inline style (this is probably easy)

Javascript inline script is currently out of scope.

## Example

The following example is provided in src/Main.cpp.

### Source Code

```cpp
    HTML::Document document("Welcome to HTML");
    document.addAttribute("lang", "en");
    document << HTML::Header2("Generated HTML") << HTML::Break() << HTML::Break();
    document.body() << "Which results in the following HTML page (truncated to fit in this README): ";
    document << HTML::Text("Text directly in the body. ") << HTML::Text("Text directly in the body.") << HTML::Break()
        << HTML::Text("Text directly in the body.");
    document << HTML::Paragraph("This is the way to go for a big text in a multi-line paragraph.");
    document << HTML::Link("Google", "http://google.com").cls("my_style");
    document << (HTML::Paragraph("A paragraph. ").addAttribute("style", "font-family:arial")
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

### Generated HTML

Which results in the following HTML page (truncated to fit in this README):

Text directly in the body. Text directly in the body.
<br/>
Text directly in the body.
<p>This is the way to go for a big text in a multi-line paragraph.</p>
<a class="my_style" href="http://google.com">Google</a>
<p style="font-family:arial">A paragraph.       Text child.
    <br/>
    And more text.
</p>
<ul>
    <li>Text item</li>
    <li>
    <a href="http://srombauts.github.io" title="SRombaut's Github home page">Github Link</a>
    </li>
    <li>
    <ul>
        <li>val1</li>
        <li>val2</li>
    </ul>
    </li>
</ul>
<table>
    <tr>
    <th>A</th>
    <th>B</th>
    </tr>
    <tr>
    <td>Cell_11</td>
    <td>Cell_12</td>
    </tr>
    <tr>
    <td>Cell_21</td>
    <td>Cell_22</td>
    </tr>
    <tr>
    <td></td>
    <td>Cell_32</td>
    </tr>
</table>


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
