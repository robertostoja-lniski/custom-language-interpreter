//
// Created by robert on 04.04.2020.
//

#include <string>
#include <iostream>
#include "../include/Scanner.h"

void Scanner::getNextToken() {

    removeWhiteSigns();
    try {
        if(tryToBuildSimpleToken()) {
            return;
        }
        if(tryToBuildNumToken()){
            return;
        }
        if(tryToBuildAlphaTokens()) {
            return;
        }
        if(tryToBuildNotDefinedToken()) {
            return;
        }
    } catch(std::exception &e) {
        std::cout << e.what();
        exit(1);
    }
}

bool Scanner::isSpecifier(std::string val) {
    return val == "int" || val == "unsigned_int" || val == "float" || val == "string" || val == "system_handler";
}

std::unique_ptr<Token> Scanner::getValueType(std::string val) {

    off64_t position = sourceInterface->position;

    if(isSpecifier(val)) {
        return std::make_unique<Token>(val, T_SPECIFIER, position);
    }
    if(val == "while") {
        return std::make_unique<Token>(val, T_WHILE, position);
    }
    if(val == "if") {
        return std::make_unique<Token>(val, T_IF, position);
    }
    if(val == "do") {
        return std::make_unique<Token>(val, T_DO, position);
    }
    if(val == "done") {
        return std::make_unique<Token>(val, T_DONE, position);
    }

    return std::make_unique<Token>(val, T_USER_DEFINED_NAME, position);
}

bool Scanner::isBracketOrParenthesis(char c) {
    return c == ')' || c == '(' || c == '{' || c == '}';
}

std::unique_ptr<Token> Scanner::getSpecialSignType(char c) {

    off64_t position = sourceInterface->position;
    if(c == '(') {
        return std::make_unique<Token>(c, T_OPENING_PARENTHESIS, position);
    }
    if(c == ')') {
        return std::make_unique<Token>(c, T_CLOSING_PARENTHESIS, position);
    }
    if(c == ',') {
        return std::make_unique<Token>(c, T_SEMICON, position);
    }
    if(c == ':') {
        return std::make_unique<Token>(c, T_CON, position);
    }
    if(c == '$') {
        return std::make_unique<Token>(c, T_END, position);
    }
    if(c == '{') {
        return std::make_unique<Token>(c, T_OPENING_BRACKET, position);
    }
    if(c == '}') {
        return std::make_unique<Token>(c, T_CLOSING_BRACKET, position);
    }
}

char Scanner::getNextSign() {
    sourceInterface->getNextSign();
    sign = sourceInterface->sign;
}

void Scanner::readToken() {
    std::cout << *token << std::endl;
}

Token Scanner::getTokenValue() {
    return {token->getValue(), token->getType(), token->getPosition()};
}

void Scanner::finalizeGeneratingToken(std::string val, Type type) {
    off64_t position = sourceInterface->position;
    token = std::make_unique<Token>(val, type, position);
    getNextSign();
}

void Scanner::finalizeGeneratingToken(char c, Type type) {
    off64_t position = sourceInterface->position;
    token = std::make_unique<Token>(c, type, position);
    getNextSign();
}

std::string Scanner::appendValWhileIsDigit(std::string val) {
    do {
        val+=sign;
        getNextSign();
    } while(isdigit(sign));
    return val;
}

bool Scanner::tryToBuildSimpleToken() {
    std::string val;
    if(sign == '*' || sign == '/' || sign == '|') {
        val += sign;
        finalizeGeneratingToken(val, T_MULT_OPERATOR);
        return true;
    }

    if( sign == '+' || sign == '-' || sign == '$'){
        val += sign;
        finalizeGeneratingToken(val, T_ADD_OPERATOR);
        return true;
    }

    // assign or boolean prefix
    if(sign == '=' || sign == '>' || sign == '<') {

        val += sign;
        getNextSign();

        if(sign == '=') {

            val += sign;
            finalizeGeneratingToken(val, T_BOOLEAN_OPERATOR);
            return true;

        } else {

            if(val == "=") {
                finalizeGeneratingToken(val, T_ASSIGN_OPERATOR);
                return true;
            }
        }
    } else if (isBracketOrParenthesis(sign) || sign == ',' || sign == ':') {

        val += sign;
        token = getSpecialSignType(val[0]);
        getNextSign();
        return true;

    }  else if (sign == '$') {
        finalizeGeneratingToken(sign, T_END);
        return true;
    }

    return false;
}

bool Scanner::tryToBuildNumToken() {
    std::string val;
    if (isdigit(sign)) {
        // assume that it is real num
        // generate possible real num prefixes
        if(sign != '0'){
            val = appendValWhileIsDigit(val);
        } else {
            // single zero prefix
            val+=sign;
            getNextSign();
        }
        // try to generate sufix
        if(sign == '.') {
            val+=sign;
            getNextSign();

            if(isdigit(sign)) {
                val = appendValWhileIsDigit(val);
                finalizeGeneratingToken(val, T_REAL_NUM);
                return true;
            } else {
                throw std::runtime_error("No suffix in real num!");
            }
        }

        // if cannot generate sufix it is int
        finalizeGeneratingToken(val, T_INT_NUM);
        return true;

    }
    return false;
}

bool Scanner::tryToBuildAlphaTokens() {
    std::string val;

    if (isalpha(sign) || sign == '_') {

        do {
            val += sign;
            getNextSign();
        } while(isalpha(sign) || sign == '_' || isdigit(sign));

        token = getValueType(val);
        getNextSign();
        return true;

    } else if (sign == '"') {

        do {
            val += sign;
            getNextSign();
        } while (sign != '"');

        // " " are not stored
        finalizeGeneratingToken(val.substr(1, val.size()-1), T_STRING);
        return true;
    }
    return false;
}

void Scanner::removeWhiteSigns() {
    while(iswspace(sign)) {
        getNextSign();
    }
}

bool Scanner::tryToBuildNotDefinedToken() {
    finalizeGeneratingToken(sign, T_NOT_DEFINED_YET);
    return true;
}

bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.value == rhs.value && typeid(rhs) == typeid(lhs);
}

bool operator!=(const Token &lhs, const Token &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, const Token& t) {
    return out << t.value << " " << t.type << " " << t.position;
}

