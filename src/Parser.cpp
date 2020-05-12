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
    if(generatePostfixRepresentation(token)) {

    }
    parse();

}

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
    while(!postfixRepresentation.empty()) {
        auto currentToken = postfixRepresentation.front();
        transformTokenIntoTreeNode(currentToken);
        postfixRepresentation.pop_front();
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

bool Parser::tryToHandleSpecialToken() {

    if(!token.isCondition() && !token.isOperator() && !token.isFunction()) {
        return false;
    }
    auto currentType = token.getType();

    if(operators.empty() || priorities[currentType].out > priorities[operators.top()->getType()].in) {
        operators.push(std::make_shared<Token>(token));
    } else {
        while(!operators.empty() && priorities[currentType].out < priorities[operators.top()->getType()].in) {
            postfixRepresentation.push_back(operators.top());
            operators.pop();
        }
        operators.push(std::make_shared<Token>(token));
    }
    return true;
}
bool Parser::tryToHandleEmbeddedExpression() {
    if(operators.empty() || token.getType()!=T_CLOSING_PARENTHESIS) {
        return false;
    }
    while(operators.top()->getType() != T_OPENING_PARENTHESIS) {
        postfixRepresentation.push_back(operators.top());
        operators.pop();

        if(operators.empty()) {
            throw std::runtime_error("Cannot find opening parenthesis");
        }
    }
    operators.pop();
    return true;
}
bool Parser::tryToHandleEmbeddedDo() {
    if(token.getType() != T_DO) {
        return false;
    }
    if(operators.empty()) {
        postfixRepresentation.push_back(std::make_shared<Token>(token));
        return true;
    }

    auto cond = operators.top();
    postfixRepresentation.push_back(cond);
    operators.pop();
    postfixRepresentation.push_back(std::make_shared<Token>(token));
    return true;
}
bool Parser::tryToHandleEmbeddedDone() {
    if(token.getType() != T_DONE) {
        return false;
    }
    while(!operators.empty()) {
        auto cond = operators.top();
        postfixRepresentation.push_back(cond);
        operators.pop();
    }
    postfixRepresentation.push_back(std::make_shared<Token>(token));
    return true;
}
void Parser::finalize() {
    // ugly as hell
    while(!operators.empty()) {
        postfixRepresentation.push_back(operators.top());
        operators.pop();
    }
}

bool Parser::tryToGenerateCondition() {
    // treat conditions as operators
    if(token.isCondition()) {
        tryToHandleSpecialToken();
        return true;
    }
    return false;
}
bool Parser::tryToHandleNextLine() {
    if(token.getType() != T_NEXT_LINE) {
        return false;
    }
    finalize();
    postfixRepresentation.push_back(std::make_unique<Token>(token));
    return true;
}
bool Parser::tryToHandleOperand() {
    if (token.isOperand()) {
        // maybe it is a function name
        if(token.getType() == T_USER_DEFINED_NAME) {
            // check if next is (
            auto firstTokenForward = getTokenValFromScanner();
            if(firstTokenForward.getType() == T_OPENING_PARENTHESIS) {

                // now maybe it is non arg function
                auto secondTokenForward = getTokenValFromScanner();
                if(secondTokenForward.getType() == T_CLOSING_PARENTHESIS) {
                    token.setType(T_NO_ARG_FUNCTION_NAME);
                    postfixRepresentation.push_back(std::make_unique<Token>(token));
                    // if it is no arg, we do not have to add ( and ) to operators
                    // they will be removed by the algorithm
                    return true;
                } else {
                    token.setType(T_FUNCTION_NAME);
                    // if not we have to handle in a row: token -> firstForward -> secondForward
                    operators.push(std::make_unique<Token>(token));
                    operators.push(std::make_unique<Token>(firstTokenForward));
                    // add , to pass information about argument num
                    Token argInfoToken = {",", T_SEMICON, 0};
                    operators.push(std::make_unique<Token>(argInfoToken));
                    return generatePostfixRepresentation(secondTokenForward);
                }

            }
            // if not, a first handle token
            postfixRepresentation.push_back(std::make_unique<Token>(token));
            // then analyze first forward
            return generatePostfixRepresentation(firstTokenForward);
        }
        // it is a simple operand
        postfixRepresentation.push_back(std::make_unique<Token>(token));
    }

    return false;
}

void Parser::printPostfix() {
    // should be iterator - to be changed soon
    auto copiedRepresentation = postfixRepresentation;
    while(!copiedRepresentation.empty()) {
        std::cout << copiedRepresentation.front()->getValue() << ' ';
        copiedRepresentation.pop_front();
    }
}
bool Parser::generatePostfixRepresentation(Token token) {
    this->token = token;
    return tryToGenerateCondition() || tryToHandleNextLine() || tryToHandleEmbeddedDo() || tryToHandleEmbeddedDone()
           || tryToHandleOperand() || tryToHandleSpecialToken() || tryToHandleEmbeddedExpression();
}
