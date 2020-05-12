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


public:
    void parseToken(Token tokenToParse);
    Parser(std::shared_ptr<Scanner> scanner){
        this->scanner = scanner;
        converter = std::make_unique<RepresentationConverter>(scanner);
        mainRoot = std::make_unique<FileExpression>();
    };
    void generateTree();
    void analyzeTree();
    void parse();
};


#endif //TKOM_PARSER_H
