#include <string>
#include <iostream>
#include "../include/Scanner.h"

void Scanner::getNextToken() {
    removeWhiteSigns();
    try {
        if(tryToBuildAssignmentOrBooleanToken() || tryToBuildSpecialSignToken() || tryToBuildNumToken()
            || tryToBuildAlphaTokens() || tryToBuildNotDefinedToken()) {
            return;
        }
    } catch(std::exception &e) {
        std::cout << e.what();
        exit(1);
    }
}
void Scanner::createTokenFromValue(std::string val) {
    if(complexTokensHandlers.find(val) == complexTokensHandlers.end()) {
        tokens.push(std::make_shared<Token>(std::move(val), T_USER_DEFINED_NAME));
        return;
    }
    auto complexTokenHandler = complexTokensHandlers[val];
    complexTokenHandler(val);
}
char Scanner::getNextSign() {
    sourceInterface->getNextSign();
    position = sourceInterface->position;
    return sourceInterface->sign;
}
void Scanner::readToken() {
    std::cout << *tokens.front() << std::endl;
}
Token Scanner::seeTokenValue() {
    getNextToken();
    auto token = tokens.front();
    return {token->getValue(), token->getType(), token->getPosition()};
}
Token Scanner::getTokenValue() {
    auto token = std::move(tokens.front());
    tokens.pop();
    return {token->getValue(), token->getType(), token->getPosition()};
}
std::string Scanner::appendValWhileIsDigit(std::string val) {
    do {
        val += getSignAndReadNext();
    } while(isdigit(sign));
    return val;
}
bool Scanner::tryToBuildAssignmentOrBooleanToken() {
    return tryToBuildGreaterOrLessBoolean() || tryToBuildAssignOrCompare();
}
bool Scanner::tryToBuildGreaterOrLessBoolean() {
    if(sign == '<' || sign == '>') {
        std::string val;
        val += getSignAndReadNext();
        if(sign == '=') {
            val += getSignAndReadNext();
        }
        tokens.push(std::make_shared<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position));
        return true;
    }
    return false;
}

bool Scanner::tryToBuildAssignOrCompare() {
    if(sign == '=') {
        std::string val;
        val += getSignAndReadNext();
        if(sign == '=') {
            val += getSignAndReadNext();
            tokens.push(std::make_shared<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position));
            return true;
        }
        tokens.push(std::make_shared<Token>(val, T_ASSIGN_OPERATOR, sourceInterface->position));
        return true;
    }
    return false;
}

bool Scanner::tryToBuildSpecialSignToken() {
    if(simpleTokensHandlers.find(sign) == simpleTokensHandlers.end()) {
        return false;
    }
    auto simpleTokenHandler = simpleTokensHandlers[sign];
    simpleTokenHandler(sign);
    this->sign = getNextSign();
    return true;
}
bool Scanner::tryToBuildNumToken() {
    if (isdigit(sign)) {
        std::string integerPrefix = returnIntegerPrefixIfBuildPossible();
        if(!tryToBuildRealNumWithGivenPrefix(integerPrefix)) {
            tokens.push(std::make_unique<Token>(integerPrefix, T_INT_NUM, sourceInterface->position));
            return true;
        }
    }
    return false;
}

std::string Scanner::returnIntegerPrefixIfBuildPossible() {
    std::string val;
    if(sign != '0'){
        val = appendValWhileIsDigit(val);
    } else {
        val += getSignAndReadNext();
    }
    return val;
}

bool Scanner::tryToBuildRealNumWithGivenPrefix(std::string val) {
    if(sign == '.') {
        val += getSignAndReadNext();
        if(isdigit(sign)) {
            val = appendValWhileIsDigit(val);
            tokens.push(std::make_unique<Token>(val, T_REAL_NUM, sourceInterface->position));
            return true;
        } else {
            throw std::runtime_error("No suffix in real num!");
        }
    }
    if(isalpha(sign) || sign == '(' ) {
        throw std::runtime_error("Forbidden sign in num!");
    }
}
bool Scanner::tryToBuildNonQuotedSign() {
    if (isalpha(sign) || sign == '_') {
        std::string val;
        do {
            val += getSignAndReadNext();
        } while(isalpha(sign) || sign == '_' || isdigit(sign));

        createTokenFromValue(val);
        return true;
    }
    return false;
}
bool Scanner::tryToBuildQuotedSign() {
     if (sign == '"') {
         std::string val;
        do {
            val += getSignAndReadNext();
            if(sign == '\\') {
                val += getSignAndReadNext();
            }
        } while (sign != '"');
        // " " are not stored
         val += getSignAndReadNext();
        tokens.push(std::make_unique<Token>(val, T_STRING, sourceInterface->position));
        return true;
    }
    return false;
}
bool Scanner::tryToBuildAlphaTokens() {
    return tryToBuildNonQuotedSign() || tryToBuildQuotedSign();
}

void Scanner::removeWhiteSigns() {
    while(iswspace(sign)) {
        this->sign = getNextSign();
    }
}
bool Scanner::tryToBuildNotDefinedToken() {
    tokens.push(std::make_unique<Token>(sign, T_NOT_DEFINED_YET, sourceInterface->position));
    this->sign = getNextSign();
    return true;
}
Scanner::Scanner(Configuration configuration) {
    this->isVerbose = configuration.isVerbose;
    if(configuration.inputPath != "tmp.txt") {
        configuration.inputPath = "/home/robert/Desktop/data.txt";
    }

    if(!configuration.inputPath.empty()) {
        sourceInterface = std::make_unique<FileInterface>(configuration.inputPath);
    } else {
        sourceInterface = std::make_unique<TerminalInterface>();
    }
    if(!configuration.outputPath.empty()) {
        //TODO raports and analyses will be added in final project step.
    }
    this->sign = getNextSign();
}

char Scanner::getSignAndReadNext() {
    return std::exchange(sign, getNextSign());
}
