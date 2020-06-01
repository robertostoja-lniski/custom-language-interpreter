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
    auto leftOperand = assignExpression->left;

    if(auto isFieldRef = std::dynamic_pointer_cast<FieldReferenceExpression>(leftOperand)) {
        isFieldRef->accept(this);
        assignExpression->right->accept(this);
        updateSystemHandler();
        return;
    }

    auto isVarName = std::dynamic_pointer_cast<VarNameExpression>(leftOperand);
    if(!isVarName) {
        throw std::runtime_error("Values can be only assigned to variables");
    }
    auto varName = isVarName->value;

    auto wasDeclared = [](std::string varName, const std::deque<Context> ctx) -> bool {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->declarationMap.find(varName) != currentCtx->declarationMap.end()) {
                return true;
            }
        }
        return false;
    };

    if(!wasDeclared(varName, ctx)) {
        throw std::runtime_error(varName + " not declared");
    }

    assignExpression->right->accept(this);
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
    typeSpecifierExpression->left->accept(this);
    auto& currentContext = ctx.back();
    auto op = currentContext.getOperandAndPopFromContext();
    if (const auto varName (std::get_if<std::string>(&op)); varName) {
        ctx.back().declarationMap[*varName] = typeSpecifierExpression->value;
    }
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

    functionExpression->left->accept(this);
    auto varName = moveLocalOperandFromNearestContext();
    //checks if it is function
    auto isFunc = std::dynamic_pointer_cast<BodyExpression>(functionExpression->right);
    std::string strVarName;
    if (const auto varNameToStr (std::get_if<std::string>(&varName)); varNameToStr) {
        strVarName = *varNameToStr;
    } else {
        throw std::runtime_error("Unknown token to be declared");
    }

    if(isFunc) {

        FunctionDeclaration functionDeclaration;
        functionDeclaration.specifier = functionExpression->value;

        auto args = isFunc->statements;
        for(auto arg : args) {
            auto argInfo = std::dynamic_pointer_cast<TypeSpecifierExpression>(arg);
            if(!argInfo) {
                throw std::runtime_error("Unknown argument in function declaration");
            }
            std::string argSpecifier = argInfo->value;
            std::string argName = std::dynamic_pointer_cast<VarNameExpression>(argInfo->left)->value;
            functionDeclaration.args.emplace_back(argSpecifier, argName);
        }
        functionDeclaration.body = functionExpression->body;
        auto& currentCtx = ctx.back();
        currentCtx.functionDeclarationMap[strVarName] = functionDeclaration;
    }
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
    ifExpression->left->accept(this);
    auto condition = moveLocalOperandFromNearestContext();
    int conditionToInt;
    if (const auto condToInt (std::get_if<int>(&condition)); condToInt) {
        conditionToInt = *condToInt;
    }
    if(conditionToInt != 0) {
        ifExpression->right->accept(this);
    } else if(ifExpression->elseCondition != nullptr) {
        ifExpression->elseCondition->accept(this);
    }
}

void EvaluationVisitor::visit(ElseExpression *elseExpression) {

}

void EvaluationVisitor::visit(WhileExpression *whileExpression) {

    whileExpression->left->accept(this);
    auto condition = moveLocalOperandFromNearestContext();
    int conditionToInt;
    if (const auto condToInt (std::get_if<int>(&condition)); condToInt) {
        conditionToInt = *condToInt;
    }
    while(conditionToInt != 0) {
        whileExpression->right->accept(this);
        whileExpression->left->accept(this);
        auto currentCondition = moveLocalOperandFromNearestContext();
        if (const auto condToInt (std::get_if<int>(&currentCondition)); condToInt) {
            conditionToInt = *condToInt;
        }
    }
    ctx.pop_back();
}

void EvaluationVisitor::visit(DoExpression *doExpression) {
    /* unused */
}

