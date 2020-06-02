//
// Created by robert on 06.05.2020.
//

#include "../include/Parser.h"

#include <utility>
void Parser::parse() {
    token = getTokenValFromScanner();
    std::shared_ptr<RootExpression> nextRoot;

    if(token.getType() == T_END) {
        return;
    }
    while((nextRoot = tryToBuildVarNamePrefixStatement()) != nullptr ||
            (nextRoot = tryToBuildBuiltInFunctionCall()) != nullptr ||
            (nextRoot = tryToBuildBlockBoundary()) != nullptr ||
            (nextRoot = generatePostfixRepresentation()) != nullptr) {
        if(nextRoot->expr) {
            handleNewExpression(nextRoot);
        }
    }
}
std::shared_ptr<RootExpression> Parser::tryToBuildBuiltInFunctionCall() {
    if(token.getType() == T_PUT) {
        token = getTokenValFromScanner();
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = std::make_shared<PutExpression>();
        return newRoot;
    }

    if(token.getType() == T_RET) {
        token = getTokenValFromScanner();
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = std::make_shared<RetExpression>();
        return newRoot;
    }
    if(token.getType() == T_EXIT) {
        exit(0);
    }
    return nullptr;
}
std::shared_ptr<RootExpression> Parser::tryToBuildVarNamePrefixStatement() {
    if(token.getType() == T_SPECIFIER) {
        auto specifierExpr = getExpressionWithAssignedSpecifier();
        token = getTokenValFromScanner();

        if(token.getType() == T_OPENING_PARENTHESIS) {
            auto function = std::make_shared<FunctionExpression>();
            auto args = getParamsAsManyDeclarations();
            function->specifier = specifierExpr->specifierName;
            function->args = args;
            function->name = specifierExpr->varName;

            auto newRoot = std::make_shared<RootExpression>();
            newRoot->expr = function;
            return newRoot;
        }
        if(token.getType() == T_NEXT_LINE) {
            token = getTokenValFromScanner();
        }
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = specifierExpr;
        return newRoot;
    }

    if(token.getType() == T_SYSTEM_HANDLER) {
        auto systemHandlerToken = token;
        token = getTokenValFromScanner();

        if(token.getType() == T_USER_DEFINED_NAME) {
            auto systemHandlerDeclExpression = std::make_shared<SystemHandlerDeclStatement>();
            auto name = std::make_shared<VarNameExpression>(token.getValue());
            systemHandlerDeclExpression->name = name;
            auto newRoot = std::make_shared<RootExpression>();
            newRoot->expr = systemHandlerDeclExpression;
            token = getTokenValFromScanner();
            if(token.getType() == T_NEXT_LINE) {
                token = getTokenValFromScanner();
            }
            return newRoot;
        }
    }
    return nullptr;
}

