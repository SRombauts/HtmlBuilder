/**
 * @file    Main.cpp
 * @ingroup HtmlBuilder
 * @brief   A simple HTML Generator C++ library.
 *
 * Copyright (c) 2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace HTML {

class Node {
public:
             Node(const char* apName, const std::string& aContent) : mName(apName), mContent(aContent) {}
    explicit Node(const char* apName, const char* apContent = nullptr) : mName(apName), mContent(apContent?apContent:"") {}

    void addAttribute(const char* apName, const std::string& aValue) {
        mAttributes[apName] = aValue;
    }
    void addChild(Node&& aNode) {
        mChildren.push_back(std::move(aNode));
    }
    Node& operator<<(Node&& aNode) {
        addChild(std::move(aNode));
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& aStream, const Node& aNode);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

private:
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
        if (mContent.empty() && mChildren.empty()) {
            if (!mName.empty()) {
                aStream << "/>\n";
            }
        }
        else {
            if (mContent.empty()) {
                aStream << ">\n";
            }
            else {
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
    std::vector<Node> mChildren;
};

std::ostream& operator<<(std::ostream& aStream, const Node& aNode) {
    return aNode.toString(aStream);
}


class Head : public Node {
public:
    Head() : Node("head") {}
};

class Body : public Node {
public:
    Body() : Node("body") {}
};

class Title : public Node {
public:
    Title(const std::string& aContent) : Node("title", aContent) {}
};

class Header1 : public Node {
public:
    Header1(const std::string& aContent) : Node("h1", aContent) {}
};

class Header2 : public Node {
public:
    Header2(const std::string& aContent) : Node("h2", aContent) {}
};

class Header3 : public Node {
public:
    Header3(const std::string& aContent) : Node("h3", aContent) {}
};

class Paragraph : public Node {
public:
    Paragraph(const std::string& aContent) : Node("p", aContent) {}
};

class Link : public Node {
public:
    Link(const std::string& aContent, const std::string& aUrl) : Node("a", aContent) {
        addAttribute("href", aUrl);
    }
};

class Break : public Node {
public:
    Break() : Node("br") {}
};

class Document {
public:
    Document() {}

    void addToHead(Node&& aNode) {
        mHead.addChild(std::move(aNode));
    }
    void addToBody(Node&& aNode) {
        mBody.addChild(std::move(aNode));
    }
    Document& operator<<(Node&& aNode) {
        addToBody(std::move(aNode));
        return *this;
    }

    Node& head() {
        return mHead;
    }
    Node& body() {
        return mBody;
    }

    friend std::ostream& operator<< (std::ostream& aStream, const Document& aNode);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

private:
    std::ostream& toString(std::ostream& aStream) const {
        aStream << "<html>\n" << mHead << mBody << "</html>\n";
        return aStream;
    }

private:
    Head mHead;
    Body mBody;
};

std::ostream& operator<< (std::ostream& aStream, const Document& aDocument) {
    return aDocument.toString(aStream);
}

} // namespace HTML

/**
 * @brief Entry-point of the application.
 */
int main() {
    HTML::Document document;
    document.head() << HTML::Title("Welcome to HTML");
    document << HTML::Header1("Welcome to HTML");
    // TODO: we would need to embedd nodes into other nodes like "<p>text<br/>next line</p>"
//    document << HTML::Paragraph("This is the way to go for a big text.") << "Additionnal text for the same paragraph.";
    document << HTML::Paragraph("Another paragraph.") << HTML::Break();
    document << HTML::Link("Google", "http://google.com");
    std::cout << document;
    return 0;
}
