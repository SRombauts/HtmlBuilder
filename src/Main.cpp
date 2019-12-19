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

    // Head
    document.head() << HTML::Meta("utf-8")
        << HTML::Meta("viewport", "width=device-width, initial-scale=1, shrink-to-fit=no");
    document.head() << HTML::Rel("stylesheet", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css")
        .integrity("sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T").crossorigin("anonymous");
    document.head() << HTML::Style(".navbar{margin-bottom:20px;}");

    // Body
    document.body().cls("bg-light");

    // Navbar
    HTML::List navList(false, "navbar-nav mr-auto");
    navList << std::move(HTML::ListItem().cls("nav-item active") << HTML::Link("Home", "#").cls("nav-link"));
    navList << std::move(HTML::ListItem().cls("nav-item") << HTML::Link("Link", "#").cls("nav-link"));
    navList << std::move(HTML::ListItem().cls("nav-item") << HTML::Link("Disabled", "#").cls("nav-link disabled"));
    navList << std::move(HTML::ListItem().cls("nav-item dropdown")
        << HTML::Link("Dropdown", "#").cls("nav-link dropdown-toggle").id("dropdown01").addAttribute("data-toggle", "dropdown").addAttribute("aria-haspopup", "true").addAttribute("aria-expanded", "false")
        << (HTML::Div("dropdown-menu").addAttribute("aria-labelledby", "dropdown01")
            << HTML::Link("Action", "#").cls("dropdown-item")
            << HTML::Link("Another", "#").cls("dropdown-item")
        )
    );
    document << (HTML::Nav("navbar navbar-expand navbar-dark bg-dark") << (HTML::Div("collapse navbar-collapse") << std::move(navList)));

    // Content in a container
    HTML::Div main("container");
    main << HTML::Header1("Welcome to HTML").id("anchor_link_1");
    main << "Text directly in the body.";
    main << HTML::Text("Text directly in the body. ") << HTML::Text("Text directly in the body.") << HTML::Break()
        << HTML::Text("Text directly in the body.");
    main << HTML::Paragraph("This is the way to go for a big text in a multi-line paragraph.");
    main << HTML::Link("Google", "http://google.com").cls("my_style");
    main << (HTML::Paragraph("A paragraph. ").style("font-family:arial")
        << HTML::Text("Text child.") << HTML::Break() << HTML::Text("And more text."));

    main << (HTML::List()
        << (HTML::ListItem("Text item"))
        << (HTML::ListItem() << HTML::Link("Github Link", "http://srombauts.github.io").title("SRombaut's Github home page"))
        << (HTML::ListItem() << (HTML::List()
                << HTML::ListItem("val1")
                << HTML::ListItem("val2"))));

    main << (HTML::Table().cls("table table-hover table-sm")
        << HTML::Caption("Table caption")
        << (HTML::Row() << HTML::ColHeader("A") << HTML::ColHeader("B"))
        << (HTML::Row() << HTML::Col("Cell_11") << HTML::Col("Cell_12"))
        << (HTML::Row() << HTML::Col("Cell_21") << (HTML::Col() << HTML::Link("Wikipedia", "https://www.wikipedia.org/")))
        << (HTML::Row() << HTML::Col("") << HTML::Col("Cell_32")));

    main << HTML::Small("Copyright Sebastien Rombauts @ 2017-2019");

    main << HTML::Link().id("anchor_link_2");

    document << std::move(main);

    // Javascript at the end of the body
    document << HTML::Script("https://code.jquery.com/jquery-3.3.1.slim.min.js")
        .integrity("sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo").crossorigin("anonymous");
    document << HTML::Script("https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js")
        .integrity("sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1").crossorigin("anonymous");
    document << HTML::Script("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js")
        .integrity("sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM").crossorigin("anonymous");

    std::cout << document;
    return 0;
}
