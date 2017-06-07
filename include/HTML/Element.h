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
    /// Constructor of the Root Element
    Element() : mName("html"), mChildren{Element("head"), Element("body")} {
    }

    // TODO(SRombauts) indentation?
    std::ostream& toString(std::ostream& aStream) const {
        toStringOpen(aStream);
        toStringContent(aStream);
        toStringClose(aStream);
        return aStream;
    }

private:
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

protected:
    std::string mName;
    std::string mContent;
    std::map<std::string, std::string> mAttributes;
    std::vector<Element> mChildren;
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
    addChild(Text(apContent));
    return std::move(*this);
}

inline Element&& Element::operator<<(std::string&& aContent) {
    addChild(Text(aContent));
    return std::move(*this);
}

inline Element&& Element::operator<<(const std::string& aContent) {
    addChild(Text(aContent.c_str()));
    return std::move(*this);
}


class Break : public Element {
public:
    Break() : Element("br") {}
};

class Col : public Element {
public:
    explicit Col(const char* apContent = nullptr) : Element("td", apContent) {}
    explicit Col(std::string&& aContent) : Element("td", aContent) {}
    explicit Col(const std::string& aContent) : Element("td", aContent) {}

    Col&& rowSpan(const unsigned int aNbRow) {
        if (0 < aNbRow) {
            addAttribute("rowspan", std::to_string(aNbRow));
        }
        return std::move(*this);
    }
    Col&& colSpan(const unsigned int aNbCol) {
        if (0 < aNbCol) {
            addAttribute("colspan", std::to_string(aNbCol));
        }
        return std::move(*this);
    }
};

class Row : public Element {
public:
    Row() : Element("tr") {}

    Row&& addChild(Element&& aElement) = delete;
    Row&& operator<<(Element&& aElement) = delete;

    Row&& addChild(Col&& aCol) {
        mChildren.push_back(std::move(aCol));
        return std::move(*this);
    }
    Row&& operator<<(Col&& aCol) {
        addChild(std::move(aCol));
        return std::move(*this);
    }
};

class Table : public Element {
public:
    Table() : Element("table") {}

    Element&& addChild(Element&& aElement) = delete;
    Element&& operator<<(Element&& aElement) = delete;

    Element&& addChild(Row&& aRow) {
        mChildren.push_back(std::move(aRow));
        return std::move(*this);
    }
    Element&& operator<<(Row&& aRow) {
        addChild(std::move(aRow));
        return std::move(*this);
    }
};

class Item : public Element {
public:
   explicit Item(const std::string& aContent) : Element("li", aContent) {}
};
class List : public Element {
public:
   List(const bool abOrdered = false) : Element(abOrdered?"ol":"ul") {}

   Element&& addChild(Element&& aElement) = delete;
   Element&& operator<<(Element&& aElement) = delete;

   Element&& addChild(Item&& aItem) {
       mChildren.push_back(std::move(aItem));
       return std::move(*this);
   }
   Element&& operator<<(Item&& aItem) {
       addChild(std::move(aItem));
       return std::move(*this);
   }
};


class Style : public Element {
public:
    explicit Style(const char* apContent) : Element("style", apContent) {}
    explicit Style(const std::string& aContent) : Element("style", aContent) {}
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
