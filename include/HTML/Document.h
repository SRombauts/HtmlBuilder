/**
* @file    Document.h
* @ingroup HtmlBuilder
* @brief   Root Element of the HTML Document Object Model.
*
* Copyright (c) 2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
*
* Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
* or copy at http://opensource.org/licenses/MIT)
*/
#pragma once

#include "Element.h"

#include <sstream>
#include <string>


namespace HTML {

/**
 * @brief Root Element of the HTML Document Object Model.
 *
 * TODO NOCOMMIT: rework this to make it an Element as all other, with some overloads/deleted methods to restrict what can be done
 *   The Document is not a specialized Element only to restrict what can be done on it,
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

    void addToHead(Element&& aElement) {
        mHead.addChild(std::move(aElement));
    }
    void addToBody(Element&& aElement) {
        mBody.addChild(std::move(aElement));
    }
    Element& operator<<(Element&& aElement) {
        addToBody(std::move(aElement));
        return mBody;
    }

    Element& head() {
        return mHead;
    }
    Element& body() {
        return mBody;
    }

    friend std::ostream& operator<< (std::ostream& aStream, const Document& aElement);
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

