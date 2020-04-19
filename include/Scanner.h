//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H

#include <memory>
#include <iostream>
#include <fstream>
#include "Configuration.h"

struct SourceInterface {

    off64_t position {0};
    char sign;
    virtual void getNextSign() = 0;
    SourceInterface() = default;
};
struct FileInterface : public SourceInterface {

    std::string filepath;
    std::unique_ptr<std::ifstream> is;

    FileInterface(std::string path) : filepath(path) {
        is = std::make_unique<std::ifstream>(filepath);
    }

    ~FileInterface() {
        is->close();
    }

    void getNextSign() {

        char c;
        is->get(c);
        sign = c;
        position++;
    }
};
struct TerminalInterface : public SourceInterface {

    size_t index {0};
    TerminalInterface() = default;

    void getNextSign() {
    }
};

enum Type {

    ANY = 0,
    T_USER_DEFINED_NAME = 1,
    T_WHILE = 2,
    T_IF = 3,
    T_EXIT = 4,
    T_REAL_NUM = 5,
    T_INT_NUM = 6,
    T_DO = 7,
    T_DONE = 8,
    T_ADD_OPERATOR = 9,
    T_MULT_OPERATOR = 10,
    T_BOOLEAN_OPERATOR = 11,
    T_ASSIGN_OPERATOR = 12,
    T_SPECIFIER = 13,
    T_OPENING_PARENTHESIS = 14,
    T_CLOSING_PARENTHESIS = 15,
    T_SEMICON = 16,
    T_CON = 17,
    T_OPENING_BRACKET = 18,
    T_CLOSING_BRACKET = 19,
    T_END = 20,
    T_NOT_DEFINED_YET = 21,
    T_STRING = 22,
    T_EOF = 23,
};

class Token {

private:
    std::string value;
    Type type;
    off64_t position{0};

public:
    Token() = default;
    // position is not necessary, since we can have the same tokens with different positions
    Token(std::string value, Type type, off64_t position = 0) : value(value), type(type), position(position) {}
    Token(char sign, Type type, off64_t position = 0) : type(type), position(position) {
        value = sign;
    }

    std::string getValue() { return value; }
    Type getType() { return type; }
    off64_t getPosition() { return position; }

    friend bool operator==(const Token& lhs, const Token& rhs);
    friend bool operator!=(const Token& lhs, const Token& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Token& t);
};

class Scanner {

private:

    std::unique_ptr<SourceInterface> sourceInterface;
    std::unique_ptr<Token> token;
    char sign;
    bool isVerbose {false};

    bool isBracketOrParenthesis(char c);
    bool isSpecifier(std::string val);

    std::unique_ptr<Token> getValueType(std::string val);
    std::unique_ptr<Token> getSpecialSignType(char c);

    void finalizeGeneratingToken(std::string val, Type type);
    void finalizeGeneratingToken(char c, Type type);
    std::string appendValWhileIsDigit(std::string);

    bool tryToBuildSimpleToken();
    bool tryToBuildNumToken();
    bool tryToBuildAlphaTokens();
    void removeWhiteSigns();
    bool tryToBuildNotDefinedToken();

public:
    Scanner(Configuration configuration);
    void getNextToken();
    // simple printing tokens
    void readToken();
    char getNextSign();
    Token getTokenValue();
};


#endif //TKOM_SCANNER_H
