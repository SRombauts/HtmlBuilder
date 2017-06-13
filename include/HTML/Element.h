/**
 * @file    Element.h
 * @ingroup HtmlBuilder
 * @brief   Definitions of an Element in the HTML Document Object Model, and various specialized Element types.
 *
 * Copyright (c) 2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


/// A simple C++ HTML Generator library.
namespace HTML {

/**
 * @brief Definitions of an Element in the HTML Document Object Model, and various specialized Element types.
 *
 * An Element represents any HTML node in the Document Object Model.
 */
class Element {
public:
    Element(const char* apName, std::string&& aContent) :
        mName(apName), mContent(aContent) {}
    Element(const char* apName, const std::string& aContent) :
        mName(apName), mContent(aContent) {}
    explicit Element(const char* apName, const char* apContent = nullptr) :
        mName(apName), mContent(apContent ? apContent : "") {}

    Element&& addAttribute(const char* apName, const std::string& aValue) {
        mAttributes[apName] = aValue;
        return std::move(*this);
    }
    Element&& addAttribute(const char* apName, const unsigned int aValue) {
        mAttributes[apName] = std::to_string(aValue);
        return std::move(*this);
    }
    Element&& operator<<(Element&& aElement) {
        mChildren.push_back(std::move(aElement));
        return std::move(*this);
    }
    Element&& operator<<(const char* apContent);
    Element&& operator<<(std::string&& aContent);
    Element&& operator<<(const std::string& aContent);

    friend std::ostream& operator<<(std::ostream& aStream, const Element& aElement);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

    Element&& id(const std::string& aValue) {
        return addAttribute("id", aValue);
    }

    Element&& cls(const std::string& aValue) {
        return addAttribute("class", aValue);
    }

    Element&& title(const std::string& aValue) {
        return addAttribute("title", aValue);
    }

    Element&& style(const std::string& aValue) {
        return addAttribute("style", aValue);
    }

protected:
    /// Constructor reserved for the Root Element
    Element();

    std::ostream& toString(std::ostream& aStream, const size_t aIndentation = 0) const {
        toStringOpen(aStream, aIndentation);
        toStringContent(aStream, aIndentation);
        toStringClose(aStream, aIndentation);
        return aStream;
    }

private:
    void toStringOpen(std::ostream& aStream, const size_t aIndentation) const {
        if (!mName.empty()) {
            std::fill_n(std::ostream_iterator<char>(aStream), aIndentation, ' ');
            aStream << '<' << mName;

            for (const auto& attr : mAttributes) {
                aStream << ' ' << attr.first;
                if (!attr.second.empty()) {
                    aStream << "=\"" << attr.second << "\"";
                }
            }

            if (mContent.empty()) {
                if (mbNonVoid) {
                    aStream << ">";
                } else if (!mChildren.empty()) {
                    aStream << ">\n";
                } else {
                    aStream << "/>\n";
                }
            } else {
                aStream << '>';
            }
        }
    }
    void toStringContent(std::ostream& aStream, const size_t aIndentation) const {
        if (!mName.empty()) {
            aStream << mContent;
            for (auto& child : mChildren) {
                child.toString(aStream, aIndentation + 2);
            }
        } else {
            std::fill_n(std::ostream_iterator<char>(aStream), aIndentation, ' ');
            aStream << mContent << '\n';
        }
    }
    void toStringClose(std::ostream& aStream, const size_t aIndentation) const {
        if (!mName.empty()) {
            if (!mChildren.empty()) {
                std::fill_n(std::ostream_iterator<char>(aStream), aIndentation, ' ');
            }
            if (!mContent.empty() || !mChildren.empty() || mbNonVoid) {
                aStream << "</" << mName << ">\n";
            }
        }
    }

protected:
    std::string mName;
    std::string mContent;
    std::map<std::string, std::string> mAttributes;
    std::vector<Element> mChildren;
    bool mbNonVoid = false; // ex. <td></td> (<td/> is not allowed)
};

