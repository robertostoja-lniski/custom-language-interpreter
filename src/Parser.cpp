//
// Created by robert on 06.05.2020.
//

#include "../include/Parser.h"

#include <utility>
void Parser::parse() {
    token = getTokenValFromScanner();
    std::shared_ptr<RootExpression> decl;
    std::shared_ptr<RootExpression> statement;

    if(token.getType() == T_END) {
        return;
    }
    while((decl = tryToBuildDeclaration()) != nullptr) {
        if(decl) {
            addDeclarationsToTree(decl);
        }
    }
    if(tryToBuildExpression(this->token)) {

    }
    parse();

}
//void Parser::parseToken(Token tokenToParse) {
//    if(tokenToParse.getType() == T_NOT_DEFINED_YET) {
//        return;
//    }
//    try {
//        std::cout << "parsing " <<  tokenToParse << '\n';
//        if(tryToBuildDeclarationLegacy()
//           || tryToBuildExpression(tokenToParse)) {
//            return;
//        }
//    } catch(std::exception& e) {
//        std::cerr << "Error in syntax\n";
//    }
//}
//void Parser::parseProgram() {
//    token = getTokenValFromScanner();
//    std::shared_ptr<RootExpression> decl;
//    std::shared_ptr<RootExpression> statement;
//    while(decl = tryToBuildDeclaration() ) {
//        if(decl) {
//            addDeclarationsToTree(decl);
//        }
//    }
//}

bool Parser::tryToBuildDeclarationLegacy() {
    auto buildDeclaration = tryToBuildDeclaration();
    if(buildDeclaration) {
        addDeclarationsToTree(buildDeclaration);
    }
}

std::shared_ptr<RootExpression> Parser::tryToBuildDeclaration() {
    if(token.getType() == T_SPECIFIER) {
        auto specifierExpr = getExpressionWithAssignedSpecifier();
        token = getTokenValFromScanner();
        if(token.getType() == T_END || token.getType() == T_NEXT_LINE) {
            return nullptr;
        }

        if(token.getType() == T_OPENING_PARENTHESIS) {
            auto body = getParamsAsManyDeclarations();
            specifierExpr->right = body;
        }
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = specifierExpr;
        return newRoot;
    }
    return nullptr;
}

std::shared_ptr<TypeSpecifierExpression> Parser::getExpressionWithAssignedSpecifier() {
    auto specifierExpr = std::make_shared<TypeSpecifierExpression>(token.getValue());
    auto shouldBeIdentToken = getTokenValFromScanner();
    if(shouldBeIdentToken.getType() != T_USER_DEFINED_NAME || shouldBeIdentToken.getValue() == "$") {
        throw std::runtime_error("Type specifier without ident");
    }
    specifierExpr->left = std::make_shared<VarNameExpression>(shouldBeIdentToken.getValue());
    return specifierExpr;
}
std::shared_ptr<BodyExpression> Parser::getParamsAsManyDeclarations() {
    auto argBlock = std::make_shared<BodyExpression>();
    while(token.getType() != T_CLOSING_PARENTHESIS) {

        token = getTokenValFromScanner();
        if(token.getType() == T_CLOSING_PARENTHESIS) {
            token = getTokenValFromScanner();
            return argBlock;
        }
        if(token.getType() == T_SEMICON) {
            continue;
        }

        auto currentArg = std::make_shared<TypeSpecifierExpression>(token.getValue());
        token = getTokenValFromScanner();
        auto currentArgName = std::make_shared<VarNameExpression>(token.getValue());

        currentArg->left = currentArgName;
        argBlock->statements.push_back(currentArg);
    }
    return nullptr;
}
bool Parser::tryToBuildExpression(Token infixToken) {
    return converter->generatePostfixRepresentation(infixToken);
}
void Parser::createIntExpression() {
    int numericValue = std::stoi(token.getValue());
    recentExpressions.push(std::make_shared<IntExpression>(numericValue));
}
void Parser::createFloatExpression() {
    double realValue = std::stod(token.getValue());
    recentExpressions.push(std::make_shared<FloatExpression>(realValue));
}
void Parser::createVarNameExpression() {
    std::string name = token.getValue();
    recentExpressions.push(std::make_shared<VarNameExpression>(name));
}
void Parser::createForExpression() {
    auto forExpr = std::make_unique<ForExpression>();

    auto collection = recentExpressions.top();
    recentExpressions.pop();
    auto iter = recentExpressions.top();
    recentExpressions.pop();

    forExpr->left = iter;
    forExpr->collectionName = collection;
    recentExpressions.push(std::move(forExpr));
}

void Parser::createElseExpression() {
    recentExpressions.push(std::move(std::make_shared<ElseExpression>()));
}

void Parser::createIfExpression() {
    auto ifExpr = std::make_shared<IfExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    ifExpr->left = cond;
    recentExpressions.size();
    recentExpressions.push(std::move(ifExpr));
}

