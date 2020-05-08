//
// Created by robert on 06.05.2020.
//

#include "../include/Parser.h"

#include <utility>

void Parser::parseToken(Token tokenToParse) {

    try {
        std::cout << "parsing " <<  tokenToParse << '\n';
        tryToBuildExpression(std::move(tokenToParse));
    } catch(std::exception& e) {
        std::cerr << "Error in syntax\n";
    }
}

void Parser::tryToBuildExpression(Token tokenToParse) {
    converter->generatePostfixRepresentation(std::move(tokenToParse));
}

void Parser::createAndAddIntExpression(Token token) {
    int numericValue = std::stoi(token.getValue());
    auto expression = std::make_unique<IntExpression>(numericValue);
    recentExpressions.push(std::move(expression));
}

void Parser::createAndAddFloatExpression(Token token) {
    double realValue = std::stod(token.getValue());
    auto expression = std::make_unique<FloatExpression>(realValue);
    recentExpressions.push(std::move(expression));
}

void Parser::createAndAddVarNameExpression(Token token) {
    std::string name = token.getValue();
    auto expression = std::make_unique<VarNameExpression>(name);
    recentExpressions.push(std::move(expression));
}

void Parser::addDoubleArgsExpression(std::unique_ptr<DoubleArgsExpression> doubleArgsExpression) {
    auto left = recentExpressions.top();
    recentExpressions.pop();
    auto right = recentExpressions.top();
    recentExpressions.pop();

    doubleArgsExpression->left = left;
    doubleArgsExpression->right = right;

    recentExpressions.push(std::move(doubleArgsExpression));
}

void Parser::createAndAddAdditionExpression(Token token) {
      auto expression = std::make_unique<AdditionExpression>(token.getValue());
      addDoubleArgsExpression(std::move(expression));
}

void Parser::createAndAddMultExpression(Token token) {
    auto expression = std::make_unique<MultiplyExpression>();
    addDoubleArgsExpression(std::move(expression));
}

void Parser::createAndAddAssignExpression(Token token) {
    auto expression = std::make_unique<AssignExpression>();
    addDoubleArgsExpression(std::move(expression));
}

void Parser::generateTree() {

    auto postfixCopy = converter->getPostfixRepresentation();
    if(postfixCopy.empty()) {
        throw std::runtime_error("Tried to build tree from empty postfix");
    }

    while(!postfixCopy.empty()) {
        auto currentToken = postfixCopy.front();
        auto func = tokensToNode[currentToken.getType()];
        func(currentToken);
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

