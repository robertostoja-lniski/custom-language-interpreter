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
#include "EvaluationVisitor.h"
#include "Scanner.h"

using boost::lexical_cast;

class Parser {
private:

    std::shared_ptr<Scanner> scanner;
    std::unique_ptr<FileExpression> mainRoot;
    std::stack <std::shared_ptr<Expression>> recentExpressions;
    Token token;
    std::shared_ptr<RootExpression> tryToBuildVarNamePrefixStatement();
    std::shared_ptr<RootExpression> tryToBuildBuiltInFunctionCall();
    std::shared_ptr<RootExpression> tryToBuildBlockBoundary();
    std::shared_ptr<TypeSpecifierExpression> getExpressionWithAssignedSpecifier();
    std::shared_ptr<BodyExpression> getParamsAsManyDeclarations();
    std::shared_ptr<RootExpression> assignTreeToRoot();
    bool parseNoArgFunctionCall();
    bool tryToParseManyArgsFunctionCall();
    bool tryToHandleOperand();
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
    void createStringExpression(Token token);
    void createFieldReferenceExpression(Token token);
    void createFieldNameExpression(Token token);
    void handleNewExpression(std::shared_ptr<RootExpression> newExpr);
    void joinUpperStatementsUntilDoFound(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperExpression(std::shared_ptr<BodyExpression> condBody);
    void assignBodyToUpperIf(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<IfExpression> condExpr);
    void assignBodyToUpperWhile(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<WhileExpression> condExpr);
    void assignBodyToUpperAnyExpression(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr);
    void setDoubleArgsExpr(std::shared_ptr<DoubleArgsExpression> doubleArgsExpression);
    void dummy() {};
    Token getTokenValFromScanner();

    std::map<Type, std::function<void(Token token)>> tokensToNode {
            {T_INT_NUM, [&](Token token){createIntExpression(token);}},
            {T_REAL_NUM, [&](Token token){createFloatExpression(token);}},
            {T_STRING, [&](Token token){createStringExpression(token);}},
            {T_ADD_OPERATOR, [&](Token token){createAdditionExpression(token);}},
            {T_MULT_OPERATOR, [&](Token token){createMultExpression(token);}},
            {T_BOOLEAN_OPERATOR, [&](Token token){createBooleanOperatorExpression(token);}},
            {T_BOOLEAN_AND, [&](Token token){createBooleanAndExpression(token);}},
            {T_SEMICON, [&](Token token){createSemiconExpression(token);}},
            {T_BOOLEAN_OR, [&](Token token){createBooleanOrExpression(token);}},
            {T_ASSIGN_OPERATOR, [&](Token token){createAssignExpression(token);}},
            {T_USER_DEFINED_NAME, [&](Token token){createVarNameExpression(token);}},
            {T_FUNCTION_NAME, [&](Token token){createFunctionCallExpression(token);}},
            {T_FUNCTION_CALL, [&](Token token){createFunctionCallExpression(token);}},
            {T_NEXT_LINE, [&](Token token){dummy();}},
            {T_END, [&](Token token){dummy();}},
            {T_OPENING_PARENTHESIS, [&](Token token){dummy();}},
            {T_CLOSING_PARENTHESIS, [&](Token token){dummy();}},
            {T_NO_ARG_FUNCTION_NAME, [&](Token token){createNoArgFunctionExpression(token);}},
            {T_WHILE, [&](Token token){createWhileExpression(token);}},
            {T_IF, [&](Token token){createIfExpression(token);}},
            {T_ELSE, [&](Token token){createElseExpression(token);}},
            {T_DO, [&](Token token){createDoExpression(token);}},
            {T_DONE, [&](Token token){createDoneExpression(token);}},
            {T_DOT, [&](Token token){createFieldReferenceExpression(token);}},
            {T_DUMMY_ARG, [&](Token token){createVarNameExpression(token);}},
            {T_REGISTER, [&](Token token){createFieldNameExpression(token);}},
            {T_PATH, [&](Token token){createFieldNameExpression(token);}},
            {T_MAIL, [&](Token token){createFieldNameExpression(token);}},
            {T_RUN, [&](Token token){createFieldNameExpression(token);}},
            {T_RUN_SCRIPT, [&](Token token){createFieldNameExpression(token);}},
            {T_RAPORT_DIR, [&](Token token){createFieldNameExpression(token);}},
            {T_RAPORT_TYPE, [&](Token token){createFieldNameExpression(token);}},
            {T_SEND_RAPORT, [&](Token token){createFieldNameExpression(token);}},
            {T_BACKUP, [&](Token token){createFieldNameExpression(token);}},
            {T_CHECK_SYSTEM, [&](Token token){createFieldNameExpression(token);}},
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
            {T_SPECIFIER, {3,2}},
            {T_BOOLEAN_OR, {4,3}},
            {T_BOOLEAN_AND, {5,4}},
            {T_ASSIGN_OPERATOR,{6,5}},
            {T_DOT, {7,6}},
            {T_BOOLEAN_OPERATOR, {7,6}},
            {T_ADD_OPERATOR, {8,7}},
            {T_MULT_OPERATOR, {9,8}},
            {T_FUNCTION_NAME, {10,9}},
            {T_FUNCTION_CALL, {10,9}},
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
    bool tryToHandleEmbeddedExpression();
    bool tryToHandleEmbeddedDo();
    bool tryToHandleEmbeddedDone();
    bool tryToHandleNextLine();
    bool tryToHandleOperator();
    Token seeNextToken();
    std::shared_ptr<RootExpression> generatePostfixRepresentation();
    std::shared_ptr<RootExpression> generateTree();

    bool isSpecial() {
        auto type = token.getType();
        return type == T_INT_NUM || type == T_USER_DEFINED_NAME ||
               type == T_REAL_NUM || type == T_STRING || type == T_SEND_RAPORT ||
               type == T_BACKUP || type == T_RUN_SCRIPT || type == T_CHECK_SYSTEM ||
               type == T_NEXT_LINE || type == T_END || type == T_WHILE ||
               type == T_IF || type == T_ELSE || type == T_FUNCTION_NAME;
    }

    bool isOperand() {
        auto type = token.getType();
        return type == T_INT_NUM || type == T_USER_DEFINED_NAME ||
               type == T_REAL_NUM || type == T_STRING || type == T_SEND_RAPORT ||
               type == T_BACKUP || type == T_RUN_SCRIPT || type == T_CHECK_SYSTEM;
    }

public:
    Parser(std::shared_ptr<Scanner> scanner){
        this->scanner = scanner;
        mainRoot = std::make_unique<FileExpression>();
    };
    void analyzeTree();
    void parse();
};


#endif //TKOM_PARSER_H
