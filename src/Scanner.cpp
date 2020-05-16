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
        val = appendVal(val);
    } while(isdigit(sign));
    return val;
}
bool Scanner::tryToBuildAssignmentOrBooleanToken() {
    std::string val;

    if(sign == '<' || sign == '>') {
        val = appendVal(val);
        if(sign == '=') {
            val = appendVal(val);
        }
        tokens.push(std::make_shared<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position));
        return true;
    }

    if(sign == '=') {
        val = appendVal(val);
        if(sign == '=' || sign == '>' || sign == '<') {
            val = appendVal(val);
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
    std::string val;
    if (isdigit(sign)) {
        // assume that it is real num
        // generate possible real num prefixes
        if(sign != '0'){
            val = appendValWhileIsDigit(val);
        } else {
            // single zero prefix
            val = appendVal(val);
        }
        // try to generate sufix
        if(sign == '.') {
            val = appendVal(val);
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
        // if cannot generate sufix it is int
        // we do not get next sign, because the sign that was not
        // a digit, it has to be interpreted (it can be * or : or etc.)
        tokens.push(std::make_unique<Token>(val, T_INT_NUM, sourceInterface->position));
        return true;
    }
    return false;
}
bool Scanner::tryToBuildAlphaTokens() {
    std::string val;

    if (isalpha(sign) || sign == '_') {
        do {
            val = appendVal(val);
        } while(isalpha(sign) || sign == '_' || isdigit(sign));

        createTokenFromValue(val);
        return true;

    } else if (sign == '"') {

        do {
            val = appendVal(val);
        } while (sign != '"');
        // " " are not stored
        val = val.substr(1, val.size());
        tokens.push(std::make_unique<Token>(sign, T_STRING, sourceInterface->position));
        this->sign = getNextSign();
        return true;
    }
    return false;
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

std::string Scanner::appendVal(std::string val) {
    val += sign;
    this->sign = getNextSign();
    return val;
}


