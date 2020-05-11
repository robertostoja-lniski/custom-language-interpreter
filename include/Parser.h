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
#include "DeclarationReader.h"
#include "Visitor.h"
#include "Scanner.h"

using boost::lexical_cast;

class Parser {
private:

    //tmp just for one subtree
    std::shared_ptr<Scanner> scanner;
    std::unique_ptr<RepresentationConverter> converter;
    std::unique_ptr<DeclarationReader> declarationReader;
    // right not used
    std::unique_ptr<FileExpression> mainRoot;
    std::stack <std::shared_ptr<Expression>> recentExpressions;
    void addDeclarationsToTree(std::shared_ptr<RootExpression> declaration);
    bool tryToBuildExpression(Token token);
    bool tryToBuildDeclaration(Token token);
    void assignTreeToRoot();
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

    Token getTokenValFromScanner();

    std::map<Type, std::function<void(Token)>> tokensToNode {
            {T_INT_NUM, [&](Token token){createIntExpression(token);}},
            {T_REAL_NUM, [&](Token token){createFloatExpression(token);}},
            {T_ADD_OPERATOR, [&](Token token){createAdditionExpression(token);}},
            {T_MULT_OPERATOR, [&](Token token){createMultExpression(token);}},
            {T_BOOLEAN_OPERATOR, [&](Token token) {createBooleanOperatorExpression(token);}},
            {T_BOOLEAN_AND, [&](Token token){createBooleanAndExpression(token);}},
            {T_SEMICON, [&](Token token){createSemiconExpression(token);}},
            {T_BOOLEAN_OR, [&](Token token){createBooleanOrExpression(token);}},
            {T_ASSIGN_OPERATOR, [&](Token token){createAssignExpression(token);}},
            {T_USER_DEFINED_NAME, [&](Token token){createVarNameExpression(token);}},
            {T_FUNCTION_NAME, [&](Token token){createFunctionCallExpression(token);}},
            {T_NO_ARG_FUNCTION_NAME, [&](Token token){createNoArgFunctionExpression(token);}},
            {T_NEXT_LINE, [&](Token token){createNextLineExpression(token);}},
            {T_WHILE, [&](Token token){createWhileExpression(token);}},
            {T_IF, [&](Token token){createIfExpression(token);}},
            {T_ELSE, [&](Token token){createElseExpression(token);}},
            {T_FOR, [&](Token token){createForExpression(token);}},
            {T_DO, [&](Token token){createDoExpression(token);}},
            {T_DONE, [&](Token token){createDoneExpression(token);}},
            {T_DOT, [&](Token token){createFieldReferenceExpression(token);}},
            {T_DUMMY_ARG, [&](Token token){createVarNameExpression(token);}},
    };


public:
    void parseToken(Token tokenToParse);
    Parser(std::shared_ptr<Scanner> scanner){
        this->scanner = scanner;
        converter = std::make_unique<RepresentationConverter>(scanner);
        declarationReader = std::make_unique<DeclarationReader>(scanner);
        mainRoot = std::make_unique<FileExpression>();
    };
    void generateTree();
    void analyzeTree();
    void parse();
};


#endif //TKOM_PARSER_H
