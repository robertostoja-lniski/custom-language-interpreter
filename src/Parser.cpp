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
    while((nextRoot = tryToBuildVarNamePrefixStatement()) != nullptr || (nextRoot = generatePostfixRepresentation()) != nullptr) {

        // tmp fix for handling do done
        if(!nextRoot->expr) {
            continue;
        }

        if(mainRoot->roots.empty()) {
            mainRoot->roots.push_back(nextRoot);
        } else if(auto maybePut = std::dynamic_pointer_cast<PutExpression>(mainRoot->roots.back()->expr)) {
            if(maybePut->toPrint == nullptr) {
                maybePut->toPrint = nextRoot->expr;
            } else {
                mainRoot->roots.push_back(nextRoot);
            }

        } else {
            mainRoot->roots.push_back(nextRoot);
        }
    }
}

std::shared_ptr<RootExpression> Parser::tryToBuildVarNamePrefixStatement() {
    if(token.getType() == T_SPECIFIER) {
        auto specifierExpr = getExpressionWithAssignedSpecifier();
        token = getTokenValFromScanner();
        if(token.getType() == T_END) {
            auto newRoot = std::make_shared<RootExpression>();
            newRoot->expr = specifierExpr;
            mainRoot->roots.push_back(newRoot);
            return nullptr;
        }
        auto function = std::make_shared<FunctionExpression>();
        if(token.getType() == T_OPENING_PARENTHESIS) {
            auto body = getParamsAsManyDeclarations();
            function->value = specifierExpr->value;
            function->right = body;
            function->left = specifierExpr->left;
            specifierExpr = nullptr;
        }
        if(token.getType() == T_NEXT_LINE) {
            token = getTokenValFromScanner();
        }
        auto newRoot = std::make_shared<RootExpression>();
        if(!specifierExpr) {
            newRoot->expr = function;
        } else {
            newRoot->expr = specifierExpr;
        }
        return newRoot;
    }

    if(token.getType() == T_PUT) {
        token = getTokenValFromScanner();
        auto newRoot = std::make_shared<RootExpression>();
        newRoot->expr = std::make_shared<PutExpression>();
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
            if(token.getType() == T_NEXT_LINE) {
                token = getTokenValFromScanner();
            }
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
void Parser::createFunctionCallExpression(Token token) {
    auto funcExpr = std::make_unique<FunctionCallExpression>();
    funcExpr->left = std::make_shared<VarNameExpression>(token.getValue());

    auto nextArg = recentExpressions.top();
    recentExpressions.pop();
    funcExpr->right = nextArg;

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
      EvaluationVisitor evaluationVisitor;
      evaluationVisitor.visit(mainRoot.get());
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
    funcExpr->left = std::make_shared<VarNameExpression>(token.getValue());
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
    auto isFunction = std::dynamic_pointer_cast<FunctionExpression>(condExpr);

    if(isElse) {
        assignBodyToUpperElse(condBody);
    } else if (isDeclaration) {
        assignBodyToUpperDeclaration(condBody, condExpr);
    } else if (isFunction) {
        isFunction->body = condBody;
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
    return scanner->getTokenValue();
}

void Parser::createFieldReferenceExpression(Token token) {
    setDoubleArgsExpr(std::make_unique<FieldReferenceExpression>());
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
    if(token.getType() == T_NO_ARG_FUNCTION_NAME) {
        postfixRepresentation.push_back(std::make_unique<Token>(token));
        return true;
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
bool Parser::tryToParseUserDefinedName() {
    postfixRepresentation.push_back(std::make_unique<Token>(token));
    return true;
}
bool Parser::parseConstantValue() {
        // tak jakby else
        // it is a simple operand
        postfixRepresentation.push_back(std::make_unique<Token>(token));
        return true;
}
bool Parser::tryToHandleOperand() {
    if (!token.isOperand()) {
        return false;
    }
    if(token.getType() == T_USER_DEFINED_NAME) {
        operators.push(std::make_unique<Token>(token));
        auto nextToken = seeNextToken();
        if(nextToken.getType() == T_OPENING_PARENTHESIS) {
            token = getTokenValFromScanner();
            return tryToParseFunctionCall();
        }

        postfixRepresentation.push_back(operators.top());
        operators.pop();
        return true;
    }
    return parseConstantValue();
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
