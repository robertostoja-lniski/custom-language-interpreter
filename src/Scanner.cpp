//
// Created by robert on 04.04.2020.
//

#include <string>
#include <iostream>
#include "../include/Scanner.h"

void Scanner::getNextToken() {

    std::string val;

    while(iswspace(sign)) {
        getNextSign();
    }

    if(sign == '*' || sign == '/' || sign == '|') {
        token = std::make_unique<Token>(sign, T_MULT_OPERATOR);
        getNextSign();
        return;
    }

    if( sign == '+' || sign == '-' || sign == '$'){
        token = std::make_unique<Token>(sign, T_ADD_OPERATOR);
        getNextSign();
        return;
    }

    // assign or boolean prefix
    if(sign == '=' || sign == '>' || sign == '<') {

        val += sign;
        getNextSign();

        if(sign == '=') {

            val += sign;
            token = std::make_unique<Token>(val, T_BOOLEAN_OPERATOR);
            getNextSign();
            return;

        } else {

            if(val == "=") {
                token = std::make_unique<Token>(val, T_ASSIGN_OPERATOR);
                getNextSign();
                return;
            }
        }
    }

    if (isdigit(sign)) {

        if(sign != '0'){

            do {
                val+=sign;
                getNextSign();
            } while(isdigit(sign));

            if(sign == '.') {
                do {
                    val+=sign;
                    getNextSign();
                } while(isdigit(sign));

                token = std::make_unique<Token>(val, T_REAL_NUM);
                getNextSign();
                return;

            } else {
                // tmp removes .
                token = std::make_unique<Token>(val, T_INT_NUM);
                getNextSign();
                return;
            }
        }
        else
        {
            val+=sign;
            getNextSign();

            if(sign == '.') {
                do {
                    val+=sign;
                    getNextSign();
                } while(isdigit(sign));

                token = std::make_unique<Token>(val, T_REAL_NUM);
                getNextSign();
                return;

            } else {
                token = std::make_unique<Token>(val, T_INT_NUM);
                getNextSign();
                return;
            }
        }

    } else if (isalpha(sign) || sign == '_') {

        do {
            val += sign;
            getNextSign();
        } while(isalpha(sign) || sign == '_' || isdigit(sign));

        token = getValueType(val);
        getNextSign();
        return;

    } else if (sign == '$') {
        token = std::make_unique<Token>(val, T_END);
        getNextSign();
        return;

    } else if (isBracketOrParenthesis(sign) || sign == ',' || sign == ':') {

        val += sign;
        token = getSpecialSignType(val[0]);
        getNextSign();
        return;

    } else if (sign == '"') {

        do {
            val += sign;
            getNextSign();
        } while (sign != '"');

        val = val.substr(1, val.size()-1);
        token = std::make_unique<Token>(val, T_STRING);
        getNextSign();
        return;
    }

    token = std::make_unique<Token>(sign, T_NOT_DEFINED_YET);
    getNextSign();
    return;
}

bool Scanner::isAddOperator(char c) {
    return c == '-' || c == '+' || c == '|';
}

bool Scanner::isMultOperator(char c) {
    return c == '/' || c == '*' || c == '&';
}

bool Scanner::isBooleanOperatorPrefix(char c) {
    return c == '=' || c == '>' || c == '<';
}

bool Scanner::isOperatorPrefix(char c) {
    return isAddOperator(c) || isMultOperator(c) || isBooleanOperatorPrefix(c);
}


bool Scanner::isSpecifier(std::string val) {
    return val == "int" || val == "unsigned_int" || val == "float" || val == "string" || val == "system_handler";
}

bool Scanner::isOneOfNumTerm(char c) {
    return iswspace(c) || isOperatorPrefix(c) || isBracketOrParenthesis(c) || c == '$' || c == '"';
}

std::unique_ptr<Token> Scanner::getValueType(std::string val) {

    if(isSpecifier(val)) {
        return std::make_unique<Token>(val, T_SPECIFIER);
    }
    if(val == "while") {
        return std::make_unique<Token>(val, T_WHILE);
    }
    if(val == "if") {
        return std::make_unique<Token>(val, T_IF);
    }
    if(val == "do") {
        return std::make_unique<Token>(val, T_DO);
    }
    if(val == "done") {
        return std::make_unique<Token>(val, T_DONE);
    }

    return std::make_unique<Token>(val, T_USER_DEFINED_NAME);
}

bool Scanner::isBracketOrParenthesis(char c) {
    return c == ')' || c == '(' || c == '{' || c == '}';
}

std::unique_ptr<Token> Scanner::getSpecialSignType(char c) {

    if(c == '(') {
        return std::make_unique<Token>(c, T_OPENING_PARENTHESIS);
    }
    if(c == ')') {
        return std::make_unique<Token>(c, T_CLOSING_PARENTHESIS);
    }
    if(c == ',') {
        return std::make_unique<Token>(c, T_SEMICON);
    }
    if(c == ':') {
        return std::make_unique<Token>(c, T_CON);
    }
    if(c == '$') {
        return std::make_unique<Token>(c, T_END);
    }
    if(c == '{') {
        return std::make_unique<Token>(c, T_OPENING_BRACKET);
    }
    if(c == '}') {
        return std::make_unique<Token>(c, T_CLOSING_BRACKET);
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
    return {token->getValue(), token->getType()};
}

bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.value == rhs.value && typeid(rhs) == typeid(lhs);
}

bool operator!=(const Token &lhs, const Token &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, const Token& t) {
    return out << t.value << " " << t.type;
}

