//
// Created by robert on 06.05.2020.
//

#include "../include/Parser.h"

#include <utility>
void Parser::parse() {
    token = getTokenValFromScanner();
    std::shared_ptr<RootExpression> nextRoot;

    while((nextRoot = tryToBuildDeclaration()) != nullptr || (nextRoot = generatePostfixRepresentation()) != nullptr) {
        if(nextRoot->expr) {
            handleNewExpression(nextRoot);
        }
    }
}

std::unique_ptr<RootExpression> Parser::tryToBuildDeclaration() {
//
//    if(token.getType() == T_NEXT_LINE) {
//        token = getTokenValFromScanner();
//        analyzeTree();
//    }

    if(token.getType() == T_SPECIFIER) {
        auto declaredVariableOrFunctionSpecifier = token.getValue();
        token = getTokenValFromScanner();

        if(token.getType() == T_USER_DEFINED_NAME) {
            auto declaredVariableOrFunctionName = token.getValue();
            token = getTokenValFromScanner();
            if(token.getType() == T_OPENING_PARENTHESIS) {

                auto functionDeclarationArguments = tryToBuildFunctionArguments();
                auto functionDeclarationNode = std::make_unique<FunctionExpression>();
                functionDeclarationNode->specifier = declaredVariableOrFunctionSpecifier;
                functionDeclarationNode->name = declaredVariableOrFunctionName;
                functionDeclarationNode->arguments = std::move(functionDeclarationArguments);

                auto nextRoot = std::make_unique<RootExpression>();
                nextRoot->expr = std::move(functionDeclarationNode);
                token = getTokenValFromScanner();
                return nextRoot;
            }

            auto variableDeclarationNode = std::make_unique<TypeSpecifierExpression>();
            variableDeclarationNode->specifier = declaredVariableOrFunctionSpecifier;
            variableDeclarationNode->name = declaredVariableOrFunctionName;

            auto nextRoot = std::make_unique<RootExpression>();
            nextRoot->expr = std::move(variableDeclarationNode);
            token = getTokenValFromScanner();
            return nextRoot;
        }

        throw std::runtime_error("Cannot parse variable or function declaration");
    }

    if(token.getType() == T_SYSTEM_HANDLER) {
        token = getTokenValFromScanner();

        if(token.getType() == T_USER_DEFINED_NAME) {
            auto declaredSystemHandlerName = token.getValue();
            auto systemHandlerDeclarationNode = std::make_unique<SystemHandlerDeclExpression>();
            systemHandlerDeclarationNode->name = declaredSystemHandlerName;

            auto nextRoot = std::make_unique<RootExpression>();
            nextRoot->expr = std::move(systemHandlerDeclarationNode);
            token = getTokenValFromScanner();
            return nextRoot;
        }
        throw std::runtime_error("Cannot parse system handler declaration");
    }
    return nullptr;
}

