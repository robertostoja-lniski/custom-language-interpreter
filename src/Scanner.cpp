#include <string>
#include <iostream>
#include "../include/Scanner.h"

void Scanner::getNextToken() {

    removeWhiteSigns();

    try {
        if(tryToBuildSimpleToken() || tryToBuildNumToken()
            || tryToBuildAlphaTokens() || tryToBuildNotDefinedToken()) {
            return;
        }
    } catch(std::exception &e) {
        std::cout << e.what();
        exit(1);
    }
}
std::unique_ptr<Token> Scanner::createTokenFromValue(std::string val) {
    off64_t position = sourceInterface->position;
    if(val == "int" || val == "unsigned_int" || val == "float" || val == "string" || val == "system_handler") {
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
std::unique_ptr<Token> Scanner::createSpecialSignToken(std::string val) {
    off64_t position = sourceInterface->position;
    if(val == "(") {
        return std::make_unique<Token>(val, T_OPENING_PARENTHESIS, position);
    }
    if(val == ")") {
        return std::make_unique<Token>(val, T_CLOSING_PARENTHESIS, position);
    }
    if(val == ",") {
        return std::make_unique<Token>(val, T_SEMICON, position);
    }
    if(val == ":") {
        return std::make_unique<Token>(val, T_CON, position);
    }
    if(val == "{") {
        return std::make_unique<Token>(val, T_OPENING_BRACKET, position);
    }
    if(val == "}") {
        return std::make_unique<Token>(val, T_CLOSING_BRACKET, position);
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
std::string Scanner::appendValWhileIsDigit(std::string val) {
    do {
        val = appendVal(val);
    } while(isdigit(sign));
    return val;
}
bool Scanner::tryToBuildSimpleToken() {
    std::string val;

    if(sign == EOF) {
        val = appendVal(val);
        token = std::make_unique<Token>(val, T_EOF, sourceInterface->position);
        throw std::runtime_error("End of file reached");
    }
    if(sign == '*' || sign == '/') {
        val = appendVal(val);
        token = std::make_unique<Token>(val, T_MULT_OPERATOR, sourceInterface->position);
        return true;
    }
    if(sign == '&') {
        val = appendVal(val);
        token = std::make_unique<Token>(val, T_BOOLEAN_AND, sourceInterface->position);
        return true;
    }
    if(sign == '+' || sign == '-'){
        val = appendVal(val);
        token = std::make_unique<Token>(val, T_ADD_OPERATOR, sourceInterface->position);
        return true;
    }
    if(sign == '|') {
        val = appendVal(val);
        token = std::make_unique<Token>(val, T_BOOLEAN_OR, sourceInterface->position);
        return true;
    }
    // assign or boolean prefix
    if(sign == '=' || sign == '>' || sign == '<') {
        val = appendVal(val);
        if(sign == '=') {
            val = appendVal(val);
            token = std::make_unique<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position);
            return true;
        } else {
            if(val == "=") {
                token = std::make_unique<Token>(val, T_ASSIGN_OPERATOR, sourceInterface->position);
                return true;
            } else {
                token = std::make_unique<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position);
                return true;
            }
        }
    } else if (sign == ')' || sign == '(' || sign == '{' || sign == '}' || sign == ',' || sign == ':') {
        val = appendVal(val);
        token = createSpecialSignToken(val);
        return true;

    }  else if (sign == '$') {
        val = appendVal(val);
        token = std::make_unique<Token>(val, T_END, sourceInterface->position);
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
            val = appendVal(val);
        }
        // try to generate sufix
        if(sign == '.') {
            val = appendVal(val);
            if(isdigit(sign)) {
                val = appendValWhileIsDigit(val);
                token = std::make_unique<Token>(val, T_REAL_NUM, sourceInterface->position);
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
        token = std::make_unique<Token>(val, T_INT_NUM, sourceInterface->position);
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

        if(sign == '.') {
            throw std::runtime_error("Forbidden sign in name!");
        }
        token = createTokenFromValue(val);
        return true;

    } else if (sign == '"') {

        do {
            val = appendVal(val);
        } while (sign != '"');
        // " " are not stored
        val = val.substr(1, val.size());
        token = std::make_unique<Token>(sign, T_STRING, sourceInterface->position);
        getNextSign();
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
    token = std::make_unique<Token>(sign, T_NOT_DEFINED_YET, sourceInterface->position);
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

std::string Scanner::appendVal(std::string val) {
    val += sign;
    getNextSign();
    return val;
}
