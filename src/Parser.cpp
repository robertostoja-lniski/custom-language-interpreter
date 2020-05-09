//
// Created by robert on 06.05.2020.
//

#include "../include/Parser.h"

#include <utility>

void Parser::parseToken(Token tokenToParse) {

    try {
        std::cout << "parsing " <<  tokenToParse << '\n';
        if(tryToBuildFunctionCall(tokenToParse) || tryToBuildExpression(tokenToParse)) {
            return;
        }
    } catch(std::exception& e) {
        std::cerr << "Error in syntax\n";
    }
}
bool Parser::tryToBuildExpression(Token tokenToParse) {
    converter->generatePostfixRepresentation(tokenToParse);
    return true;
}
void Parser::createIntExpression(Token token) {
    int numericValue = std::stoi(token.getValue());
    auto expression = std::make_unique<IntExpression>(numericValue);
    recentExpressions.push(std::move(expression));
}
void Parser::createFloatExpression(Token token) {
    double realValue = std::stod(token.getValue());
    auto expression = std::make_unique<FloatExpression>(realValue);
    recentExpressions.push(std::move(expression));
}
void Parser::createVarNameExpression(Token token) {
    std::string name = token.getValue();
    auto expression = std::make_unique<VarNameExpression>(name);
    recentExpressions.push(std::move(expression));
}
void Parser::addDoubleArgsExpression(std::unique_ptr<DoubleArgsExpression> doubleArgsExpression) {
    auto right = recentExpressions.top();
    recentExpressions.pop();
    auto left = recentExpressions.top();
    recentExpressions.pop();

    doubleArgsExpression->left = left;
    doubleArgsExpression->right = right;

    recentExpressions.push(std::move(doubleArgsExpression));
}
void Parser::createAdditionExpression(Token token) {
      auto expression = std::make_unique<AdditionExpression>(token.getValue());
      addDoubleArgsExpression(std::move(expression));
}
void Parser::createMultExpression(Token token) {
    auto expression = std::make_unique<MultiplyExpression>();
    addDoubleArgsExpression(std::move(expression));
}
void Parser::createBooleanOperatorExpression(Token token) {
    auto value = token.getValue();
    auto expression = std::make_unique<BooleanOperatorExpression>(value);
    addDoubleArgsExpression(std::move(expression));
}
void Parser::createAssignExpression(Token token) {
    auto expression = std::make_unique<AssignExpression>();
    addDoubleArgsExpression(std::move(expression));
}
void Parser::createBooleanAndExpression(Token token) {
    auto expression = std::make_unique<BooleanAndExpression>();
    addDoubleArgsExpression(std::move(expression));
}
void Parser::createBooleanOrExpression(Token token) {
    auto expression = std::make_unique<BooleanOrExpression>();
    addDoubleArgsExpression(std::move(expression));
}
void Parser::createFunctionCallExpression(Token token) {
    auto funcExpr = std::make_unique<FunctionExpression>();
    funcExpr->left = std::make_shared<VarNameExpression>(token.getValue());

    if(recentExpressions.empty()) {
        funcExpr->right = nullptr;
    } else {
        auto right = recentExpressions.top();
        recentExpressions.pop();
        funcExpr->right = right;
    }

    recentExpressions.push(std::move(funcExpr));
}
void Parser::generateTree() {

    auto postfixCopy = converter->getPostfixRepresentation();
    if(postfixCopy.empty()) {
        throw std::runtime_error("Tried to build tree from empty postfix");
    }

    while(!postfixCopy.empty()) {
        auto currentToken = postfixCopy.front();
        auto func = tokensToNode[currentToken->getType()];
        func(*currentToken);
        postfixCopy.pop();
    }
    root = std::make_shared<RootExpression>();
    root->next = recentExpressions.top();
    recentExpressions.pop();
}

void Parser::analyzeTree() {
    ExpressionVisitor expressionVisitor;
    expressionVisitor.visit(root.get());
}

bool Parser::tryToBuildFunctionCall(Token token) {
    return converter->tryToGenerateFunctionCall(token);
}

void Parser::createSemiconExpression(Token token) {
    auto expression = std::make_unique<FunctionArgExpression>();
    addDoubleArgsExpression(std::move(expression));
}