std::unique_ptr<BodyExpression> Parser::tryToBuildFunctionArguments() {
    token = getTokenValFromScanner();
    if(token.getType() == T_CLOSING_PARENTHESIS) {
        // function with no args
        return nullptr;
    }
    std::string nextArgSpecifier;
    std::string nextArgName;

    auto functionDeclarationArguments = std::make_unique<BodyExpression>();

    while(token.getType() == T_SPECIFIER) {
        nextArgSpecifier = token.getValue();
        token = getTokenValFromScanner();

        if(token.getType() == T_USER_DEFINED_NAME) {
            nextArgName = token.getValue();
            token = getTokenValFromScanner();

            if(token.getType() == T_SEMICON) {
                token = getTokenValFromScanner();
                auto nextArg = std::make_unique<TypeSpecifierExpression>();
                nextArg->specifier = nextArgSpecifier;
                nextArg->name = nextArgName;
                functionDeclarationArguments->statements.push_back(std::move(nextArg));
                continue;
            }
        }
        throw std::runtime_error("Error in function declaration");
    }
    return functionDeclarationArguments;
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

void Parser::createElseExpression(Token token) {
    recentExpressions.push(std::move(std::make_shared<ElseExpression>()));
}

void Parser::createIfExpression(Token token) {
    auto ifExpr = std::make_shared<IfExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    ifExpr->mainBody = std::dynamic_pointer_cast<BodyExpression>(cond);
    recentExpressions.size();
    recentExpressions.push(std::move(ifExpr));
}

void Parser::createWhileExpression(Token token) {
    auto whileExpr = std::make_shared<WhileExpression>();
    auto cond = recentExpressions.top();
    recentExpressions.pop();

    whileExpr->body = std::dynamic_pointer_cast<BodyExpression>(cond);
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
void Parser::createFunctionCallExpression(Token token) {
    auto funcExpr = std::make_unique<FunctionCallExpression>();
    funcExpr->name = token.getValue();

    if(!recentExpressions.empty()) {
        auto nextArg = recentExpressions.top();
        recentExpressions.pop();
//        funcExpr->right = nextArg;
    }
    recentExpressions.push(std::move(funcExpr));
}
std::shared_ptr<RootExpression> Parser::generateTree() {
    while(!postfixRepresentation.empty()) {
        auto currentToken = postfixRepresentation.front();
        transformTokenIntoTreeNode(currentToken);
        postfixRepresentation.pop_front();
    }
    return assignTreeToRoot();
}
void Parser::analyzeTree() {
      evaluationVisitor.visit(mainRoot.get());
}

void Parser::createSemiconExpression(Token token) {
//    auto newArgs = std::make_shared<Body>();
//
//    if(!recentExpressions.empty()) {
//        newArgs->right = recentExpressions.top();
//        recentExpressions.pop();
//        // maybe few arguments can be joined
//
//        if(!recentExpressions.empty()) {
//            auto previousExpr = recentExpressions.top();
//                newArgs->left = previousExpr;
//                recentExpressions.pop();
//        }
//    }
//    recentExpressions.push(newArgs);
}

void Parser::transformTokenIntoTreeNode(std::shared_ptr<Token> postfixToken) {
    auto tokenType = postfixToken->getType();
    auto handler = tokensToNode[tokenType];
    handler(*postfixToken);
}

std::shared_ptr<RootExpression> Parser::assignTreeToRoot() {
    if(!recentExpressions.empty()) {
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = recentExpressions.top();
        recentExpressions.pop();
        return newRoot;
    }
    return nullptr;
}

void Parser::createDoExpression(Token token) {
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
    condExprAsDoubleArg->elseBody = condBody;
}
void Parser::assignBodyToUpperDeclaration(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr) {
//    auto declaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(condExpr);
//    auto declarationStatements = std::dynamic_pointer_cast<BodyExpression>(declaration->right);
//    declarationStatements->statements.push_back(condBody);
}
void Parser::assignBodyToUpperAnyExpression(std::shared_ptr<BodyExpression> condBody, std::shared_ptr<Expression> condExpr) {
    auto condExprAsDoubleArg = std::dynamic_pointer_cast<DoubleArgsExpression>(condExpr);
    condExprAsDoubleArg->right = condBody;
}
void Parser::assignBodyToUpperExpression(std::shared_ptr<BodyExpression> condBody) {
    auto condExpr = mainRoot->roots.back()->expr;
    auto isElse = std::dynamic_pointer_cast<ElseExpression>(condExpr);
    auto isDeclaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(condExpr);
    auto isFunction = std::dynamic_pointer_cast<FunctionExpression>(condExpr);

    if(isElse) {
        assignBodyToUpperElse(condBody);
    } else if (isDeclaration) {
        assignBodyToUpperDeclaration(condBody, condExpr);
    } else if (isFunction) {
//        isFunction->body = condBody;
    } else {
        assignBodyToUpperAnyExpression(condBody, condExpr);
    }
}
void Parser::createDoneExpression(Token token) {
    auto condBody = std::make_shared<BodyExpression>();
    joinUpperStatementsUntilDoFound(condBody);
    assignBodyToUpperExpression(condBody);
}
Token Parser::seeNextToken() {
    if(!scanner) {
        throw std::runtime_error("No scanner pointed");
    }
    return scanner->seeNextTokenValue();
}
Token Parser::getTokenValFromScanner() {
    if(!scanner) {
        throw std::runtime_error("No scanner pointed");
    }
    scanner->scan();
    auto ret = scanner->getTokenValue();
    return ret;
}

void Parser::createFieldReferenceExpression(Token token) {
    auto fieldReferenceExpression = std::make_unique<FieldReferenceExpression>();
    auto fieldName = recentExpressions.top();
    auto handlerName = recentExpressions.top();
    recentExpressions.pop();
    recentExpressions.pop();
    fieldReferenceExpression->fieldName = std::dynamic_pointer_cast<VarNameExpression>(fieldName)->value;
    fieldReferenceExpression->varName = std::dynamic_pointer_cast<VarNameExpression>(fieldName)->value;
    recentExpressions.push(std::move(fieldReferenceExpression));
}
bool Parser::handleOperator() {
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
bool Parser::tryToHandleSpecialToken() {
    if(!token.isCondition() && !token.isOperator() && !token.isFunction() || token.getType() == T_NEXT_LINE || token.getType() == T_END) {
        return false;
    }
    return handleOperator();
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
    while(!operators.empty()) {
        postfixRepresentation.push_back(operators.top());
        operators.pop();
    }
}

bool Parser::tryToGenerateCondition() {
    // treat conditions as operators
    if(token.isCondition()) {
        return tryToHandleSpecialToken();
    }
    return false;
}
bool Parser::tryToHandleNextLine() {
    if(token.getType() != T_NEXT_LINE && token.getType() != T_END) {
        return false;
    }
    finalize();
    postfixRepresentation.push_back(std::make_unique<Token>(token));
    return false;
}
bool Parser::tryToHandleOperand() {
    if (token.isOperand()) {
        if(token.getType() == T_USER_DEFINED_NAME) {
            auto nextToken = seeNextToken();
            if(nextToken.getType() == T_OPENING_PARENTHESIS) {
                token.setType(T_FUNCTION_CALL);
                operators.push(std::make_unique<Token>(token));
                token = getTokenValFromScanner();
                operators.push(std::make_unique<Token>(token));
                return true;
            }

            if(nextToken.getType() == T_DOT) {
                postfixRepresentation.push_back(std::make_unique<Token>(token));
                // dot
                token = getTokenValFromScanner();
                operators.push(std::make_unique<Token>(token));
                // field
                token = getTokenValFromScanner();
                postfixRepresentation.push_back(std::make_unique<Token>(token));
                return true;
            }
        }
        postfixRepresentation.push_back(std::make_unique<Token>(token));
        return true;
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
std::shared_ptr<RootExpression> Parser::generatePostfixRepresentation() {

    while (tryToHandleOperand() || tryToGenerateCondition() || tryToHandleEmbeddedDo() || tryToHandleEmbeddedDone() || tryToHandleNextLine()
           || tryToHandleSpecialToken() || tryToHandleEmbeddedExpression() ) {
        token = getTokenValFromScanner();
    }
    if(postfixRepresentation.front()->getType() == T_DONE) {
        token = getTokenValFromScanner();
        generateTree();
        return std::make_shared<RootExpression>();
    }
    if(token.getType() == T_NEXT_LINE) {
        token = getTokenValFromScanner();
        return generateTree();
    }
    if(token.getType() == T_END) {
        return generateTree();
    }
    return nullptr;
}

void Parser::createFieldNameExpression(Token token) {
    recentExpressions.push(std::make_unique<VarNameExpression>(token.getValue()));
}

void Parser::createStringExpression(Token token) {
    recentExpressions.push(std::make_unique<StringExpression>(token.getValue()));
}

void Parser::handleNewExpression(std::shared_ptr<RootExpression> nextRoot) {

    if(mainRoot->roots.empty()) {
        mainRoot->roots.push_back(nextRoot);
        return;
    } else if(auto maybePut = std::dynamic_pointer_cast<PutExpression>(mainRoot->roots.back()->expr)) {
        if(maybePut->toPrint == nullptr) {
            maybePut->toPrint = nextRoot->expr;
        } else {
            mainRoot->roots.push_back(nextRoot);
        }
        return;
    } else if(auto maybeRet = std::dynamic_pointer_cast<RetExpression>(mainRoot->roots.back()->expr)) {
        if(maybeRet->toRet == nullptr) {
            maybeRet->toRet = nextRoot->expr;
        } else {
            mainRoot->roots.push_back(nextRoot);
        }
        return;
    }
    mainRoot->roots.push_back(nextRoot);
}
