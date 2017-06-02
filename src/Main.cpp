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

    friend std::ostream& operator<< (std::ostream& aStream, const Node& aNode);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

private:
    std::string mName;
    std::string mContent;
    std::map<std::string, std::string> mAttributes;
    std::vector<Node> mChildren;
};

std::ostream& operator<< (std::ostream& aStream, const Node& aNode) {
    aStream << '<' << aNode.mName;
    for (const auto& attr : aNode.mAttributes) {
        aStream << ' ' << attr.first << "=\"" << attr.second << "\"";
    }
    if (aNode.mContent.empty() && aNode.mChildren.empty()) {
        aStream << "/>\n";
    }
    else {
        if (aNode.mContent.empty()) {
            aStream << ">\n";
        } else  {
            aStream << '>' << aNode.mContent;
        }
        for (auto& child : aNode.mChildren) {
            aStream << child;
        }
        aStream << "</" << aNode.mName << ">\n";
    }
    return aStream;
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

    friend std::ostream& operator<< (std::ostream& aStream, const Document& aNode);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

    Node& head() {
        return mHead;
    }
    Node& body() {
        return mBody;
    }

private:
    Head mHead;
    Body mBody;
};

std::ostream& operator<< (std::ostream& aStream, const Document& aNode) {
    aStream << "<html>\n";
    aStream << aNode.mHead;
    aStream << aNode.mBody;
    aStream << "</html>\n";
    return aStream;
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
    document << HTML::Paragraph("This is the way to go for a big text.") << HTML::Break();
    document << HTML::Paragraph("Another paragraph.") << HTML::Break();
    document << HTML::Link("Google", "http://google.com");
    std::cout << document;
    return 0;
}