void Parser::createWhileExpression() {
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
void Parser::createAdditionExpression() {
    setDoubleArgsExpr(std::make_shared<AdditionExpression>(token.getValue()));
}
void Parser::createMultExpression() {
    setDoubleArgsExpr(std::make_shared<MultiplyExpression>());
}
void Parser::createBooleanOperatorExpression() {
    auto value = token.getValue();
    setDoubleArgsExpr(std::make_shared<BooleanOperatorExpression>(value));
}
void Parser::createAssignExpression() {
    setDoubleArgsExpr(std::make_unique<AssignExpression>());
}
void Parser::createBooleanAndExpression() {
    setDoubleArgsExpr(std::make_unique<BooleanAndExpression>());
}
void Parser::createBooleanOrExpression() {
    setDoubleArgsExpr(std::make_unique<BooleanOrExpression>());
}
void Parser::createNextLineExpression() {
    assignTreeToRoot();
}
void Parser::createFunctionCallExpression() {
    auto funcExpr = std::make_unique<FunctionExpression>();
    // get function name
    funcExpr->left = std::make_shared<VarNameExpression>(token.getValue());

    auto nextArg = recentExpressions.top();
    recentExpressions.pop();
    funcExpr->right = nextArg;

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
    expressionVisitor.visit(mainRoot.get());
}

void Parser::createSemiconExpression() {
    auto newArgs = std::make_shared<FunctionArgExpression>();

    if(!recentExpressions.empty()) {
        newArgs->left = recentExpressions.top();
        recentExpressions.pop();
        // maybe few arguments can be joined

        if(!recentExpressions.empty()) {
            auto previousExpr = recentExpressions.top();
            auto isFuncArgExpr = std::dynamic_pointer_cast<FunctionArgExpression>(previousExpr);
            if(isFuncArgExpr) {
                newArgs->right = previousExpr;
                recentExpressions.pop();
            }
        }
    }
    recentExpressions.push(newArgs);
}

void Parser::createNoArgFunctionExpression() {
    std::string name = token.getValue();
    recentExpressions.push(std::make_shared<NoArgFunctionExpression>(name));
}

void Parser::transformTokenIntoTreeNode(std::shared_ptr<Token> postfixToken) {
    token = *postfixToken;
    auto tokenType = postfixToken->getType();
    auto handler = tokensToNode[tokenType];
    handler();
}

void Parser::assignTreeToRoot() {
    while(!recentExpressions.empty()) {
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = recentExpressions.top();
        mainRoot->roots.push_back(newRoot);
        recentExpressions.pop();
    }
}

void Parser::createDoExpression() {
    auto condBody = std::make_shared<DoExpression>();
    recentExpressions.push(condBody);
}

void Parser::joinUpperStatementsUntilDoFound(std::shared_ptr<BodyExpression> condBody){
    auto upperRoot = mainRoot->roots.back()->expr;
    while(!std::dynamic_pointer_cast<DoExpression>(upperRoot)) {
        condBody->statements.push_front(upperRoot);
        mainRoot->roots.pop_back();
        upperRoot = mainRoot->roots.back()->expr;
    }
    mainRoot->roots.pop_back();
}
void Parser::assignBodyToUpperElse(std::shared_ptr<BodyExpression> condBody) {
    mainRoot->roots.pop_back();
    auto condExpr = mainRoot->roots.back()->expr;
    auto condExprAsDoubleArg = std::dynamic_pointer_cast<IfExpression>(condExpr);
    condExprAsDoubleArg->elseCondition = condBody;
}
void Parser::assignBodyToUpperDeclaration(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr) {
    auto declaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(condExpr);
    auto declarationStatements = std::dynamic_pointer_cast<BodyExpression>(declaration->right);
    declarationStatements->statements.push_back(condBody);
}
void Parser::assignBodyToUpperAnyExpression(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr) {
    auto condExprAsDoubleArg = std::dynamic_pointer_cast<DoubleArgsExpression>(condExpr);
    condExprAsDoubleArg->right = condBody;
}
void Parser::assignBodyToUpperExpression(std::shared_ptr<BodyExpression> condBody) {
    auto condExpr = mainRoot->roots.back()->expr;
    auto isElse = std::dynamic_pointer_cast<ElseExpression>(condExpr);
    auto isDeclaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(condExpr);
    if(isElse) {
        assignBodyToUpperElse(condBody);
    } else if (isDeclaration) {
        assignBodyToUpperDeclaration(condBody, condExpr);
    } else {
        assignBodyToUpperAnyExpression(condBody, condExpr);
    }
}
void Parser::createDoneExpression() {
    auto condBody = std::make_shared<BodyExpression>();
    joinUpperStatementsUntilDoFound(condBody);
    assignBodyToUpperExpression(condBody);
}

void Parser::addDeclarationsToTree(std::shared_ptr<RootExpression> declaration) {
    mainRoot->roots.push_back(std::move(declaration));
}

Token Parser::getTokenValFromScanner() {
    if(!scanner) {
        throw std::runtime_error("No scanner pointed");
    }
    scanner->getNextToken();
    scanner->readToken();
    return scanner->getTokenValue();
}

void Parser::createFieldReferenceExpression() {
    setDoubleArgsExpr(std::make_unique<FieldReferenceExpression>());
}
