/**
 * @file    Main.cpp
 * @ingroup HtmlBuilder
 * @brief   A simple C++ HTML Generator library.
 *
 * Copyright (c) 2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
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
    HTML::Document document;
    document.head() << HTML::Title("Welcome to HTML");
    document << HTML::Header1("Welcome to HTML");
    document.body() << "Text direclty in the body. ";
    document << HTML::Text("Text direclty in the body. ") << HTML::Text("Text direclty in the body.") << HTML::Break()
        << HTML::Text("Text direclty in the body.");
    document << HTML::Paragraph("This is the way to go for a big text in a multiline paragraph.");
    document.body().addChild(HTML::Paragraph("Another paragraphe."))
        .addChild(HTML::Break())
        .addChild(HTML::Paragraph("Another paragraphe."));
// TODO(SRombauts) testing nesting
//    document.body().addChild(HTML::Paragraph("Another paragraphe.").addChild(HTML::Link("Google", "http://google.com")));
    document << HTML::Paragraph("Another paragraph.") << HTML::Break();
    document << HTML::Link("Google", "http://google.com");
    std::cout << document;
    return 0;
}
