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
std::shared_ptr<Token> Scanner::createTokenFromValue(std::string val) {
    off64_t position = sourceInterface->position;
    if(val == "int" || val == "unsigned_int" || val == "float" || val == "string" || val == "system_handler") {
        return std::make_shared<Token>(val, T_SPECIFIER, position);
    }
    if(val == "while") {
        return std::make_shared<Token>(val, T_WHILE, position);
    }
    if(val == "for") {
        return std::make_shared<Token>(val, T_FOR, position);
    }
    if(val == "if") {
        return std::make_shared<Token>(val, T_IF, position);
    }
    if(val == "do") {
        return std::make_shared<Token>(val, T_DO, position);
    }
    if(val == "else") {
        return std::make_shared<Token>(val, T_ELSE, position);
    }
    if(val == "done") {
        return std::make_shared<Token>(val, T_DONE, position);
    }
    return std::make_shared<Token>(val, T_USER_DEFINED_NAME, position);
}
std::shared_ptr<Token> Scanner::createSpecialSignToken(std::string val) {
    off64_t position = sourceInterface->position;
    if(val == "(") {
        return std::make_shared<Token>(val, T_OPENING_PARENTHESIS, position);
    }
    if(val == ")") {
        return std::make_shared<Token>(val, T_CLOSING_PARENTHESIS, position);
    }
    if(val == ",") {
        return std::make_shared<Token>(val, T_SEMICON, position);
    }
    if(val == ":") {
        return std::make_shared<Token>(val, T_CON, position);
    }
    if(val == "{") {
        return std::make_shared<Token>(val, T_OPENING_BRACKET, position);
    }
    if(val == "}") {
        return std::make_shared<Token>(val, T_CLOSING_BRACKET, position);
    }
    if(val == ".") {
        return std::make_shared<Token>(val, T_DOT, position);
    }
}
char Scanner::getNextSign() {
    sourceInterface->getNextSign();
    sign = sourceInterface->sign;
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
bool Scanner::tryToBuildSimpleToken() {
    std::string val;

    if(sign == EOF) {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_EOF, sourceInterface->position));
        throw std::runtime_error("End of file reached");
    }
    if(sign == '*' || sign == '/') {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_MULT_OPERATOR, sourceInterface->position));
        return true;
    }
    if(sign == '&') {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_BOOLEAN_AND, sourceInterface->position));
        return true;
    }
    if(sign == '.') {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_DOT, sourceInterface->position));
        return true;
    }
    if(sign == '+' || sign == '-'){
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_ADD_OPERATOR, sourceInterface->position));
        return true;
    }
    if(sign == '|') {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_BOOLEAN_OR, sourceInterface->position));
        return true;
    }
    if(sign == '?') {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_NEXT_LINE, sourceInterface->position));
        return true;
    }
    // assign or boolean prefix
    if(sign == '=' || sign == '>' || sign == '<') {
        val = appendVal(val);
        if(sign == '=') {
            val = appendVal(val);
            tokens.push(std::make_shared<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position));
            return true;
        } else {
            if(val == "=") {
                tokens.push( std::make_shared<Token>(val, T_ASSIGN_OPERATOR, sourceInterface->position));
                return true;
            } else {
                tokens.push(std::make_shared<Token>(val, T_BOOLEAN_OPERATOR, sourceInterface->position));
                return true;
            }
        }
    } else if (sign == ')' || sign == '(' || sign == '{' || sign == '}' || sign == ',' || sign == ':') {
        val = appendVal(val);
        tokens.push(createSpecialSignToken(val));
        return true;

    }  else if (sign == '$') {
        val = appendVal(val);
        tokens.push(std::make_shared<Token>(val, T_END, sourceInterface->position));
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

//        if(sign == '.') {
//            throw std::runtime_error("Forbidden sign in name!");
//        }
        tokens.push(createTokenFromValue(val));
        return true;

    } else if (sign == '"') {

        do {
            val = appendVal(val);
        } while (sign != '"');
        // " " are not stored
        val = val.substr(1, val.size());
        tokens.push(std::make_unique<Token>(sign, T_STRING, sourceInterface->position));
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
    tokens.push(std::make_unique<Token>(sign, T_NOT_DEFINED_YET, sourceInterface->position));
    getNextSign();
    return true;
}
Scanner::Scanner(Configuration configuration) {
    this->isVerbose = configuration.isVerbose;
    configuration.inputPath = "/home/robert/Desktop/data.txt";
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
