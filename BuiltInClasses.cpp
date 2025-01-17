/* Copyright 2011 Tomas Härdin
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * File:   BuiltInClasses.cpp
 * Author: tjoppen
 * 
 * Created on February 14, 2010, 6:48 PM
 */

#include <stdexcept>
#include <sstream>
#include "BuiltInClasses.h"
#include "main.h"

using namespace std;

const string t = "    "; // Python indentation step (four spaces)

BuiltInClass::BuiltInClass(string name) : Class(FullName(XSL, name), Class::SIMPLE_TYPE) {
}

BuiltInClass::~BuiltInClass() {
}

bool BuiltInClass::isBuiltIn() const {
    return true;
}

string BuiltInClass::generateAppender() const {
    throw runtime_error("generateAppender() called in BuiltInClass");
}

string BuiltInClass::generateElementSetter(string memberName, string nodeName, string tabs) const {
    ostringstream oss;
    oss << tabs << "tmp = document.createElement(\"" << nodeName << "\")" << endl;
    oss << tabs << "tmpText = document.createTextNode(str(" << memberName << "))" << endl;
    oss << tabs << "tmp.appendChild(tmpText)" << endl;
    oss << tabs << "node.appendChild(tmp)" << endl;

    return oss.str();
}

string BuiltInClass::generateAttributeSetter(string memberName, string attributeName, string tabs) const {
    ostringstream oss;

    oss << tabs << "tmpAttr = document.createAttribute(\"" << memberName << "\")" << endl;
    oss << tabs << "tmpAttr.value = str(" << attributeName << ")" << endl;
    oss << tabs << "node.setAttributeNode(tmpAttr)" << endl;

    return oss.str();
}

string BuiltInClass::generateParser() const {
    throw runtime_error("generateParser() called in BuiltInClass");
}

string BuiltInClass::generateMemberSetter(string memberName, string nodeName, string tabs) const {
    ostringstream oss;
    
    oss << tabs << "if node.firstChild == None:" << endl;
    oss << tabs << t << memberName << " = None" << endl;
    oss << tabs << "else:" << endl;

    oss << tabs << t << memberName << " = ";
    string type = getClassname();
    if(type == "int" || type == "short" || type == "unsignedShort" || type == "unsignedInt" || type == "byte" || type == "unsignedByte") {
        oss << "int(node.firstChild.nodeValue)";
    } else if(type == "long" || type == "unsignedLong") {
        oss << "long(node.firstChild.nodeValue)";
    } else if(type == "float" || type == "double") {
        oss << "float(node.firstChild.nodeValue)";
    } else if(type == "string") {
        oss << "node.firstChild.nodeValue";
    } else {
        oss << "str(node.firstChild.nodeValue)";
    } 

    return oss.str();
}
