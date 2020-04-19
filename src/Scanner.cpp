//
// Created by robert on 04.04.2020.
//

#include <string>
#include <iostream>
#include "../include/Scanner.h"

void Scanner::getNextToken() {

    // terminator token is $ T_END
    // if end exit parser
    if(token && token->getType() == T_END) {
        exit(0);
    }

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
}

void Scanner::finalizeGeneratingToken(char c, Type type) {
    off64_t position = sourceInterface->position;
    token = std::make_unique<Token>(c, type, position);
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
    if(sign == EOF) {
        val += sign;
        finalizeGeneratingToken(val, T_EOF);
        getNextSign();
        exit(0);
    }
    if(sign == '*' || sign == '/' || sign == '&') {
        val += sign;
        finalizeGeneratingToken(val, T_MULT_OPERATOR);
        getNextSign();
        return true;
    }

    if( sign == '+' || sign == '-' || sign == '|'){
        val += sign;
        finalizeGeneratingToken(val, T_ADD_OPERATOR);
        getNextSign();
        return true;
    }

    // assign or boolean prefix
    if(sign == '=' || sign == '>' || sign == '<') {

        val += sign;
        getNextSign();

        if(sign == '=') {

            val += sign;
            finalizeGeneratingToken(val, T_BOOLEAN_OPERATOR);
            getNextSign();
            return true;

        } else {

            if(val == "=") {
                finalizeGeneratingToken(val, T_ASSIGN_OPERATOR);
                return true;
            } else {
                finalizeGeneratingToken(val, T_BOOLEAN_OPERATOR);
                return true;
            }
        }
    } else if (isBracketOrParenthesis(sign) || sign == ',' || sign == ':') {

        token = getSpecialSignType(sign);
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
                // we do not get next sign, because the sign that was not
                // a digit, it has to be interpreted (it can be * or : or etc.)
                return true;
            } else {
                throw std::runtime_error("No suffix in real num!");
            }
        }
        if(isalpha(sign) || sign == '(' || sign == ')') {
            throw std::runtime_error("Forbidden sign in num!");
        }
        // if cannot generate sufix it is int
        // we do not get next sign, because the sign that was not
        // a digit, it has to be interpreted (it can be * or : or etc.)
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

        if(sign == '.') {
            throw std::runtime_error("Forbidden sign in name!");
        }
        token = getValueType(val);
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
    getNextSign();
    return true;
}

Scanner::Scanner(Configuration configuration) {

    this->isVerbose = configuration.isVerbose;

    if(!configuration.inputPath.empty()) {
        sourceInterface = std::make_unique<FileInterface>(configuration.inputPath);
    } else {
        sourceInterface = std::make_unique<TerminalInterface>();
    }

    if(!configuration.outputPath.empty()) {
        //TODO raports and analyses will be added in final project step.
    }

    getNextSign();
}

