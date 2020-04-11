//
// Created by robert on 04.04.2020.
//

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Scanner.h"

Token Scanner::getNextToken(std::string input) {

    NumAnalysingHelper numAnalysingHelper;
    std::string val;
    state = START;

    for (;currentCharIndex < input.size(); currentCharIndex++) {

        char sign = input[currentCharIndex];
        if(state == START) {
            state = getStateBasedOnFirstSign(sign);
        }

        if(state == READING_NAME) {

            if(isOneOfNameTerm(sign)) {
                auto type = getValueType(val);
                state = START;
                return {val, type};
            }

            if(!isAllowedForName(sign)) {
                throw std::runtime_error("Error in reading name");
            }

        } else if(state == READING_REAL_NUM) {

            if(isOneOfNumTerm(sign)){
                if(!numAnalysingHelper.hasDecimalPart) {
                    throw std::runtime_error("No decimal part in real number");
                }
                state = START;
                return {val, T_REAL_NUM};
            }

            if(!isAllowedForNum(sign)) {
                throw std::runtime_error("Forbidden sign in real number");
            }
            numAnalysingHelper.hasDecimalPart = true;

        } else if(state == READING_INTEGER_NUM) {

            if(isOneOfNumTerm(sign)){
                state = START;
                return {val, T_INT_NUM};
            }

            if(isZero(sign)) {
                //if it is leading zero
                if(val.empty()) {
                    numAnalysingHelper.hasLeadingZero = true;
                } else if(numAnalysingHelper.hasLeadingZero) {
                    throw std::runtime_error("Too many zeros in prefix");
                }
            }
            
            if(isComa(sign)) {
                numAnalysingHelper.hasCon = true;
                state = READING_REAL_NUM;
            } else if(!isAllowedForNum(sign)) {
                throw std::runtime_error("Forbidden sign in integer number");
            }

        } else if(state == READING_OPERATOR) {

            if(isOperator(val) || isOneOfOperatorTerm(sign)) {
                state = START;
                auto type = getOperatorType(val);
                return {val, type};
            }

            if(val.size() == 1 && !isBooleanOperatorSuffix(sign)) {
                throw std::runtime_error("Forbidden sign in reading operator");
            }

        } else if(state == READING_SPECIAL_SIGN) {

            if(!val.empty()) {
                auto type = getSpecialSignType(val[0]);
                return {val, type};
            }

        } else if(state == END) {

            currentCharIndex++;
            return {"$", T_END};

        } else if(state == TRAILING_SPACE) {

            state = START;
            continue;

        } else {
            throw std::runtime_error("Unknown expression");
        }

        val += sign;
    }

    return {"UNDEFINED", ANY};
}

std::vector<Token> Scanner::scan() {

    std::vector<Token> tokens;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    std::string input;
    std::getline(std::cin, input);
    input += "$";

        try {
            while(currentCharIndex < input.size()) {
                auto nextToken = getNextToken(input);
                tokens.emplace_back(nextToken);
                std::cout << nextToken << std::endl;
            }
        }catch(std::exception& e){
            std::cout << e.what() << std::endl;
        }
    return tokens;

}


bool Scanner::isNum(char c) {
    return isdigit(c);
}

bool Scanner::isNonDigit(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isSpace(char c){
    return c == ' ';
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

bool Scanner::isInstructionOpening(char c) {
    return c == '(';
}

bool Scanner::isSemicon(char c) {
    return c == ',';
}

bool Scanner::isCon(char c) {
    return c == ':';
}

bool Scanner::isOneOfNumTerm(char c) {
    return isSpace(c) || isOperatorPrefix(c) || isInterpunction(c) || isTerm(c);
}

bool Scanner::isOneOfNameTerm(char c) {
    return isOneOfNumTerm(c);
}

bool Scanner::isAllowedForName(char c) {
    return isNum(c) || isNonDigit(c);
}

bool Scanner::isZero(char c) {
    return c == '0';
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

State Scanner::getStateBasedOnFirstSign(char c) {

    if(isOperatorPrefix(c)) {
        return READING_OPERATOR;
    }

    if(isNum(c)) {
        return READING_INTEGER_NUM;
    }

    if(isNonDigit(c)) {
        return READING_NAME;
    }

    if(isTerm(c)) {
        return END;
    }

    if(isSpace(c)) {
        return TRAILING_SPACE;
    }

    if(isInterpunction(c) || isCon(c)) {
        return READING_SPECIAL_SIGN;
    }
    return UNDEFINED_STATE;
}

bool Scanner::isAllowedForNum(char c) {
    return isNum(c);
}

bool Scanner::isAllowedForOperator(char c) {
    return isOperatorPrefix(c) || isBooleanOperatorSuffix(c);
}

bool Scanner::isOneOfOperatorTerm(char c) {
    return isSpace(c) || isNum(c) || isNonDigit(c) ||  isTerm(c) || isInterpunction(c);
}

Type Scanner::getOperatorType(std::string val) {

    //TODO
    //jedna wielka heura
    //niejawne zalozenie ze kazdy dwuznakowy operator to boolean
    //nie sprawdza sie wiekszych operatorow powinno wywlac wyjatek (trzeba dodac tez obsluge)

    if(val.size() == 1) {

        char sign = val[0];

        if(isAddOperator(sign)) {
            return T_ADD_OPERATOR;
        }

        if(isMultOperator(sign)) {
            return T_MULT_OPERATOR;
        }

        if(isAssignmentOperator(sign)){
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

bool Scanner::isInstructionClosing(char c) {
    return c == ')';
}

bool Scanner::isTerm(char c) {
    return c == '$';
}

bool Scanner::isCollectionClosing(char c) {
    return c == '}';
}

bool Scanner::isCollectionOpening(char c) {
    return c == '{';
}

bool Scanner::isInterpunction(char c) {
    return isInstructionOpening(c) || isInstructionClosing(c) || isCollectionOpening(c) || isCollectionClosing(c) || isSemicon(c);
}

Type Scanner::getSpecialSignType(char c) {
    if(isInstructionOpening(c)) {
        return T_OPENING_PARENTHESIS;
    }

    if(isInstructionClosing(c)){
        return T_CLOSING_PARENTHESIS;
    }

    if(isSemicon(c)) {
        return T_SEMICON;
    }

    if(isCon(c)) {
        return T_CON;
    }

    if(isCollectionOpening(c)) {
        return T_OPENING_BRACKET;
    }

    if(isCollectionClosing(c)) {
        return T_CLOSING_BRACKET;
    }

    if(isTerm(c)) {
        return T_END;
    }
}

bool Scanner::isAssignmentOperator(char c) {
    return c == '=';
}

bool Scanner::isComa(char c) {
    return c == '.';
}

std::vector<Token> Scanner::testScan(std::string input) {
    input += "$";

    std::vector<Token> tokens;
    try {
        while(currentCharIndex < input.size()) {
            auto nextToken = getNextToken(input);
            tokens.emplace_back(nextToken);
        }
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return tokens;
}

bool Scanner::isEnd(char c) {
    return false;
}

bool Scanner::isOperator(std::string val) {

    bool isSingle = val.size() == 1;
    bool isSingleOperator = isSingle && (isAddOperator(val[0]) || isMultOperator(val[0]));

    bool isDouble = val.size() == 2;
    bool isDoubleOperator = isDouble && isBooleanOperatorPrefix(val[0]) && isBooleanOperatorSuffix(val[1]);

    return isSingleOperator || isDoubleOperator;
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
