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
    Element&& addChild(Element&& aElement) {
        mChildren.push_back(std::move(aElement));
        return std::move(*this);
    }
    Element&& operator<<(Element&& aElement) {
        addChild(std::move(aElement));
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

private:
    // TODO(SRombauts) indentation?
    std::ostream& toString(std::ostream& aStream) const {
        toStringOpen(aStream);
        toStringContent(aStream);
        toStringClose(aStream);
        return aStream;
    }

    void toStringOpen(std::ostream& aStream) const {
        if (!mName.empty()) {
            aStream << '<' << mName;
        }
        for (const auto& attr : mAttributes) {
            aStream << ' ' << attr.first << "=\"" << attr.second << "\"";
        }
        if (!mName.empty()) {
            if (mContent.empty()) {
                if (mChildren.empty()) {
                    aStream << "/>\n";
                } else {
                    aStream << ">\n";
                }
            } else {
                aStream << '>';
            }
        }
    }
    void toStringContent(std::ostream& aStream) const {
        aStream << mContent;
        for (auto& child : mChildren) {
            aStream << child;
        }
    }
    void toStringClose(std::ostream& aStream) const {
        if ((!mContent.empty() || !mChildren.empty()) && !mName.empty()) {
            aStream << "</" << mName << ">\n";
        }
    }

private:
    std::string mName;
    std::string mContent;
    std::map<std::string, std::string> mAttributes;
    std::vector<Element> mChildren;
};

std::ostream& operator<<(std::ostream& aStream, const Element& aElement) {
    return aElement.toString(aStream);
}

class Text : public Element {
public:
    explicit Text(const char* apContent) : Element("", apContent) {}
    explicit Text(std::string&& aContent) : Element("", aContent) {}
    explicit Text(const std::string& aContent) : Element("", aContent) {}
};

Element&& Element::operator<<(const char* apContent) {
    addChild(Text(apContent));
    return std::move(*this);
}

Element&& Element::operator<<(std::string&& aContent) {
    addChild(Text(aContent));
    return std::move(*this);
}

Element&& Element::operator<<(const std::string& aContent) {
    addChild(Text(aContent.c_str()));
    return std::move(*this);
}


class Head : public Element {
public:
    Head() : Element("head") {}
};

class Body : public Element {
public:
    Body() : Element("body") {}
};

class Break : public Element {
public:
    Break() : Element("br") {}
};

class Table : public Element {
public:
    Table() : Element("table") {}
};

class Row : public Element {
public:
    Row() : Element("tr") {}
};

class ColHeader : public Element {
public:
    ColHeader() : Element("th") {}
};

class Col : public Element {
public:
    explicit Col(const char* apContent = nullptr) : Element("td", apContent) {}
    explicit Col(std::string&& aContent) : Element("td", aContent) {}
    explicit Col(const std::string& aContent) : Element("td", aContent) {}

    Element&& rowSpan(const unsigned int aNbRow) {
        if (0 < aNbRow) {
            addAttribute("rowspan", std::to_string(aNbRow));
        }
        return std::move(*this);
    }
    Element&& colSpan(const unsigned int aNbCol) {
        if (0 < aNbCol) {
            addAttribute("colspan", std::to_string(aNbCol));
        }
        return std::move(*this);
    }
};

class Title : public Element {
public:
    explicit Title(const char* apContent) : Element("title", apContent) {}
    explicit Title(const std::string& aContent) : Element("title", aContent) {}
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

class Paragraph : public Element {
public:
    explicit Paragraph(const std::string& aContent) : Element("p", aContent) {}
};

class Link : public Element {
public:
    Link(const std::string& aContent, const std::string& aUrl) : Element("a", aContent) {
        addAttribute("href", aUrl);
    }
};

} // namespace HTML
