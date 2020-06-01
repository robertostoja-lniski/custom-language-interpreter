//
// Created by robert on 01.06.2020.
//

#include "../include/EvaluationVisitor.h"

/*
 * Evaluation visitor used for execution of instructions
 */
void EvaluationVisitor::visit(IntExpression *intExpression) {
    addToCurrentContext(intExpression->value);
}

void EvaluationVisitor::visit(FloatExpression *floatExpression) {
    addToCurrentContext(floatExpression->value);
}

void EvaluationVisitor::visit(VarNameExpression *varNameExpression) {
    addToCurrentContext(varNameExpression->value);
}

void EvaluationVisitor::visit(DoubleArgsExpression *doubleArgsExpression) {
    doubleArgsExpression->left->accept(this);
    doubleArgsExpression->right->accept(this);
}

void EvaluationVisitor::visit(AdditionExpression *additionExpression) {
    additionExpression->left->accept(this);
    additionExpression->right->accept(this);
    handleOperation(additionExpression->operation);
}

void EvaluationVisitor::visit(MultiplyExpression *multiplyExpression) {
    multiplyExpression->left->accept(this);
    multiplyExpression->right->accept(this);
    handleOperation("*");
}

void EvaluationVisitor::visit(DivideExpression *divideExpression) {
    divideExpression->left->accept(this);
    divideExpression->right->accept(this);
    handleOperation("/");
}

void EvaluationVisitor::visit(AssignExpression *assignExpression) {
    if(!assignExpression->fieldReference.empty()) {
        assignExpression->toAssign->accept(this);
        updateSystemHandler(assignExpression->variable, assignExpression->fieldReference);
        return;
    }

    auto varName = assignExpression->variable;
    assignExpression->toAssign->accept(this);

    auto valueToBeAssigned = moveLocalOperandFromNearestContext();
    auto getTypeOf = [](std::string varName, std::deque<Context> ctx) -> std::string {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->declarationMap.find(varName) != currentCtx->declarationMap.end()) {
                return currentCtx->declarationMap[varName];
            }
        }
        throw std::runtime_error("Variable " + varName + " not declared");
    };

    auto type = getTypeOf(varName, ctx);
    if (const auto val (std::get_if<double>(&valueToBeAssigned)); val
            && type != "float") {
        throw std::runtime_error("Type cast error");
    }
    if (const auto val (std::get_if<int>(&valueToBeAssigned)); val
            && type != "int") {
        throw std::runtime_error("Type cast error");
    }
    if (const auto val (std::get_if<std::string>(&valueToBeAssigned)); val
            && type != "string") {
        throw std::runtime_error("Type cast error");
    }

    for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
        if(currentCtx->variableAssignmentMap.find(varName) != currentCtx->variableAssignmentMap.end()) {
            currentCtx->variableAssignmentMap[varName] = valueToBeAssigned;
            return;
        }
    }
    auto& currentCtx = ctx.back();
    currentCtx.variableAssignmentMap[varName] = valueToBeAssigned;
}

void EvaluationVisitor::visit(RootExpression *rootExpression) {
    rootExpression->expr->accept(this);
    auto& currentCtxOperands = ctx.back().operands;
    if(currentCtxOperands.empty()) {
        return;
    }
    auto result = moveLocalOperandFromNearestContext();
}

void EvaluationVisitor::visit(VarDeclarationExpression *varDeclarationExpression) {
    /* handled as type specifier */
}

void EvaluationVisitor::visit(TypeSpecifierExpression *typeSpecifierExpression) {
    auto varName = typeSpecifierExpression->varName;
    auto specifierName = typeSpecifierExpression->specifierName;
    ctx.back().declarationMap[varName] = specifierName;
}

void EvaluationVisitor::visit(BooleanAndExpression *booleanAndExpression) {
    booleanAndExpression->left->accept(this);
    booleanAndExpression->right->accept(this);
    handleOperation("&");
}

void EvaluationVisitor::visit(BooleanOrExpression *booleanOrExpression) {
    booleanOrExpression->left->accept(this);
    booleanOrExpression->right->accept(this);
    handleOperation("|");
}

