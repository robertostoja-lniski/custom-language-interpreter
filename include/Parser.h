//
// Created by robert on 06.05.2020.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H
#include "Token.h"
#include <memory>
#include <stack>
#include <vector>
#include <map>
#include <functional>
#include <queue>
#include "boost/lexical_cast.hpp"
#include "RepresentationConverter.h"
#include "Visitor.h"
#include "Scanner.h"

using boost::lexical_cast;

class Parser {
private:

    //tmp just for one subtree
    std::unique_ptr<RepresentationConverter> converter;
    // right not used
    std::shared_ptr<RootExpression> root;
    std::stack <std::shared_ptr<Expression>> recentExpressions;
    std::queue <Token> functionCall;
    bool isBuildingFunctionStarted {false};

    bool tryToBuildExpression(Token token);
    void createIntExpression(Token token);
    void createFloatExpression(Token token);
    void createAdditionExpression(Token token);
    void createMultExpression(Token token);
    void createAssignExpression(Token token);
    void createVarNameExpression(Token token);
    void createFunctionCallExpression(Token token);
    void createBooleanAndExpression(Token token);
    void createBooleanOrExpression(Token token);
    void createBooleanOperatorExpression(Token token);
    void createSemiconExpression(Token token);
    void addDoubleArgsExpression(std::unique_ptr<DoubleArgsExpression> doubleArgsExpression);

    std::map<Type, std::function<void(Token)>> tokensToNode {
            {T_INT_NUM, [&](Token token) {createIntExpression(token);}},
            {T_REAL_NUM, [&](Token token) {createFloatExpression(token);}},
            {T_ADD_OPERATOR, [&](Token token) {createAdditionExpression(token);}},
            {T_MULT_OPERATOR, [&](Token token) {createMultExpression(token);}},
            {T_BOOLEAN_OPERATOR, [&](Token token) {createBooleanOperatorExpression(token);}},
            {T_BOOLEAN_AND, [&](Token token) {createBooleanAndExpression(token);}},
            {T_SEMICON, [&](Token token) {createSemiconExpression(token);}},
            {T_BOOLEAN_OR, [&](Token token) {createBooleanOrExpression(token);}},
            {T_ASSIGN_OPERATOR, [&](Token token) {createAssignExpression(token);}},
            {T_USER_DEFINED_NAME, [&](Token token) {createVarNameExpression(token);}},
            {T_FUNCTION_NAME, [&](Token token) {createFunctionCallExpression(token);}},
            {T_SPECIFIER, [&](Token token) {createVarNameExpression(token);}},
    };


public:
    void parseToken(Token tokenToParse);
    Parser() { converter = std::make_unique<RepresentationConverter>(); };
    void generateTree();
    void analyzeTree();
    std::shared_ptr<Scanner> scanner;
    void parseNextToken() {
        int i = 20;
        while (i--) {
            scanner->getNextToken();
            scanner->readToken();
            auto token = scanner->getTokenValue();
            if (token.getType() == T_END) {
                return;
            }
            parseToken(token);
        }
    }

    bool tryToBuildFunctionCall(Token token);
};


#endif //TKOM_PARSER_H
