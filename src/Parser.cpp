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
        if(tryToBuildDeclaration(tokenToParse)) {
            return;
        }
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
void Parser::createTypeDeclarationExpression(Token token) {
//    // if no value initialisation
    if(recentExpressions.size() == 1) {
        auto specifier = std::make_unique<TypeSpecifierExpression>(token.getValue());
        specifier->left = recentExpressions.top();
        recentExpressions.pop();
        recentExpressions.push(std::move(specifier));
        return;
    }
//
//    // if single value initialisation
//    if(recentExpressions.size() == 3) {
//        auto specifier = std::make_unique<TypeSpecifierExpression>(token.getValue());
//        auto assignment = recentExpressions.top();
//        specifier->left = assignment;
//        recentExpressions.push(std::move(specifier));
//        return;
//    }

    // if collection initialisation
    // f.e int a = 3 4 5
    std::string name = token.getValue();
    // handle previous expr
    auto doubleExpr = recentExpressions.top();
    recentExpressions.pop();

    auto values = std::dynamic_pointer_cast<DoubleArgsExpression>(doubleExpr);
    auto initialisationBody = std::make_shared<BodyExpression>();
    initialisationBody->statements.push_back(values->right);
    initialisationBody->statements.push_back(values->left);

    while(recentExpressions.size() > 1) {
        initialisationBody->statements.push_back(recentExpressions.top());
        recentExpressions.pop();
    }

    auto specifier = std::make_shared<TypeSpecifierExpression>(token.getValue());
    // set varname to left
    specifier->left = recentExpressions.top();
    recentExpressions.pop();
    specifier->right = initialisationBody;
    recentExpressions.push(specifier);
}
void Parser::createForExpression(Token token) {
    auto forExpr = std::make_unique<ForExpression>();
    auto collection = recentExpressions.top();
    recentExpressions.pop();
    auto iter = recentExpressions.top();
    recentExpressions.pop();
    forExpr->left = iter;
    forExpr->collectionName = collection;
    recentExpressions.push(std::move(forExpr));
}

void Parser::createElseExpression(Token token) {
    recentExpressions.push(std::move(std::make_shared<ElseExpression>()));
}

void Parser::createIfExpression(Token token) {

    auto ifExpr = std::make_shared<IfExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    ifExpr->left = cond;
    recentExpressions.size();
    recentExpressions.push(std::move(ifExpr));
}

void Parser::createWhileExpression(Token token) {
    auto whileExpr = std::make_shared<WhileExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    whileExpr->left = cond;
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
    // if if/while/for body is at stack top
    // do not take it out.
    assignTreeToRoot();
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
        roots.pop_back();
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
//    if(recentExpressions.size())
    recentExpressions.push(std::make_shared<NoArgFunctionExpression>(name));
}

void Parser::transformTokenIntoTreeNode(std::shared_ptr<Token> token) {
    auto tokenType = token->getType();
    auto handler = tokensToNode[tokenType];
    handler(*token);
}

void Parser::assignTreeToRoot() {
    while(!recentExpressions.empty()) {
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = recentExpressions.top();
        roots.push_back(newRoot);
        recentExpressions.pop();
    }
}

void Parser::assignTreeToCurrentBody() {
    auto currentTree = recentExpressions.top();
    auto currentBody = embeddedBodies.top();
    currentBody->statements.push_back(currentTree);
    recentExpressions.pop();
    embeddedBodies.pop();
}

bool Parser::tryToBuildConditionConstruction(Token token) {
    return converter->tryToGenerateCondition(token);
}

void Parser::createDoExpression(Token token) {
    auto condBody = std::make_shared<DoExpression>();
    recentExpressions.push(condBody);
}

