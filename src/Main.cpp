/**
 * @file    Main.cpp
 * @ingroup HtmlBuilder
 * @brief   A simple C++ HTML Generator library.
 *
 * Copyright (c) 2017-2019 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <HTML/HTML.h>

#include <iostream>

/**
 * @brief Entry-point of the application.
 */
int main() {
    HTML::Document document("Welcome to HTML");
	document.addAttribute("lang", "en");
    document << HTML::Header1("Welcome to HTML").id("anchor_link_1");
    document.body() << "Text directly in the body. ";
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

	document << HTML::Link().id("anchor_link_2");

    std::cout << document;
    return 0;
}