void EvaluationVisitor::visit(BooleanOperatorExpression *booleanOperatorExpression) {
    booleanOperatorExpression->left->accept(this);
    booleanOperatorExpression->right->accept(this);
    handleOperation(booleanOperatorExpression->value);
}

void EvaluationVisitor::visit(FunctionArgExpression *functionArgExpression) {
    functionArgExpression->left->accept(this);
    functionArgExpression->right->accept(this);
}

void EvaluationVisitor::visit(FunctionExpression *functionExpression) {

    std::string strVarName = functionExpression->name;
    auto args = functionExpression->body->statements;
    auto& currentCtx = ctx.back();
    currentCtx.functionDeclarationMap[strVarName] = functionExpression;
}

void EvaluationVisitor::visit(NoArgFunctionExpression *noArgFunctionExpression) {
    /* unused - handled as any arg num function */
}

void EvaluationVisitor::visit(NewLineExpression *newLineExpression) {
    /* unused */
}

void EvaluationVisitor::visit(BodyExpression *bodyExpression) {
    ctx.push_back({});
    for(auto statement : bodyExpression->statements) {
        statement->accept(this);
    }
    ctx.pop_back();
}

void EvaluationVisitor::visit(IfExpression *ifExpression) {
    ifExpression->condition->accept(this);
    auto condition = moveLocalOperandFromNearestContext();
    int conditionToInt;
    if (const auto condToInt (std::get_if<int>(&condition)); condToInt) {
        conditionToInt = *condToInt;
    }
    if(conditionToInt != 0) {
        ifExpression->ifBlock->accept(this);
    } else if(ifExpression->elseBlock != nullptr) {
        ifExpression->elseBlock->accept(this);
    }
}

void EvaluationVisitor::visit(ElseExpression *elseExpression) {

}

void EvaluationVisitor::visit(WhileExpression *whileExpression) {

    whileExpression->condition->accept(this);
    auto condition = moveLocalOperandFromNearestContext();
    int conditionToInt;
    if (const auto condToInt (std::get_if<int>(&condition)); condToInt) {
        conditionToInt = *condToInt;
    }
    while(conditionToInt != 0) {
        whileExpression->block->accept(this);
        whileExpression->condition->accept(this);
        auto currentCondition = moveLocalOperandFromNearestContext();
        if (const auto condToInt (std::get_if<int>(&currentCondition)); condToInt) {
            conditionToInt = *condToInt;
        }
    }
}

void EvaluationVisitor::visit(DoExpression *doExpression) {
    /* unused */
}

void EvaluationVisitor::visit(FunctionCallExpression *functionCallExpression) {

    auto funcName = functionCallExpression->name;
    if(functionCallExpression->argListHead) {
        functionCallExpression->argListHead->accept(this);
    }

    auto getNearestFunctionDeclaration = [](std::string funcName, std::deque<Context> ctx)
            -> FunctionExpression* {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->functionDeclarationMap.find(funcName) != currentCtx->functionDeclarationMap.end()) {
                return currentCtx->functionDeclarationMap[funcName];
            }
        }
        throw std::runtime_error("Declaration not found");
    };

    auto& currentArgs = ctx.back().operands;
    auto functionDeclaration = getNearestFunctionDeclaration(funcName, ctx);
    auto declaredArgs = functionDeclaration->args->statements;
    auto declaredArgsIt = declaredArgs.begin();
    if(currentArgs.size() != declaredArgs.size()) {
        throw std::runtime_error("Arg num mismatch");
    }
    // sets function call args with values from currentArgs
    ctx.push_back({});
    while(!currentArgs.empty()) {

        if(const auto isString = std::get_if<std::string>(&currentArgs.front()); isString) {
            if(auto decl = std::dynamic_pointer_cast<TypeSpecifierExpression>(*declaredArgsIt); decl->specifierName == "string"){
                ctx.back().variableAssignmentMap[decl->varName] = currentArgs.front();
                declaredArgsIt++;
                currentArgs.pop_front();
                continue;
            }
        }

        if(const auto isInt = std::get_if<int>(&currentArgs.front()); isInt) {
            if(auto decl = std::dynamic_pointer_cast<TypeSpecifierExpression>(*declaredArgsIt); decl->specifierName == "int"){
                ctx.back().variableAssignmentMap[decl->varName] = currentArgs.front();
                declaredArgsIt++;
                currentArgs.pop_front();
                continue;
            }
        }

        if(const auto isFloat = std::get_if<double>(&currentArgs.front()); isFloat) {
            if(auto decl = std::dynamic_pointer_cast<TypeSpecifierExpression>(*declaredArgsIt); decl->specifierName == "float"){
                ctx.back().variableAssignmentMap[decl->varName] = currentArgs.front();
                declaredArgsIt++;
                currentArgs.pop_front();
                continue;
            }
        }

        throw std::runtime_error("Arg mismatch");
    }
    functionDeclaration->body->accept(this);
    ctx.pop_back();
}

