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
#include "Visitor.h"
#include "Scanner.h"

using boost::lexical_cast;

class Parser {
private:

    //tmp just for one subtree
    std::shared_ptr<Scanner> scanner;
    // right not used
    std::unique_ptr<FileExpression> mainRoot;
    std::stack <std::shared_ptr<Expression>> recentExpressions;
    Token token;
    void parseProgram();
    void addDeclarationsToTree(std::shared_ptr<RootExpression> declaration);
    bool tryToBuildExpression(Token token);
    std::shared_ptr<RootExpression> tryToBuildDeclaration();
    bool tryToBuildDeclarationLegacy();
    std::shared_ptr<TypeSpecifierExpression> getExpressionWithAssignedSpecifier();
    std::shared_ptr<BodyExpression> getParamsAsManyDeclarations();
    void assignTreeToRoot();
    void transformTokenIntoTreeNode(std::shared_ptr<Token> token);
    void createIntExpression();
    void createFloatExpression();
    void createAdditionExpression();
    void createMultExpression();
    void createAssignExpression();
    void createVarNameExpression();
    void createFunctionCallExpression();
    void createBooleanAndExpression();
    void createBooleanOrExpression();
    void createBooleanOperatorExpression();
    void createSemiconExpression();
    void createNoArgFunctionExpression();
    void createNextLineExpression();
    void createForExpression();
    void createIfExpression();
    void createElseExpression();
    void createWhileExpression();
    void createDoExpression();
    void createDoneExpression();
    void createFieldReferenceExpression();
    void joinUpperStatementsUntilDoFound(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperExpression(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperElse(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperDeclaration(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr);
    void assignBodyToUpperAnyExpression(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr);
    void setDoubleArgsExpr(std::shared_ptr<DoubleArgsExpression> doubleArgsExpression);

    Token getTokenValFromScanner();

    std::map<Type, std::function<void(void)>> tokensToNode {
            {T_INT_NUM, [&](){createIntExpression();}},
            {T_REAL_NUM, [&](){createFloatExpression();}},
            {T_ADD_OPERATOR, [&](){createAdditionExpression();}},
            {T_MULT_OPERATOR, [&](){createMultExpression();}},
            {T_BOOLEAN_OPERATOR, [&]() {createBooleanOperatorExpression();}},
            {T_BOOLEAN_AND, [&](){createBooleanAndExpression();}},
            {T_SEMICON, [&](){createSemiconExpression();}},
            {T_BOOLEAN_OR, [&](){createBooleanOrExpression();}},
            {T_ASSIGN_OPERATOR, [&](){createAssignExpression();}},
            {T_USER_DEFINED_NAME, [&](){createVarNameExpression();}},
            {T_FUNCTION_NAME, [&](){createFunctionCallExpression();}},
            {T_NO_ARG_FUNCTION_NAME, [&](){createNoArgFunctionExpression();}},
            {T_NEXT_LINE, [&](){createNextLineExpression();}},
            {T_WHILE, [&](){createWhileExpression();}},
            {T_IF, [&](){createIfExpression();}},
            {T_ELSE, [&](){createElseExpression();}},
            {T_FOR, [&](){createForExpression();}},
            {T_DO, [&](){createDoExpression();}},
            {T_DONE, [&](){createDoneExpression();}},
            {T_DOT, [&](){createFieldReferenceExpression();}},
            {T_DUMMY_ARG, [&](){createVarNameExpression();}},
    };

    // operators by priority
    struct Priority {
        int in;
        int out;
    };

    std::map<Type, Priority> priorities {
            {T_CON, {1,0}},
            {T_OPENING_PARENTHESIS, {0,INT_MAX}},
            {T_SEMICON, {2,1}},
            {T_DOT, {2,1}},
            {T_SPECIFIER, {3,2}},
            {T_BOOLEAN_OR, {4,3}},
            {T_BOOLEAN_AND, {5,4}},
            {T_ASSIGN_OPERATOR,{6,5}},
            {T_BOOLEAN_OPERATOR, {7,6}},
            {T_ADD_OPERATOR, {8,7}},
            {T_MULT_OPERATOR, {9,8}},
            {T_FUNCTION_NAME, {10,9}},
            {T_NO_ARG_FUNCTION_NAME, {10,9}},
            {T_SEMICON, {11,10}},
            {T_FOR,{12,11}},
            {T_IF, {13,12}},
            {T_ELSE, {14,13}},
            {T_WHILE, {15,14}},
            {T_DO, {16,15}},
            {T_DONE, {17,16}},
            {T_NEXT_LINE, {18,17}},
    };

    std::stack <std::shared_ptr<Token>> operators;
    std::deque <std::shared_ptr<Token>> postfixRepresentation;

    void finalize();
    bool tryToHandleSpecialToken();
    bool tryToHandleEmbeddedExpression();
    bool tryToHandleEmbeddedDo();
    bool tryToHandleEmbeddedDone();
    bool tryToGenerateCondition();
    bool tryToHandleNextLine();
    bool tryToHandleOperand();
    void printPostfix();
    std::deque<std::shared_ptr<Token>> getPostfixRepresentation();
    bool generatePostfixRepresentation(Token token);

public:
    Parser(std::shared_ptr<Scanner> scanner){
        this->scanner = scanner;
        mainRoot = std::make_unique<FileExpression>();
    };
    void generateTree();
    void analyzeTree();
    void parse();
};


#endif //TKOM_PARSER_H