void EvaluationVisitor::visit(FunctionCallExpression *functionCallExpression) {

    auto funcNameExpression = functionCallExpression->left;
    auto funcName = std::dynamic_pointer_cast<VarNameExpression>(funcNameExpression)->value;

    auto isDeclaredIntGivenCtx = [](std::string funcName, std::deque<Context> ctx) -> bool {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->functionDeclarationMap.find(funcName) != currentCtx->functionDeclarationMap.end()) {
                return true;
            }
        }
        return false;
    };
    if(!isDeclaredIntGivenCtx(funcName, ctx)) {
        throw std::runtime_error("Function not defined");
    }

    if(functionCallExpression->right) {
        functionCallExpression->right->accept(this);
    }

    auto getNearestFunctionDeclaration = [](std::string funcName, std::deque<Context> ctx)
            -> FunctionDeclaration {
        for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
            if(currentCtx->functionDeclarationMap.find(funcName) != currentCtx->functionDeclarationMap.end()) {
                return currentCtx->functionDeclarationMap[funcName];
            }
        }
        throw std::runtime_error("Declaration not found");
    };
    auto functionDeclaration = getNearestFunctionDeclaration(funcName, ctx);
    auto& currentCtxOperands = ctx.back().operands;
    if(currentCtxOperands.size() != functionDeclaration.args.size()) {
        throw std::runtime_error("Wrong number of arguments");
    }

    auto currentArg = functionDeclaration.args.cbegin();
    while(!currentCtxOperands.empty()) {
        auto calledArg = moveLocalOperandFromNearestContext();

        if (const auto value (std::get_if<std::string>(&calledArg)); value
                                                                     && currentArg->specifier != "int") {
            throw std::runtime_error("Arg mismatch in function " + funcName + " call.");
        }
        if (const auto value (std::get_if<double>(&calledArg)); value
                                                                && currentArg->specifier != "double") {
            throw std::runtime_error("Arg mismatch in function " + funcName + " call.");
        }
        if (const auto value (std::get_if<int>(&calledArg)); value
                                                             && currentArg->specifier != "string") {
            throw std::runtime_error("Arg mismatch in function " + funcName + " call.");
        }
        currentArg++;

        if(currentArg == functionDeclaration.args.cend()) {
            break;
        }
    }
    functionDeclaration.body->accept(this);
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
    // check if right is handler control
    auto isVarNameExpr = std::dynamic_pointer_cast<VarNameExpression>(fieldReferenceExpression->right);
    if(isVarNameExpr) {
        if(isVarNameExpr->value == "start") {
            auto handlerName = std::dynamic_pointer_cast<VarNameExpression>(fieldReferenceExpression->left)->value;
            auto handlerRef = getSystemHandlerReferenceByName(handlerName);
            handlerRef->run();
            return;
        }
        if(isVarNameExpr->value == "stop") {
            auto handlerName = std::dynamic_pointer_cast<VarNameExpression>(fieldReferenceExpression->left)->value;
            auto handlerRef = getSystemHandlerReferenceByName(handlerName);
            handlerRef->stop();
            return;
        }

    }
    fieldReferenceExpression->left->accept(this);
    fieldReferenceExpression->right->accept(this);
}

void EvaluationVisitor::visit(PutExpression *putExpression) {
    putExpression->toPrint->accept(this);
    auto valueToPrint = moveLocalOperandFromNearestContext();

    if (const auto value (std::get_if<double>(&valueToPrint)); value) {
        std::cout << *value << " of real type.\n";
        return;
    }
    if (const auto value (std::get_if<int>(&valueToPrint)); value) {
        std::cout << *value << " of int type.\n";
        return;
    }
    if (const auto value (std::get_if<std::string>(&valueToPrint)); value) {
        auto printIfFuncOrVariable = [](std::string name, std::deque<Context> ctx)
                -> bool {
            for(auto currentCtx = ctx.rbegin(); currentCtx != ctx.rend(); currentCtx++) {
                if(currentCtx->functionDeclarationMap.find(name) != currentCtx->functionDeclarationMap.end()) {
                    std::cout << name << " is a function with:\n";
                    auto func = currentCtx->functionDeclarationMap[name];
                    std::cout << "\t" << func.specifier << " specifier\n";
                    std::cout << "and args:\n";
                    for(auto [specifier, name] : func.args) {
                        std::cout << "\t" << specifier << " " << name << '\n';
                    }
                    return true;
                }

                if(currentCtx->declarationMap.find(name) != currentCtx->declarationMap.end()) {
                    auto value = currentCtx->variableAssignmentMap[name];

                    if (const auto valueToPrint (std::get_if<double>(&value)); valueToPrint) {
                        std::cout << *valueToPrint << " of real type.\n";
                        return true;
                    }
                    if (const auto valueToPrint (std::get_if<int>(&value)); valueToPrint) {
                        std::cout << *valueToPrint << " of int type.\n";
                        return true;
                    }
                    if (const auto valueToPrint (std::get_if<std::string>(&value)); valueToPrint) {
                        std::cout << *valueToPrint << " of int type.\n";
                        return true;
                    }
                }

                if(currentCtx->systemHandlerDeclarations.find(name) != currentCtx->systemHandlerDeclarations.end()) {
                    std::cout << name << " is a system handler.\n";
                    return true;
                }
            }
            return false;
        };

        if(!printIfFuncOrVariable(*value, ctx)) {
            std::cout << "no value assigned to " + *value + " variable.\n";
        }
    }
}

void EvaluationVisitor::visit(SystemHandlerExpression *systemHandlerExpression) {
    /* unused - handled by AssignExpression */
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
    ctxIt++;
    ctxIt->operands.push(toRet);
}
