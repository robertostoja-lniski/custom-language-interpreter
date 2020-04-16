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
class Token {

protected:
    std::string value;
    Position position;

public:
    Token() = default;

    friend bool operator==(const Token& lhs, const Token& rhs);
    friend bool operator!=(const Token& lhs, const Token& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Token& t);
};

class UserDefinedNameToken : public Token {
public:
    UserDefinedNameToken(std::string arg) {
        value = arg;
    }
};
class IntToken : public Token {
public:
    IntToken(std::string digits) {
        value = digits;
    }
};
class FloatToken : public Token {
public:
    FloatToken(std::string arg) {
        value = arg;
    }
};
class ExpressionToken : public Token {
public:
    ExpressionToken(std::string type) {
        value = type;
    }
};
class BlockToken : public Token {
public:
    BlockToken(std::string type) {
        value = type;
    }
};
class AddOperatorToken : public Token {
public:
    AddOperatorToken(std::string op) {
        value = op;
    }
    AddOperatorToken(char op) {
        value = op;
    }
};
class MultOperatorToken : public Token {
public:
    MultOperatorToken(std::string op) {
        value = op;
    }
    MultOperatorToken(char op) {
        value = op;
    }
};
class AssignOperatorToken : public Token {
public:
    AssignOperatorToken() {
        value = "=";
    }
    AssignOperatorToken(char sign) {
        value = sign;
    }
};
class BooleanOperatorToken : public Token {
public:
    BooleanOperatorToken(std::string op) {
        value = op;
    }
};
class SpecifierToken : public Token {
public:
    SpecifierToken(std::string specifier) {
        value = specifier;
    }
};
class ParenthesisToken : public Token {
public:
    ParenthesisToken(std::string prn) {
        value = prn;
    }
    ParenthesisToken(char prn) {
        value = prn;
    }
};
class InterpunctionToken : public Token {
public:
    InterpunctionToken(std::string interpunction) {
        value = interpunction;
    }
    InterpunctionToken(char interpunction) {
        value = interpunction;
    }
};
class StringToken : public Token {
public:
    StringToken(std::string string) {
        value = string;
    }
};
class BracketToken : public Token {
public:
    BracketToken(std::string bracket) {
        value = bracket;
    }
    BracketToken(char bracket) {
        value = bracket;
    }
};
class SpecialToken : public Token {
public:
    SpecialToken(std::string special) {
        value = special;
    }
    SpecialToken(char special) {
        value = special;
    }
};
class UnknownToken : public Token {
public:
    UnknownToken(std::string val) {
        value = val;
    }
};

struct NumAnalysingHelper {

    std::string integralPart;
    bool hasCon {false};
    bool hasDecimalPart {false};
    bool hasLeadingZero{false};

};

class Scanner {

private:

    std::unique_ptr<SourceInterface> sourceInterface;
    std::unique_ptr<Token> token;

    bool isOperatorPrefix(char c);
    bool isAddOperator(char c);
    bool isMultOperator(char c);

    bool isBooleanOperatorPrefix(char c);
    bool isBooleanOperatorSuffix(char c);
    bool isBracketOrParenthesis(char c);

    bool isOperator(std::string val);
    bool isAllowedForName(char c);

    bool isOneOfNameTerm(char c);
    bool isOneOfNumTerm(char c);
    bool isOneOfOperatorTerm(char c);

    bool isSpecifier(std::string val);

    std::unique_ptr<Token> getValueType(std::string val);
    std::unique_ptr<Token> getOperatorType(std::string val);
    std::unique_ptr<Token> getSpecialSignType(char c);

public:
    Scanner() {
        sourceInterface = std::make_unique<FileInterface>();
    }

    void getNextToken();
    void readToken();
    // not implemented yet
//  void setPrams(Configuration configuration);
    char getNextSign();
    bool isReadingPossible();
};


#endif //TKOM_SCANNER_H