void EvaluationVisitor::visit(FileExpression *fileExpression) {
    ctx.push_back({});
    for(auto it : fileExpression->roots) {
        it->accept(this);
    }
}

void EvaluationVisitor::visit(StringExpression* stringExpression){
    addToCurrentContext(stringExpression->value);
}

void EvaluationVisitor::visit(FieldReferenceExpression *fieldReferenceExpression) {
    auto handlerName = fieldReferenceExpression->varName;
    auto handlerRef = getSystemHandlerReferenceByName(handlerName);
    if(fieldReferenceExpression->refName == "start") {
        handlerRef->run();
    } else if(fieldReferenceExpression->refName == "stop") {
        handlerRef->stop();
    } else {
        throw std::runtime_error("Command or field unrecognised by handler\n"
                                 "Use <my_handler>.start or <my_handler>.stop");
    }
}

void EvaluationVisitor::visit(PutExpression *putExpression) {
    putExpression->toPrint->accept(this);
    auto valueToPrint = moveLocalOperandFromNearestContext();
    auto isString = std::get_if<std::string>(&valueToPrint);
    if(isString) {
        auto printIfFuncOrVariable = [](std::string name, std::deque<Context> ctx)
                -> bool {
            for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
                if(currentCtx->functionDeclarationMap.find(name) != currentCtx->functionDeclarationMap.end()) {
                    std::cout << name << " is a function with:\n";
                    auto func = currentCtx->functionDeclarationMap[name];
                    std::cout << "\t" << func->specifier << " specifier\n";
                    return true;
                }

                if(currentCtx->declarationMap.find(name) != currentCtx->declarationMap.end()) {
                    auto value = currentCtx->variableAssignmentMap[name];
                    std::visit([](const auto &elem) { std::cout << elem << '\n'; }, value);
                    return true;
                }

                if(currentCtx->systemHandlerDeclarations.find(name) != currentCtx->systemHandlerDeclarations.end()) {
                    std::cout << name << " is a system handler.\n";
                    return true;
                }
            }
            return false;
        };
        if(!printIfFuncOrVariable(*isString, ctx)) {
            std::cout << "no value assigned to " + *isString + " variable.\n";
        }
        return;
    }
    std::visit([](const auto &elem) { std::cout << elem << '\n'; }, valueToPrint);
}


void EvaluationVisitor::visit(SystemHandlerDeclExpression *systemHandlerDeclExpression) {
    auto handlerName = systemHandlerDeclExpression->name->value;
    auto& currentContext = ctx.back();
    ctx.back().systemHandlerDeclarations[handlerName] = std::make_shared<SystemHandlerInfo>();
}

void EvaluationVisitor::visit(RetExpression *retExpression) {
    retExpression->toRet->accept(this);
    auto toRet = ctx.back().operands.front();
    // go to previous ctx
    // (ctx from which function was called)
    auto ctxIt = ctx.rbegin();
    // goes two ctx upper
    ctxIt += 2;
    ctxIt->operands.push_back(toRet);
}
