//
// Created by robert on 06.05.2020.
//

#include "../include/Parser.h"

#include <utility>

void Parser::parseToken(Token tokenToParse) {
    if(tokenToParse.getType() == T_NOT_DEFINED_YET) {
        return;
    }
    try {
        std::cout << "parsing " <<  tokenToParse << '\n';
        if(tryToBuildFunctionCall(tokenToParse)
            || tryToBuildConditionConstruction(tokenToParse)
            || tryToBuildExpression(tokenToParse)) {
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
    recentExpressions.push(std::make_shared<IntExpression>(numericValue));
}
void Parser::createFloatExpression(Token token) {
    double realValue = std::stod(token.getValue());
    recentExpressions.push(std::make_shared<FloatExpression>(realValue));
}
void Parser::createVarNameExpression(Token token) {
    std::string name = token.getValue();
    recentExpressions.push(std::make_shared<VarNameExpression>(name));
}
void Parser::createForExpression(Token token) {

}

void Parser::createIfExpression(Token token) {
    //subtle changes between if and while, maybe
    //will be remove to remote function
    //but there should be one upper class for while
    //or maybe while can iherit from If
    //but is really every while and if?
    auto ifExpr = std::make_shared<WhileExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    ifExpr->condition = cond;
    recentExpressions.size();
    recentExpressions.push(std::move(ifExpr));
}

void Parser::createWhileExpression(Token token) {
    auto whileExpr = std::make_shared<WhileExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    whileExpr->condition = cond;
    recentExpressions.size();
    recentExpressions.push(std::move(whileExpr));
}
void Parser::setDoubleArgsExpr(std::shared_ptr<DoubleArgsExpression> doubleArgsExpression) {
    if(recentExpressions.size() < 2) {
        throw std::runtime_error("Not enough args for operation");
    }
    auto right = recentExpressions.top();
    recentExpressions.pop();
    auto left = recentExpressions.top();
    recentExpressions.pop();

    doubleArgsExpression->left = left;
    doubleArgsExpression->right = right;

    recentExpressions.push(std::move(doubleArgsExpression));
}
void Parser::createAdditionExpression(Token token) {
    setDoubleArgsExpr(std::make_shared<AdditionExpression>(token.getValue()));
}
void Parser::createMultExpression(Token token) {
    setDoubleArgsExpr(std::make_shared<MultiplyExpression>());
}
void Parser::createBooleanOperatorExpression(Token token) {
    auto value = token.getValue();
    setDoubleArgsExpr(std::make_shared<BooleanOperatorExpression>(value));
}
void Parser::createAssignExpression(Token token) {
    setDoubleArgsExpr(std::make_unique<AssignExpression>());
}
void Parser::createBooleanAndExpression(Token token) {
    setDoubleArgsExpr(std::make_unique<BooleanAndExpression>());
}
void Parser::createBooleanOrExpression(Token token) {
    setDoubleArgsExpr(std::make_unique<BooleanOrExpression>());
}
void Parser::createNextLineExpression(Token token) {
    if(!recentExpressions.empty()) {
        assignTreeToRoot();
    }
}
void Parser::createFunctionCallExpression(Token token) {
    auto funcExpr = std::make_unique<FunctionExpression>();
    funcExpr->left = std::make_shared<VarNameExpression>(token.getValue());

    if(recentExpressions.empty()) {
        funcExpr->right = nullptr;
    } else {
        auto nextArg = recentExpressions.top();
        recentExpressions.pop();
        funcExpr->right = nextArg;
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
        transformTokenIntoTreeNode(currentToken);
        postfixCopy.pop_front();
    }
    assignTreeToRoot();
}
void Parser::analyzeTree() {
    ExpressionVisitor expressionVisitor;
    while(!roots.empty()) {
        auto currentRoot = roots.front();
        expressionVisitor.visit(currentRoot.get());
        roots.pop();
    }
}

bool Parser::tryToBuildFunctionCall(Token token) {
    return converter->tryToGenerateFunctionCall(token);
}
void Parser::createSemiconExpression(Token token) {
    auto newArgs = std::make_shared<FunctionArgExpression>();

    if(recentExpressions.size() < 2) {
        throw std::runtime_error("Not enough function args");
    }
    newArgs->right = recentExpressions.top();
    recentExpressions.pop();
    newArgs->left = recentExpressions.top();
    recentExpressions.pop();

    recentExpressions.push(newArgs);
}

void Parser::createNoArgFunctionExpression(Token token) {
    std::string name = token.getValue();
    recentExpressions.push(std::make_shared<NoArgFunctionExpression>(name));
}

void Parser::transformTokenIntoTreeNode(std::shared_ptr<Token> token) {
    auto tokenType = token->getType();
    auto handler = tokensToNode[tokenType];
    handler(*token);
}

void Parser::assignTreeToRoot() {
    auto newRoot = std::make_shared<RootExpression>();
    newRoot->left = recentExpressions.top();
    roots.push(newRoot);
    recentExpressions.pop();
}

bool Parser::tryToBuildConditionConstruction(Token token) {
    return converter->tryToGenerateCondition(token);
}