bool Parser::isCondExpression(std::shared_ptr<Expression> expr) {
    auto rawExpr = expr.get();
    return dynamic_cast<DoExpression *>(rawExpr);
}
void Parser::createDoneExpression(Token token) {

    auto condBody = std::make_shared<BodyExpression>();
    if(recentExpressions.empty()) {
            auto upperRoot = roots.back()->expr;
            while(!std::dynamic_pointer_cast<DoExpression>(upperRoot)) {
                condBody->statements.push_front(upperRoot);
                roots.pop_back();
                upperRoot = roots.back()->expr;
            }
            // pop Do mark
            roots.pop_back();
            auto condExpr = roots.back()->expr;
            auto isElse = std::dynamic_pointer_cast<ElseExpression>(condExpr);
            auto isDeclaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(condExpr);
            if(isElse) {
                roots.pop_back();
                auto condExpr = roots.back()->expr;
                auto condExprAsDoubleArg = std::dynamic_pointer_cast<IfExpression>(condExpr);
                condExprAsDoubleArg->elseCondition = condBody;
            } else if (isDeclaration) {
                auto declaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(condExpr);
                auto declarationStatements = std::dynamic_pointer_cast<BodyExpression>(declaration->right);
                declarationStatements->statements.push_back(condBody);
            } else {
                auto condExprAsDoubleArg = std::dynamic_pointer_cast<DoubleArgsExpression>(condExpr);
                condExprAsDoubleArg->right = condBody;
            }

            return;
    }

    auto currentExpr = recentExpressions.top();
    if(currentExpr == nullptr) {
        throw std::runtime_error("Single done.");
    }

    while(!isCondExpression(currentExpr)) {
        if(recentExpressions.empty()) {
            throw std::runtime_error("Done without do.");
        }
        condBody->statements.push_back(currentExpr);
        recentExpressions.pop();
        currentExpr = recentExpressions.top();
    }
    recentExpressions.pop();
    currentExpr = recentExpressions.top();
    // now we have to set cond to have right ptr to body
    if(currentExpr == nullptr) {
        throw std::runtime_error("Single done.");
    }
    auto condExpr = std::dynamic_pointer_cast<DoubleArgsExpression>(currentExpr);
    condExpr->right = condBody;
}

bool Parser::tryToBuildDeclaration(Token token) {
    if(token.getType() == T_SPECIFIER) {
        auto specifierExpr = std::make_shared<TypeSpecifierExpression>(token.getValue());
        scanner->getNextToken();
        scanner->readToken();
        auto shouldBeIdentToken = scanner->getTokenValue();
        if(shouldBeIdentToken.getType() != T_USER_DEFINED_NAME) {
            throw std::runtime_error("Type specifier without ident");
        }

        // user name
        specifierExpr->left = std::make_shared<VarNameExpression>(shouldBeIdentToken.getValue());

        // function
        scanner->getNextToken();
        scanner->readToken();
        auto nextToken = scanner->getTokenValue();

        if(nextToken.getType() == T_OPENING_PARENTHESIS) {
            // store args in right ptr
            auto argBlock = std::make_shared<BodyExpression>();
            while(nextToken.getType() != T_CLOSING_PARENTHESIS || nextToken.getType() != T_NEXT_LINE) {

                scanner->getNextToken();
                scanner->readToken();
                nextToken = scanner->getTokenValue();

                if(nextToken.getType() == T_CLOSING_PARENTHESIS) {
                    specifierExpr->right = argBlock;
                    auto newRoot = std::make_shared<RootExpression>();
                    newRoot->expr = specifierExpr;
                    roots.push_back(newRoot);
                    return true;
                }
                if(nextToken.getType() == T_SEMICON) {
                    continue;
                }

                auto currentArg = std::make_shared<TypeSpecifierExpression>(nextToken.getValue());

                scanner->getNextToken();
                scanner->readToken();
                nextToken = scanner->getTokenValue();

                auto currentArgName = std::make_shared<VarNameExpression>(nextToken.getValue());
                currentArg->left = currentArgName;

                argBlock->statements.push_back(currentArg);
            }
        } else {
            auto newRoot = std::make_shared<RootExpression>();
            newRoot->expr = specifierExpr;
            roots.push_back(newRoot);
            parseToken(nextToken);
        }
    }
    return false;
}