inline std::ostream& operator<<(std::ostream& aStream, const Element& aElement) {
    return aElement.toString(aStream);
}

class Text : public Element {
public:
    explicit Text(const char* apContent) : Element("", apContent) {}
    explicit Text(std::string&& aContent) : Element("", aContent) {}
    explicit Text(const std::string& aContent) : Element("", aContent) {}
};

inline Element&& Element::operator<<(const char* apContent) {
    return *this << Text(apContent);
}

inline Element&& Element::operator<<(std::string&& aContent) {
    return *this << Text(std::move(aContent));
}

inline Element&& Element::operator<<(const std::string& aContent) {
    return *this << Text(aContent);
}


class Title : public Element {
public:
    explicit Title(const char* apContent) : Element("title", apContent) {}
    explicit Title(const std::string& aContent) : Element("title", aContent) {}
};

class Style : public Element {
public:
    explicit Style(const char* apContent) : Element("style", apContent) {}
    explicit Style(const std::string& aContent) : Element("style", aContent) {}
};

class Script : public Element {
public:
    explicit Script(const char* apSrc, const char* apContent = nullptr) : Element("script", apContent) {
        if (nullptr != apSrc) {
            addAttribute("src", apSrc);
        }
    }
};

class Meta : public Element {
public:
    explicit Meta(const char* apCharset) : Element("meta") {
        addAttribute("charset", apCharset);
    }
    explicit Meta(const char* apName, const char* apContent) : Element("meta") {
        addAttribute("name", apName);
        addAttribute("content", apContent);
    }
};

class Rel : public Element {
public:
    Rel(const char* apRel, const char* apUrl, const char* apType = nullptr) : Element("link") {
        addAttribute("rel", apRel);
        addAttribute("href", apUrl);
        if (nullptr != apType) {
            addAttribute("type", apType);
        }
    }
};

class Base : public Element {
public:
    Base(const std::string& aContent, const std::string& aUrl, const char* apTarget) : Element("base", aContent) {
        addAttribute("href", aUrl);
        if (nullptr != apTarget) {
            addAttribute("target", apTarget);
        }
    }
};

class Head : public Element {
public:
    Head() : Element("head") {}

    Head&& operator<<(Element&& aElement) = delete;
    Head&& operator<<(Title&& aTitle) {
        mChildren.push_back(std::move(aTitle));
        return std::move(*this);
    }
    Head&& operator<<(Style&& aStyle) {
        mChildren.push_back(std::move(aStyle));
        return std::move(*this);
    }
    Head&& operator<<(Script&& aScript) {
        mChildren.push_back(std::move(aScript));
        return std::move(*this);
    }
    Head&& operator<<(Meta&& aMeta) {
        mChildren.push_back(std::move(aMeta));
        return std::move(*this);
    }
    Head&& operator<<(Rel&& aRel) {
        mChildren.push_back(std::move(aRel));
        return std::move(*this);
    }
    Head&& operator<<(Base&& aBase) {
        mChildren.push_back(std::move(aBase));
        return std::move(*this);
    }
};

class Body : public Element {
public:
    Body() : Element("body") {}
};

// Constructor of the Root Element
inline Element::Element() : mName("html"), mChildren{Head(), Body()} {
}


class Break : public Element {
public:
    Break() : Element("br") {}
};

class Col : public Element {
public:
    explicit Col(const char* apContent = nullptr) : Element("td", apContent) {
        mbNonVoid = true;
    }
    explicit Col(std::string&& aContent) : Element("td", aContent) {
        mbNonVoid = true;
    }
    explicit Col(const std::string& aContent) : Element("td", aContent) {
        mbNonVoid = true;
    }

    Col&& rowSpan(const unsigned int aNbRow) {
        if (0 < aNbRow) {
            addAttribute("rowspan", aNbRow);
        }
        return std::move(*this);
    }
    Col&& colSpan(const unsigned int aNbCol) {
        if (0 < aNbCol) {
            addAttribute("colspan", aNbCol);
        }
        return std::move(*this);
    }
};

