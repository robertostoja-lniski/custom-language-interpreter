//
// Created by robert on 04.04.2020.
//

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Scanner.h"

Token Scanner::getNextToken() {

    NumAnalysingHelper numAnalysingHelper;
    std::string val;
    while (true) {

        char sign = getNextSign();
        if (isOperatorPrefix(sign)) {

            while (!isOperator(val) && !isOneOfOperatorTerm(sign)) {

                if (val.size() == 1 && !isBooleanOperatorSuffix(sign)) {
                    throw std::runtime_error("Forbidden sign in reading operator");
                }
                val += sign;
                sign = getNextSign();
            }

            auto type = getOperatorType(val);
            return {val, type};

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

                    return {val, T_REAL_NUM};

                } else if (!isdigit(sign)) {
                    throw std::runtime_error("Forbidden sign in integer number");
                }

                val += sign;
                sign = getNextSign();
            }

            return {val, T_INT_NUM};

        } else if (isalpha(sign) || sign == '_') {

            while (!isOneOfNameTerm(sign)) {
                if (!isAllowedForName(sign)) {
                    throw std::runtime_error("Error in reading name");
                }

                val += sign;
                sign = getNextSign();
            }

            auto type = getValueType(val);
            return {val, type};

        } else if (sign == '$') {
            return {"$", T_END};

        } else if (iswspace(sign)) {
            continue;

        } else if (isBracketOrParenthesis(sign) || sign == ',' || sign == ':') {

            val += sign;
            auto type = getSpecialSignType(val[0]);
            return {val, type};

        } else if (sign == '"') {

            while (val.empty() || sign != '"') {
                val += sign;
                sign = getNextSign();
            }

            val = val.substr(1, val.size());
            return {val, T_STRING};
        }

    }

}

std::vector<Token> Scanner::scan() {

    std::vector<Token> tokens;
    std::string input;
    std::getline(std::cin, input);
    input += "$";
    setInput(input);

    try {
         while(currentCharIndex < input.size()) {
            auto nextToken = getNextToken();
            tokens.emplace_back(nextToken);
            std::cout << nextToken << std::endl;
         }
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
    return tokens;

}

bool Scanner::isAddOperator(char c) {
    std::vector<char> addOperators = {'-', '+', '|'};
    return std::find(addOperators.begin(), addOperators.end(), c) != addOperators.end();
}

bool Scanner::isMultOperator(char c) {
    std::vector<char> multOperators = {'/', '*', '&'};
    return std::find(multOperators.begin(), multOperators.end(), c) != multOperators.end();
}

bool Scanner::isBooleanOperatorPrefix(char c) {
    std::vector<char> operatorPrefixes = {'=', '>', '<'};
    return std::find(operatorPrefixes.begin(), operatorPrefixes.end(), c) != operatorPrefixes.end();
}

bool Scanner::isOperatorPrefix(char c) {
    return isAddOperator(c) || isMultOperator(c) || isBooleanOperatorPrefix(c);
}

bool Scanner::isBooleanOperatorSuffix(char c) {
    std::vector<char> doubleOperatorSuffixes = {'='};
    return std::find(doubleOperatorSuffixes.begin(), doubleOperatorSuffixes.end(), c) != doubleOperatorSuffixes.end();
}

bool Scanner::isSpecifier(std::string val) {
    std::vector<std::string> specifiers = {"int", "unsigned_int", "float", "string", "system_handler"};
    return std::find(specifiers.begin(), specifiers.end(), val) != specifiers.end();
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


Type Scanner::getValueType(std::string val) {

    if(isSpecifier(val)) {
        return T_SPECIFIER;
    }
    if(val == "while") {
        return T_WHILE;
    }
    if(val == "if") {
        return T_IF;
    }
    if(val == "exit") {
        return T_EXIT;
    }
    if(val == "do") {
        return T_DO;
    }
    if(val == "done") {
        return T_DONE;
    }

    return T_USER_DEFINED_NAME;
}

bool Scanner::isOneOfOperatorTerm(char c) {
    return c == ' ' || isdigit(c) || isalpha(c) || c == '$' || isBracketOrParenthesis(c);
}

Type Scanner::getOperatorType(std::string val) {

    if(val.size() == 1) {

        char sign = val[0];

        if(isAddOperator(sign)) {
            return T_ADD_OPERATOR;
        }

        if(isMultOperator(sign)) {
            return T_MULT_OPERATOR;
        }

        if(sign == '='){
            return T_ASSIGN_OPERATOR;
        }

        if(isBooleanOperatorPrefix(sign)) {
            return T_BOOLEAN_OPERATOR;
        }
    }
    if(val.size() == 2) {
        return T_BOOLEAN_OPERATOR;
    }

    return T_NOT_DEFINED_YET;
}


bool Scanner::isBracketOrParenthesis(char c) {
    return c == ')' || c == '(' || c == '{' || c == '}';
}

Type Scanner::getSpecialSignType(char c) {
    if(c == '(') {
        return T_OPENING_PARENTHESIS;
    }

    if(c == ')'){
        return T_CLOSING_PARENTHESIS;
    }

    if(c == ',') {
        return T_SEMICON;
    }

    if(c == ':') {
        return T_CON;
    }

    if(c == '{') {
        return T_OPENING_BRACKET;
    }

    if(c == '}') {
        return T_CLOSING_BRACKET;
    }

    if(c == '$') {
        return T_END;
    }
}


bool Scanner::isOperator(std::string val) {

    bool isSingle = val.size() == 1;
    bool isSingleOperator = isSingle && (isAddOperator(val[0]) || isMultOperator(val[0]));

    bool isDouble = val.size() == 2;
    bool isDoubleOperator = isDouble && isBooleanOperatorPrefix(val[0]) && isBooleanOperatorSuffix(val[1]);

    return isSingleOperator || isDoubleOperator;
}

char Scanner::getNextSign() {
    return input[currentCharIndex++];
}

void Scanner::setInput(std::string basicString) {
    this->input = basicString;
}

Token Scanner::getNextToken(std::string input) {

    this->input = input;
    this->currentCharIndex = 0;
    return getNextToken();
}

bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.val == rhs.val && lhs.type == rhs.type;
}

bool operator!=(const Token &lhs, const Token &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, const Token &t) {
    return out << t.val << " " << t.type ;
}