std::shared_ptr<TypeSpecifierStatement> Parser::getExpressionWithAssignedSpecifier() {
    auto specifierExpr = std::make_shared<TypeSpecifierStatement>();
    auto shouldBeIdentToken = getTokenValFromScanner();
    if(shouldBeIdentToken.getType() != T_USER_DEFINED_NAME) {
        throw std::runtime_error("Type specifier without ident");
    }
    specifierExpr->specifierName = token.getValue();
    specifierExpr->varName = shouldBeIdentToken.getValue();
    return specifierExpr;
}
std::shared_ptr<BodyStatement> Parser::getParamsAsManyDeclarations() {
    auto argBlock = std::make_shared<BodyStatement>();
    token = getTokenValFromScanner();

    while(token.getType() == T_SPECIFIER) {
        auto specifierName = token.getValue();
        token = getTokenValFromScanner();
        if(token.getType() == T_USER_DEFINED_NAME) {
            auto varName = token.getValue();
            auto currentArg = std::make_shared<TypeSpecifierStatement>();

            currentArg->varName = varName;
            currentArg->specifierName = specifierName;
            argBlock->statements.push_back(currentArg);

            token = getTokenValFromScanner();
            if(token.getType() == T_SEMICON) {
                token = getTokenValFromScanner();
                continue;
            }
            if(token.getType() == T_CLOSING_PARENTHESIS) {
                token = getTokenValFromScanner();
                if(token.getType() == T_NEXT_LINE) {
                    token = getTokenValFromScanner();
                }
                return argBlock;
            }
        }
        throw std::runtime_error("Wrong args in declaration");
    }
    if(token.getType() == T_CLOSING_PARENTHESIS) {
        token = getTokenValFromScanner();
        if(token.getType() == T_NEXT_LINE) {
            token = getTokenValFromScanner();
        }
        return argBlock;
    }
    throw std::runtime_error("Wrong declaration");
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

    ifExpr->condition = std::move(cond);
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
    auto assignExpr = std::make_unique<AssignExpression>();
    if(recentExpressions.size() < 2) {
        throw std::runtime_error("Not enough args for operation");
    }
    auto toAssign = recentExpressions.top();
    recentExpressions.pop();
    auto variable = recentExpressions.top();
    recentExpressions.pop();

    if(auto isFieldRef = std::dynamic_pointer_cast<FieldReferenceExpression>(variable)) {
        assignExpr->variable = isFieldRef->varName;
        assignExpr->fieldReference = isFieldRef->refName;
    } else {
        assignExpr->variable = std::dynamic_pointer_cast<VarNameExpression>(variable)->value;
    }

    assignExpr->toAssign = toAssign;
    recentExpressions.push(std::move(assignExpr));
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

    auto nextArg = recentExpressions.top();
    recentExpressions.pop();
    funcExpr->argListHead = nextArg;

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

void Parser::createSemiconExpression(Token token) {
    auto newArgs = std::make_shared<FunctionArgExpression>();

    if(!recentExpressions.empty()) {
        newArgs->right = recentExpressions.top();
        recentExpressions.pop();
        // maybe few arguments can be joined

        if(!recentExpressions.empty()) {
            auto previousExpr = recentExpressions.top();
                newArgs->left = previousExpr;
                recentExpressions.pop();
        }
    }
    recentExpressions.push(newArgs);
}

void Parser::createNoArgFunctionExpression(Token token) {
    auto funcExpr = std::make_unique<FunctionCallExpression>();
    funcExpr->name = token.getValue();
    recentExpressions.push(std::move(funcExpr));
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
    auto condBody = std::make_shared<DoNode>();
    recentExpressions.push(condBody);
}

void Parser::joinUpperStatementsUntilDoFound(std::shared_ptr<BodyStatement> condBody){
    auto upperRoot = mainRoot->roots.back()->expr;
    while(!std::dynamic_pointer_cast<DoNode>(upperRoot)) {
        condBody->statements.push_front(upperRoot);
        mainRoot->roots.pop_back();
        upperRoot = mainRoot->roots.back()->expr;
    }
    mainRoot->roots.pop_back();
}
void Parser::assignBodyToUpperIf(std::shared_ptr<BodyStatement> condBody, std::shared_ptr<IfExpression> condExpr) {

    if(!condExpr->ifBlock) {
        condExpr->ifBlock = condBody;
        return;
    }
    if(!condExpr->elseBlock) {
        condExpr->elseBlock = condBody;
        return;
    }
}

void Parser::assignBodyToUpperAnyExpression(std::shared_ptr<BodyStatement> condBody, std::shared_ptr<Node> condExpr) {
    auto condExprAsDoubleArg = std::dynamic_pointer_cast<DoubleArgsExpression>(condExpr);
    condExprAsDoubleArg->right = condBody;
}
void Parser::assignBodyToUpperWhile(std::shared_ptr<BodyStatement> condBody, std::shared_ptr<WhileExpression> condExpr) {
    condExpr->block = condBody;
}
void Parser::assignBodyToUpperExpression(std::shared_ptr<BodyStatement> condBody) {
    auto condExpr = mainRoot->roots.back()->expr;
    auto isElse = std::dynamic_pointer_cast<ElseExpression>(condExpr);
    if(isElse) {
        mainRoot->roots.pop_back();
    }
    condExpr = mainRoot->roots.back()->expr;
    auto isIf = std::dynamic_pointer_cast<IfExpression>(condExpr);
    auto isFunction = std::dynamic_pointer_cast<FunctionExpression>(condExpr);
    auto isWhile = std::dynamic_pointer_cast<WhileExpression>(condExpr);

    if(isIf) {
        assignBodyToUpperIf(condBody, isIf);
    } else if (isFunction) {
        isFunction->body = condBody;
    } else if(isWhile) {
        assignBodyToUpperWhile(condBody, isWhile);
    } else {
        assignBodyToUpperAnyExpression(condBody, condExpr);
    }
}
void Parser::createDoneExpression(Token token) {
    auto condBody = std::make_shared<BodyStatement>();
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
    return scanner->getTokenValue();
}

void Parser::createFieldReferenceExpression(Token token) {
    auto fieldReferenceExpression = std::make_unique<FieldReferenceExpression>();
    auto refName = recentExpressions.top();
    recentExpressions.pop();
    auto handlerName = recentExpressions.top();
    recentExpressions.pop();
    fieldReferenceExpression->varName = std::dynamic_pointer_cast<VarNameExpression>(handlerName)->value;
    fieldReferenceExpression->refName = std::dynamic_pointer_cast<VarNameExpression>(refName)->value;
    recentExpressions.push(std::move(fieldReferenceExpression));
}
bool Parser::tryToHandleOperator() {
    if(isSpecial()) {
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

void Parser::finalize() {
    while(!operators.empty()) {
        postfixRepresentation.push_back(operators.top());
        operators.pop();
    }
}

bool Parser::tryToHandleNextLine() {
    if(token.getType() != T_NEXT_LINE && token.getType() != T_END) {
        return false;
    }
    finalize();
    postfixRepresentation.push_back(std::make_unique<Token>(token));
    return false;
}
bool Parser::parseNoArgFunctionCall() {
    // take '(' from operators stack
    operators.pop();
    auto func_name = operators.top();
    func_name->setType(T_NO_ARG_FUNCTION_NAME);
    token = getTokenValFromScanner();
    return true;
}
bool Parser::tryToParseManyArgsFunctionCall() {
    // take '(' from operators stack
    // and manipulate function call type
    auto function_call_opening = operators.top();
    operators.pop();
    auto function_name = operators.top();
    function_name->setType(T_FUNCTION_CALL);
    operators.push(function_call_opening);
    return true;
}
bool Parser::tryToParseFunctionCall() {
    operators.push(std::make_unique<Token>(token));
    token = seeNextToken();
    if(token.getType() == T_CLOSING_PARENTHESIS) {
        return parseNoArgFunctionCall();
    } else {
        return tryToParseManyArgsFunctionCall();
    }
}
bool Parser::tryToHandleOperand() {
    if (!isOperand()) {
        return false;
    }
    if(token.getType() == T_USER_DEFINED_NAME) {
        operators.push(std::make_unique<Token>(token));
        auto nextToken = seeNextToken();
        if(nextToken.getType() == T_OPENING_PARENTHESIS) {
            token = getTokenValFromScanner();
            return tryToParseFunctionCall();
        }
        if(nextToken.getType() == T_DOT) {

            auto handler = operators.top();
            operators.pop();
            postfixRepresentation.push_back(handler);
            // dot
            token = getTokenValFromScanner();
            operators.push(std::make_unique<Token>(token));
            // field
            token = getTokenValFromScanner();
            postfixRepresentation.push_back(std::make_unique<Token>(token));
            return true;
        }

        postfixRepresentation.push_back(operators.top());
        operators.pop();
        return true;
    }
    postfixRepresentation.push_back(std::make_unique<Token>(token));
    return true;
}

std::shared_ptr<RootExpression> Parser::generatePostfixRepresentation() {

    while (tryToHandleOperand() || tryToHandleOperator() || tryToHandleNextLine()
            || tryToHandleEmbeddedExpression() ) {
        token = getTokenValFromScanner();
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

    if(!nextRoot->expr) {
        return;
    }
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

std::shared_ptr<RootExpression> Parser::tryToBuildBlockBoundary() {
    if(token.getType() == T_DONE) {
        createDoneExpression(token);
        token = getTokenValFromScanner();
        if(token.getType() == T_NEXT_LINE) {
            token = getTokenValFromScanner();
        }
        return std::make_shared<RootExpression>();
    }
    if(token.getType() == T_DO) {
        token = getTokenValFromScanner();
        auto condBody = std::make_shared<DoNode>();
        if(token.getType() == T_NEXT_LINE) {
            token = getTokenValFromScanner();
        }
        auto ret = std::make_shared<RootExpression>();
        ret->expr = condBody;
        return ret;
    }
    return nullptr;
}