class Row : public Element {
public:
    Row() : Element("tr") {}

    Row&& operator<<(Element&& aElement) = delete;
    Row&& operator<<(Col&& aCol) {
        mChildren.push_back(std::move(aCol));
        return std::move(*this);
    }
};

class Table : public Element {
public:
    Table() : Element("table") {}

    Element&& operator<<(Element&& aElement) = delete;
    Element&& operator<<(Row&& aRow) {
        mChildren.push_back(std::move(aRow));
        return std::move(*this);
    }
};

class Item : public Element {
public:
    explicit Item(const char* apContent) : Element("li", apContent) {}
    explicit Item(const std::string& aContent) : Element("li", aContent) {}
};
class List : public Element {
public:
    explicit List(const bool abOrdered = false) : Element(abOrdered?"ol":"ul") {}

    Element&& operator<<(Element&& aElement) = delete;
    Element&& operator<<(Item&& aItem) {
        mChildren.push_back(std::move(aItem));
        return std::move(*this);
    }
};


class Form : public Element {
public:
    explicit Form(const char* apAction = nullptr) : Element("form") {
        if (nullptr != apAction) {
            addAttribute("action", apAction);
        }
    }
};

class Input : public Element {
public:
    explicit Input(const char* apType, const char* apName = nullptr,
                   const char* apValue = nullptr, const char* apContent = nullptr) : Element("input", apContent) {
        addAttribute("type", apType);
        if (nullptr != apName) {
            addAttribute("name", apName);
        }
        if (nullptr != apValue) {
            addAttribute("value", apValue);
        }
    }

    Input&& addAttribute(const char* apName, const std::string& aValue) {
        mAttributes[apName] = aValue;
        return std::move(*this);
    }
    Input&& addAttribute(const char* apName, const unsigned int aValue) {
        mAttributes[apName] = std::to_string(aValue);
        return std::move(*this);
    }

    Input&& id(const std::string& aValue) {
        return addAttribute("id", aValue);
    }
    Input&& cls(const std::string& aValue) {
        return addAttribute("class", aValue);
    }
    Input&& title(const std::string& aValue) {
        return addAttribute("title", aValue);
    }
    Input&& style(const std::string& aValue) {
        return addAttribute("style", aValue);
    }

    Input&& size(const unsigned int aSize) {
        return addAttribute("size", aSize);
    }
    Input&& maxlength(const unsigned int aMaxlength) {
        return addAttribute("maxlength", aMaxlength);
    }
    Input&& placeholder(const std::string& aPlaceholder) {
        return addAttribute("placeholder", aPlaceholder);
    }
    Input&& min(const std::string& aMin) {
        return addAttribute("min", aMin);
    }
    Input&& max(const std::string& aMax) { // NOLINT(build/include_what_you_use) false positive
        return addAttribute("max", aMax);
    }

    Input&& checked(const bool abChecked = true) {
        if (abChecked) {
            addAttribute("checked", "");
        }
        return std::move(*this);
    }
    Input&& autocomplete() {
        return addAttribute("autocomplete", "");
    }
    Input&& autofocus() {
        return addAttribute("autofocus", "");
    }
    Input&& disabled() {
        return addAttribute("disabled", "");
    }
    Input&& readonly() {
        return addAttribute("readonly", "");
    }
    Input&& required() {
        return addAttribute("required", "");
    }
};

class InputRadio : public Input {
public:
    explicit InputRadio(const char* apName, const char* apValue = nullptr, const char* apContent = nullptr) :
        Input("radio", apName, apValue, apContent) {
    }
};

class InputCheckbox : public Input {
public:
    explicit InputCheckbox(const char* apName, const char* apValue = nullptr, const char* apContent = nullptr) :
        Input("checkbox", apName, apValue, apContent) {
    }
};

class InputText : public Input {
public:
    explicit InputText(const char* apName, const char* apValue = nullptr) :
        Input("text", apName, apValue) {
    }
};

