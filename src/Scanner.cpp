//
// Created by robert on 04.04.2020.
//

#include <string>
#include <iostream>
#include "../include/Scanner.h"

void Scanner::getNextToken() {

    NumAnalysingHelper numAnalysingHelper;
    std::string val;
    while (isReadingPossible()) {

        char sign = getNextSign();
        if (isOperatorPrefix(sign)) {

            while (!isOperator(val) && !isOneOfOperatorTerm(sign)) {

                if (val.size() == 1 && !isBooleanOperatorSuffix(sign)) {
                    throw std::runtime_error("Forbidden sign in reading operator");
                }
                val += sign;
                sign = getNextSign();
            }

             token = getOperatorType(val);
             return;

        } else if (isdigit(sign)) {

            while (!isOneOfNumTerm(sign)) {

                if (sign == '0') {
                    //if it is leading zero
                    if (val.empty()) {
                        numAnalysingHelper.hasLeadingZero = true;
                    } else if (numAnalysingHelper.hasLeadingZero) {
                        throw std::runtime_error("Too many zeros in prefix");
                    }
                }

                if (sign == '.') {
                    numAnalysingHelper.hasCon = true;

                    val += sign;
                    sign = getNextSign();

                    while (!isOneOfNumTerm(sign)) {

                        if (!isdigit(sign)) {
                            throw std::runtime_error("Forbidden sign in real number");
                        }
                        numAnalysingHelper.hasDecimalPart = true;

                        val += sign;
                        sign = getNextSign();
                    }

                    if (!numAnalysingHelper.hasDecimalPart) {
                        throw std::runtime_error("No decimal part in real number");
                    }

                    token = std::make_unique<FloatToken>(val);
                    return;

                } else if (!isdigit(sign)) {
                    throw std::runtime_error("Forbidden sign in integer number");
                }

                val += sign;
                sign = getNextSign();
            }

            token = std::make_unique<IntToken>(val);
            return;

        } else if (isalpha(sign) || sign == '_') {

            while (!isOneOfNameTerm(sign)) {
                if (!isAllowedForName(sign)) {
                    throw std::runtime_error("Error in reading name");
                }

                val += sign;
                sign = getNextSign();
            }

            token = getValueType(val);
            return;

        } else if (sign == '$') {
            token = std::make_unique<SpecialToken>(val);
            return;

        } else if (iswspace(sign)) {
            continue;

        } else if (isBracketOrParenthesis(sign) || sign == ',' || sign == ':') {

            val += sign;
            token = getSpecialSignType(val[0]);
            return;

        } else if (sign == '"') {

            while (val.empty() || sign != '"') {
                val += sign;
                sign = getNextSign();
            }

            val = val.substr(1, val.size());
            token = std::make_unique<StringToken>(val);
        }
    }
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

bool Scanner::isBooleanOperatorSuffix(char c) {
    return c == '=';
}

bool Scanner::isSpecifier(std::string val) {
    return val == "int" || val == "unsigned_int" || val == "float" || val == "string" || val == "system_handler";
}

bool Scanner::isOneOfNumTerm(char c) {
    return iswspace(c) || isOperatorPrefix(c) || isBracketOrParenthesis(c) || c == '$' || c == '"';
}

bool Scanner::isOneOfNameTerm(char c) {
    return isOneOfNumTerm(c);
}

bool Scanner::isAllowedForName(char c) {
    return isdigit(c) || isalpha(c) || c == '_';
}

std::unique_ptr<Token> Scanner::getValueType(std::string val) {

    if(isSpecifier(val)) {
        return std::make_unique<SpecifierToken>(val);
    }
    if(val == "while" || val == "if") {
        return std::make_unique<ExpressionToken>(val);
    }
    if(val == "do" || val == "done") {
        return std::make_unique<BlockToken>(val);
    }

    return std::make_unique<UserDefinedNameToken>(val);
}

bool Scanner::isOneOfOperatorTerm(char c) {
    return c == ' ' || isdigit(c) || isalpha(c) || c == '$' || isBracketOrParenthesis(c);
}

std::unique_ptr<Token> Scanner::getOperatorType(std::string val) {

    if(val.size() == 1) {

        char sign = val[0];

        if(isAddOperator(sign)) {
            return std::make_unique<AddOperatorToken>(sign);
        }

        if(isMultOperator(sign)) {
            return std::make_unique<MultOperatorToken>(sign);
        }

        if(sign == '='){
            return std::make_unique<AssignOperatorToken>(sign);
        }

        if(isBooleanOperatorPrefix(sign)) {
            return std::make_unique<BooleanOperatorToken>(val);
        }
    }
    if(val.size() == 2) {
        return std::make_unique<BooleanOperatorToken>(val);
    }

    return std::make_unique<UnknownToken>("Not defined yet");
}


bool Scanner::isBracketOrParenthesis(char c) {
    return c == ')' || c == '(' || c == '{' || c == '}';
}

std::unique_ptr<Token> Scanner::getSpecialSignType(char c) {

    if(c == '(' || c == ')') {
        return std::make_unique<ParenthesisToken>(c);
    }

    if(c == ',' || c == ':' || c == '$') {
        return std::make_unique<SpecialToken>(c);
    }

    if(c == '{' || c == '}') {
        return std::make_unique<BracketToken>(c);
    }

    return std::make_unique<SpecialToken>("unknown");
}


bool Scanner::isOperator(std::string val) {

    bool isSingle = val.size() == 1;
    bool isSingleOperator = isSingle && (isAddOperator(val[0]) || isMultOperator(val[0]));

    bool isDouble = val.size() == 2;
    bool isDoubleOperator = isDouble && isBooleanOperatorPrefix(val[0]) && isBooleanOperatorSuffix(val[1]);

    return isSingleOperator || isDoubleOperator;
}

char Scanner::getNextSign() {
    sourceInterface->getNextSign();
    return sourceInterface->sign;
}

bool Scanner::isReadingPossible() {
    return true;
}

void Scanner::readToken() {
    std::cout << *token << std::endl;
}

bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.value == rhs.value && typeid(rhs) == typeid(lhs);
}

bool operator!=(const Token &lhs, const Token &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, const Token& t) {

    std::string type;
    return out << t.value;
}
