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

// Note: to configure indentation & minification, define this at compile time before including HTML headers.
#define HTML_INDENTATION 2 ///< Default indentation can be set to 0 to remove many spaces in generated HTML
#define HTML_ENDLINE "\n" ///< End of lines can be removed to minimize even more the resulting generated HTML

#include <HTML/HTML.h>

#include <iostream>

/**
 * @brief Entry-point of the application.
 */
int main() {
    HTML::Document document("Welcome to HTML");
    document.addAttribute("lang", "en");
    document.head() << HTML::Meta("utf-8")
        << HTML::Meta("viewport", "width=device-width, initial-scale=1, shrink-to-fit=no");
    document.head() << HTML::Rel("stylesheet", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css")
        .integrity("sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T").crossorigin("anonymous");
    document << HTML::Header1("Welcome to HTML").id("anchor_link_1");
    document.body() << "Text directly in the body. ";
    document << HTML::Text("Text directly in the body. ") << HTML::Text("Text directly in the body.") << HTML::Break()
        << HTML::Text("Text directly in the body.");
    document << HTML::Paragraph("This is the way to go for a big text in a multi-line paragraph.");
    document << HTML::Link("Google", "http://google.com").cls("my_style");
    document << (HTML::Paragraph("A paragraph. ").style("font-family:arial")
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

    document << HTML::Script("https://code.jquery.com/jquery-3.3.1.slim.min.js")
        .integrity("sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo").crossorigin("anonymous");
    document << HTML::Script("https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js")
        .integrity("sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1").crossorigin("anonymous");
    document << HTML::Script("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js")
        .integrity("sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM").crossorigin("anonymous");

    std::cout << document;
    return 0;
}