class InputNumber : public Input {
public:
    explicit InputNumber(const char* apName, const char* apValue = nullptr) :
        Input("number", apName, apValue) {
    }
};

class InputRange : public Input {
public:
    explicit InputRange(const char* apName, const char* apValue = nullptr) :
        Input("range", apName, apValue) {
    }
};

class InputDate : public Input {
public:
    explicit InputDate(const char* apName, const char* apValue = nullptr) :
        Input("date", apName, apValue) {
    }
};

class InputTime : public Input {
public:
    explicit InputTime(const char* apName, const char* apValue = nullptr) :
        Input("time", apName, apValue) {
    }
};

class InputEmail : public Input {
public:
    explicit InputEmail(const char* apName, const char* apValue = nullptr) :
        Input("email", apName, apValue) {
    }
};

class InputUrl : public Input {
public:
    explicit InputUrl(const char* apName, const char* apValue = nullptr) :
        Input("url", apName, apValue) {
    }
};

class InputPassword : public Input {
public:
    explicit InputPassword(const char* apName) :
        Input("password", apName) {
    }
};

class InputSubmit : public Input {
public:
    explicit InputSubmit(const char* apValue = nullptr, const char* apName = nullptr) :
        Input("submit", apName, apValue) {
    }
};

class InputReset : public Input {
public:
    explicit InputReset(const char* apValue = nullptr) :
        Input("reset", nullptr, apValue) {
    }
};

class Header1 : public Element {
public:
    explicit Header1(const std::string& aContent) : Element("h1", aContent) {}
};

class Header2 : public Element {
public:
    explicit Header2(const std::string& aContent) : Element("h2", aContent) {}
};

class Header3 : public Element {
public:
    explicit Header3(const std::string& aContent) : Element("h3", aContent) {}
};

class Bold : public Element {
public:
    explicit Bold(const std::string& aContent) : Element("b", aContent) {}
};

class Italic : public Element {
public:
    explicit Italic(const std::string& aContent) : Element("i", aContent) {}
};

class Strong : public Element {
public:
    explicit Strong(const std::string& aContent) : Element("strong", aContent) {}
};

class Mark : public Element {
public:
    explicit Mark(const std::string& aContent) : Element("mark", aContent) {}
};

class Paragraph : public Element {
public:
    explicit Paragraph(const std::string& aContent) : Element("p", aContent) {}
};

class Div : public Element {
public:
    explicit Div(const std::string& aContent) : Element("div", aContent) {}
};

class Span : public Element {
public:
    explicit Span(const std::string& aContent) : Element("span", aContent) {}
};

class Header : public Element {
public:
    Header() : Element("header") {}
};

class Footer : public Element {
public:
    Footer() : Element("footer") {}
};

class Section : public Element {
public:
    Section() : Element("section") {}
};

class Article : public Element {
public:
    Article() : Element("article") {}
};

class Nav : public Element {
public:
    Nav() : Element("nav") {}
};

class Aside : public Element {
public:
    Aside() : Element("aside") {}
};

class Main : public Element {
public:
    Main() : Element("main") {}
};

class Figure : public Element {
public:
    Figure() : Element("figure") {}
};

class FigCaption : public Element {
public:
    explicit FigCaption(const std::string& aContent) : Element("figcaption", aContent) {}
};
class Details : public Element {
public:
    Details() : Element("details") {}
};

class Summary : public Element {
public:
    explicit Summary(const std::string& aContent) : Element("summary", aContent) {}
};

class Link : public Element {
public:
    Link(const std::string& aContent, const std::string& aUrl) : Element("a", aContent) {
        addAttribute("href", aUrl);
    }
};

class Image : public Element {
public:
    Image(const std::string& aSrc, const std::string& aAlt, unsigned int aWidth = 0, unsigned int aHeight = 0) :
        Element("img") {
        addAttribute("src", aSrc);
        addAttribute("alt", aAlt);
        addAttribute("width", aWidth);
        addAttribute("height", aHeight);
    }
};

} // namespace HTML
