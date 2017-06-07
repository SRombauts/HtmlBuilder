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
 *   The Document is a specialized Element with restriction on what can be done on it,
 * since many aspects of the <html> root tag are well defined and constrained.
 */
class Document : public Element {
public:
    explicit Document(const char* apTitle = nullptr) : mHead(mChildren[0]), mBody(mChildren[1]) {
        if (nullptr != apTitle) {
            addToHead(HTML::Title(apTitle));
        }
    }
    explicit Document(std::string&& aTitle) : mHead(mChildren[0]), mBody(mChildren[1]) {
        addToHead(HTML::Title(std::move(aTitle)));
    }
    explicit Document(const std::string& aTitle) : mHead(mChildren[0]), mBody(mChildren[1]) {
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

    Element&& addChild(Element&& aElement) = delete;

    friend std::ostream& operator<< (std::ostream& aStream, const Document& aElement);
    std::string toString() const {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

private:
    std::ostream& toString(std::ostream& aStream) const {
        aStream << "<!doctype html>\n";
        Element::toString(aStream);
        return aStream;
    }

private:
    Element& mHead; ///< Reference to the first child <head> Element
    Element& mBody; ///< Reference to the second child <body> Element
};

std::ostream& operator<< (std::ostream& aStream, const Document& aDocument) {
    return aDocument.toString(aStream);
}

} // namespace HTML

