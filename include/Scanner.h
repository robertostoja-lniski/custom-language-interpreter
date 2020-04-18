//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H

#include <memory>
#include <iostream>
#include <fstream>

struct Position {
    size_t column {0};
    size_t row {1};

    Position() = default;
};

struct SourceInterface {

    std::unique_ptr<Position> position;
    char sign;
    virtual void getNextSign() = 0;
    SourceInterface() {
        position = std::make_unique<Position>();
    }
};
struct FileInterface : public SourceInterface {

    std::string filepath = "/home/robert/Desktop/data.txt";
    std::unique_ptr<std::ifstream> is;

    FileInterface(std::string path) {
        is = std::make_unique<std::ifstream>(path);
        filepath = path;
    }

    FileInterface() {
        is = std::make_unique<std::ifstream>(filepath);
    }

    ~FileInterface() {
        is->close();
    }

    void getNextSign() {

        char c;
        is->get(c);
        sign = c;
        position->column++;
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

};

class Token {

private:
    std::string value;
    Type type;
//    Position position;

public:
    Token() = default;
    Token(std::string value, Type type) : value(value), type(type) {}
    Token(char sign, Type type) : type(type) {
        value = sign;
    }

    std::string getValue() { return value; }
    Type getType() { return type; }
    friend bool operator==(const Token& lhs, const Token& rhs);
    friend bool operator!=(const Token& lhs, const Token& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Token& t);
};

class Scanner {

private:

    std::unique_ptr<SourceInterface> sourceInterface;
    std::unique_ptr<Token> token;
    char sign;

    bool isOperatorPrefix(char c);
    bool isAddOperator(char c);
    bool isMultOperator(char c);

    bool isBooleanOperatorPrefix(char c);
    bool isBracketOrParenthesis(char c);

    bool isOneOfNumTerm(char c);
    bool isSpecifier(std::string val);

    std::unique_ptr<Token> getValueType(std::string val);
    std::unique_ptr<Token> getSpecialSignType(char c);

public:
    Scanner() {
        sourceInterface = std::make_unique<FileInterface>();
        getNextSign();
    }
    Scanner(std::string path) {
        sourceInterface = std::make_unique<FileInterface>(path);
        getNextSign();
    }
    void getNextToken();
    void readToken();
    // not implemented yet
//  void setPrams(Configuration configuration);
    char getNextSign();
    Token getTokenValue();
};


#endif //TKOM_SCANNER_H
