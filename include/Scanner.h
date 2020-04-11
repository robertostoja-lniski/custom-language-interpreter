//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H

enum State {

    UNDEFINED_STATE = -1,
    START = 0,
    READING_NAME = 1,
    READING_REAL_NUM = 2,
    READING_INTEGER_NUM = 3,
    READING_OPERATOR = 4,
    END = 5,
    TRAILING_SPACE = 6,
    INTERPUNCTION = 7,
    READING_SPECIAL_SIGN = 8,
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

};

struct NumAnalysingHelper {

    std::string integralPart;
    bool hasCon {false};
    bool hasDecimalPart {false};
    bool hasLeadingZero{false};

};

struct Token {

    std::string val;
    Type type {ANY};

    Token() = default;
    Token(std::string val, Type type) : val(val), type(type) {}

    friend bool operator==(const Token& lhs, const Token& rhs);
    friend bool operator!=(const Token& lhs, const Token& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Token& t);
};

class Scanner {

private:
//    NumAnalysingHelper numAnalysingHelper;
//    std::string val;
    State state{START};
    unsigned int currentCharIndex{0};

    bool isOperatorPrefix(char c);
    bool isAddOperator(char c);
    bool isMultOperator(char c);
    bool isAssignmentOperator(char c);
    bool isBooleanOperatorPrefix(char c);
    bool isBooleanOperatorSuffix(char c);

    bool isNum(char c);
    bool isNonDigit(char c);
    bool isSpace(char c);
    bool isSemicon(char c);
    bool isCon(char c);
    bool isComa(char c);
    bool isZero(char c);
    bool isEnd(char c);
    bool isInstructionOpening(char c);
    bool isInstructionClosing(char c);
    bool isCollectionOpening(char c);
    bool isCollectionClosing(char c);
    bool isTerm(char c);
    bool isInterpunction(char c);

    bool isOperator(std::string val);
    bool isAllowedForName(char c);
    bool isAllowedForNum(char c);
    bool isAllowedForOperator(char c);

    bool isOneOfNameTerm(char c);
    bool isOneOfNumTerm(char c);
    bool isOneOfOperatorTerm(char c);

    bool isSpecifier(std::string val);

    Type getValueType(std::string val);
    Type getOperatorType(std::string val);
    Type getSpecialSignType(char c);
    State getStateBasedOnFirstSign(char c);

public:
    Scanner() = default;
    Token getNextToken(std::string);
    std::vector<Token> scan();
    std::vector<Token> testScan(std::string);

};


#endif //TKOM_SCANNER_H
