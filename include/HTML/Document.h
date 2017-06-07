/**
* @file    Document.h
* @ingroup HtmlBuilder
* @brief   Root of the HTML Document Object Model.
*
* Copyright (c) 2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
*
* Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
* or copy at http://opensource.org/licenses/MIT)
*/
#pragma once

#include "Node.h"

#include <sstream>
#include <string>


namespace HTML {

/**
 * @brief Root of the HTML Document Object Model.
 *
 * The Document is not a specialized Node only to restrict what can be done on it,
 * since many aspects of the <html> root tag are well defined.
 */
class Document {
public:
    explicit Document(const char* apTitle = nullptr) {
        if (nullptr != apTitle) {
            addToHead(HTML::Title(apTitle));
        }
    }
    explicit Document(std::string&& aTitle) {
        addToHead(HTML::Title(std::move(aTitle)));
    }
    explicit Document(const std::string& aTitle) {
        addToHead(HTML::Title(aTitle));
    }

    void addToHead(Node&& aNode) {
        mHead.addChild(std::move(aNode));
    }
    void addToBody(Node&& aNode) {
        mBody.addChild(std::move(aNode));
    }
    Node& operator<<(Node&& aNode) {
        addToBody(std::move(aNode));
        return mBody;
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
        aStream << "<!doctype html>\n<html>\n" << mHead << mBody << "</html>\n";
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

