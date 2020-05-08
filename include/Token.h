//
// Created by robert on 19.04.2020.
//

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include <string>
#include <iostream>

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
    T_BOOLEAN_AND = 24,
    T_BOOLEAN_OR = 24,
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
    bool isOperand() {
        return type == T_INT_NUM || type == T_USER_DEFINED_NAME ||
                type == T_REAL_NUM || type == T_STRING;
    }
    friend bool operator==(const Token& lhs, const Token& rhs);
    friend bool operator!=(const Token& lhs, const Token& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Token& t);

    bool isOperator() {
        return type == T_MULT_OPERATOR || type == T_BOOLEAN_AND || type == T_ADD_OPERATOR ||
                type == T_BOOLEAN_OPERATOR || type == T_BOOLEAN_OR || type == T_OPENING_PARENTHESIS;
    };

    bool isClosingParenthesis();
};

#endif //TKOM_TOKEN_H
