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
    void addDeclarationsToTree(std::shared_ptr<RootExpression> declaration);
    std::shared_ptr<RootExpression> tryToBuildVarNamePrefixStatement();
    std::shared_ptr<TypeSpecifierExpression> getExpressionWithAssignedSpecifier();
    std::shared_ptr<BodyExpression> getParamsAsManyDeclarations();
    std::shared_ptr<RootExpression> assignTreeToRoot();
    bool parseNoArgFunctionCall();
    bool tryToParseManyArgsFunctionCall();
    bool tryToParseUserDefinedName();
    bool tryToHandleOperand();
    bool parseConstantValue();
    bool tryToParseFunctionCall();
    void transformTokenIntoTreeNode(std::shared_ptr<Token> token);
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
    void createNoArgFunctionExpression(Token token);
    void createNextLineExpression(Token token);
    void createForExpression(Token token);
    void createIfExpression(Token token);
    void createElseExpression(Token token);
    void createWhileExpression(Token token);
    void createDoExpression(Token token);
    void createDoneExpression(Token token);
    void createFieldReferenceExpression(Token token);
    void joinUpperStatementsUntilDoFound(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperExpression(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperElse(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperDeclaration(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr);
    void assignBodyToUpperAnyExpression(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr);
    void setDoubleArgsExpr(std::shared_ptr<DoubleArgsExpression> doubleArgsExpression);
    void dummy() {
//        postfixRepresentation.push_front(std::make_shared<Token>());
    };
    Token getTokenValFromScanner();

    std::map<Type, std::function<void(Token token)>> tokensToNode {
            {T_INT_NUM, [&](Token token){createIntExpression(token);}},
            {T_REAL_NUM, [&](Token token){createFloatExpression(token);}},
            {T_ADD_OPERATOR, [&](Token token){createAdditionExpression(token);}},
            {T_MULT_OPERATOR, [&](Token token){createMultExpression(token);}},
            {T_BOOLEAN_OPERATOR, [&](Token token){createBooleanOperatorExpression(token);}},
            {T_BOOLEAN_AND, [&](Token token){createBooleanAndExpression(token);}},
            {T_SEMICON, [&](Token token){createSemiconExpression(token);}},
            {T_BOOLEAN_OR, [&](Token token){createBooleanOrExpression(token);}},
            {T_ASSIGN_OPERATOR, [&](Token token){createAssignExpression(token);}},
            {T_USER_DEFINED_NAME, [&](Token token){createVarNameExpression(token);}},
            {T_FUNCTION_NAME, [&](Token token){createFunctionCallExpression(token);}},
            {T_NEXT_LINE, [&](Token token){dummy();}},
            {T_NO_ARG_FUNCTION_NAME, [&](Token token){createNoArgFunctionExpression(token);}},
            {T_WHILE, [&](Token token){createWhileExpression(token);}},
            {T_IF, [&](Token token){createIfExpression(token);}},
            {T_ELSE, [&](Token token){createElseExpression(token);}},
            {T_FOR, [&](Token token){createForExpression(token);}},
            {T_DO, [&](Token token){createDoExpression(token);}},
            {T_DONE, [&](Token token){createDoneExpression(token);}},
            {T_DOT, [&](Token token){createFieldReferenceExpression(token);}},
            {T_DUMMY_ARG, [&](Token token){createVarNameExpression(token);}},
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
    void printPostfix();
    bool handleOperator();
    Token seeNextToken();
    std::deque<std::shared_ptr<Token>> getPostfixRepresentation();
    std::shared_ptr<RootExpression> generatePostfixRepresentation();
    std::shared_ptr<RootExpression> generateTree();

public:
    Parser(std::shared_ptr<Scanner> scanner){
        this->scanner = scanner;
        mainRoot = std::make_unique<FileExpression>();
    };
    void analyzeTree();
    void parse();
};


#endif //TKOM_PARSER_H
