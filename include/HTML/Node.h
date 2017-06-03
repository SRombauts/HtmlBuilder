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
#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace HTML {

class Node {
public:
    Node(const char* apName, const std::string& aContent) :
        mName(apName), mContent(aContent) {}
    explicit Node(const char* apName, const char* apContent = nullptr) :
        mName(apName), mContent(apContent ? apContent : "") {}

    Node& addAttribute(const char* apName, const std::string& aValue) {
        mAttributes[apName] = aValue;
        return *this;
    }
    Node& addChild(Node&& aNode) {
        mChildren.push_back(std::move(aNode));
        return *this;
    }
    Node& operator<<(Node&& aNode) {
        addChild(std::move(aNode));
        return *this;
    }
    Node& operator<<(const char* apContent);

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
        // TODO(SRombauts): rewrite/optimize the following
        if (!mName.empty()) {
            if (mContent.empty()) {
                aStream << "/>\n";
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
    std::vector<Node> mChildren;
};

std::ostream& operator<<(std::ostream& aStream, const Node& aNode) {
    return aNode.toString(aStream);
}

class Text : public Node {
public:
    explicit Text(const char* apContent) : Node("", apContent) {}
};

Node& Node::operator<<(const char* apContent) {
    addChild(Text(apContent));
    return *this;
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
    explicit Title(const std::string& aContent) : Node("title", aContent) {}
};

class Header1 : public Node {
public:
    explicit Header1(const std::string& aContent) : Node("h1", aContent) {}
};

class Header2 : public Node {
public:
    explicit Header2(const std::string& aContent) : Node("h2", aContent) {}
};

class Header3 : public Node {
public:
    explicit Header3(const std::string& aContent) : Node("h3", aContent) {}
};

class Paragraph : public Node {
public:
    explicit Paragraph(const std::string& aContent) : Node("p", aContent) {}
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

} // namespace HTML
