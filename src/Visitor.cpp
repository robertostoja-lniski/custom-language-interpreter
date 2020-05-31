//
// Created by robert on 06.05.2020.
//
#include <iostream>
#include "../include/Visitor.h"

void ExpressionVisitor::visit(IntExpression *intExpression) {
    std::cout << "visiting int: " << intExpression->value << '\n';
}

void ExpressionVisitor::visit(FloatExpression *floatExpression) {
    std::cout << "visiting float: " << floatExpression->value << '\n';
}

void ExpressionVisitor::visit(VarNameExpression *varNameExpression) {
    std::cout << "variable name: " << varNameExpression->value << '\n';
}

void ExpressionVisitor::visit(DoubleArgsExpression *doubleArgsExpression) {
    std::cout << "in double args expression\n";
    doubleArgsExpression->left->accept(this);
    doubleArgsExpression->right->accept(this);
}

void ExpressionVisitor::visit(AdditionExpression *additionExpression) {
    std::cout << "Doing " << additionExpression->operation << " operation\n";
    additionExpression->left->accept(this);
    additionExpression->right->accept(this);
}

void ExpressionVisitor::visit(MultiplyExpression *multiplyExpression) {
    std::cout << "Multiplying\n";
    multiplyExpression->left->accept(this);
    multiplyExpression->right->accept(this);
}

void ExpressionVisitor::visit(AssignExpression *assignExpression) {
    std::cout << "Assignment\n";
    assignExpression->left->accept(this);
    assignExpression->right->accept(this);
}

void ExpressionVisitor::visit(DivideExpression *divideExpression) {
    std::cout << "Dividing (not by zero, of course!)\n";
    divideExpression->left->accept(this);
    divideExpression->right->accept(this);
}

void ExpressionVisitor::visit(RootExpression *rootExpression) {
    std::cout << "Starting\n";
    rootExpression->expr->accept(this);
//    rootExpression->right->accept(this);
}

void ExpressionVisitor::visit(VarDeclarationExpression *varDeclarationExpression) {
    std::cout << "Initialising: ";
    varDeclarationExpression->left->accept(this);
    varDeclarationExpression->right->accept(this);
}

void ExpressionVisitor::visit(TypeSpecifierExpression *typeSpecifierExpression) {
    std::cout << typeSpecifierExpression->value << '\n';
    typeSpecifierExpression->left->accept(this);
    if(typeSpecifierExpression->right) {
        std::cout << "Collection with values\n";
        typeSpecifierExpression->right->accept(this);
    }
}

void ExpressionVisitor::visit(BooleanAndExpression *booleanAndExpression) {
    std::cout << "Boolean and\n";
    booleanAndExpression->left->accept(this);
    booleanAndExpression->right->accept(this);
}

void ExpressionVisitor::visit(BooleanOrExpression *booleanOrExpression) {
    std::cout << "Boolean or\n";
    booleanOrExpression->left->accept(this);
    booleanOrExpression->right->accept(this);
}

void ExpressionVisitor::visit(BooleanOperatorExpression *booleanOperatorExpression) {
    std::cout << "In Boolean: " << booleanOperatorExpression->value << '\n';
    booleanOperatorExpression->left->accept(this);
    booleanOperatorExpression->right->accept(this);
}

void ExpressionVisitor::visit(FunctionExpression *functionExpression) {
    std::cout << "Function with name\n";
    functionExpression->left->accept(this);
    if(functionExpression->right) {
        std::cout << "And args:\n";
        functionExpression->right->accept(this);
    } else {
        std::cout << "Without any args\n";
    }
}

void ExpressionVisitor::visit(FunctionArgExpression *functionArgExpression) {
    std::cout << "Function Arg:\n\t";
    functionArgExpression->left->accept(this);
    std::cout << "\t";
    if(functionArgExpression->right)
        functionArgExpression->right->accept(this);
}

void ExpressionVisitor::visit(NoArgFunctionExpression *noArgFunctionExpression) {
    std::cout << "Function with no args:\n";
    std::cout << noArgFunctionExpression->name <<"\n";
}

void ExpressionVisitor::visit(NewLineExpression *newLineExpression) {
    std::cout << "Analysing next line\n";
    newLineExpression->left->accept(this);
//    newLineExpression->right->accept(this);
}
void ExpressionVisitor::visit(IfExpression* ifExpression) {
    std::cout << "In if condition\n";
    std::cout << "Condition: ";
    ifExpression->left->accept(this);
    std::cout << "Block positive\n";
    ifExpression->right->accept(this);
    if(ifExpression->elseCondition) {
        std::cout << "Block else\n";
        ifExpression->elseCondition->accept(this);
    }
}
void ExpressionVisitor::visit(ForExpression* forExpression) {
    std::cout << "In for loop\n";
    std::cout << "iterator: ";
    forExpression->left->accept(this);
    std::cout << "collection: ";
    forExpression->collectionName->accept(this);
    std::cout << "block: ";
    forExpression->right->accept(this);
}
void ExpressionVisitor::visit(WhileExpression* whileExpression) {
    std::cout << "In while loop\n";
    std::cout << "Condition:\n";
    whileExpression->left->accept(this);
    std::cout << "Block";
    if(whileExpression->right) {
        whileExpression->right->accept(this);
    } else {
        std::cout << " is empty.\n";
    }

}

void ExpressionVisitor::visit(FunctionCallExpression *functionCallExpression) {

}

void ExpressionVisitor::visit(BodyExpression *bodyExpression) {

    std::cout << "Inside a collection\n";
    for(auto statement : bodyExpression->statements) {
        std::cout << "visiting statement\n";
        statement->accept(this);
    }
}

void ExpressionVisitor::visit(DoExpression *doExpression) {
    std::cout << "It is do markdown\n";
}

void ExpressionVisitor::visit(ElseExpression *elseExpression) {
    std::cout << "It is else markdown\n";
}

void ExpressionVisitor::visit(FileExpression *fileExpression) {
    std::cout << "Visiting file\n";
    for(auto it : fileExpression->roots) {
        it->accept(this);
    }
}

void ExpressionVisitor::visit(FieldReferenceExpression *fieldReferenceExpression) {
    std::cout << "Object has field accessed\n";
    fieldReferenceExpression->left->accept(this);
    fieldReferenceExpression->right->accept(this);
}

void ExpressionVisitor::visit(PutExpression *putExpression) {
    std::cout << putExpression->toPrint;
}

void ExpressionVisitor::visit(SystemHandlerExpression *systemHandlerExpression) {
    /* unused */
}

void ExpressionVisitor::visit(SystemHandlerDeclExpression *systemHandlerDeclExpression) {
    /* unused */
}

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
    std::cout << "in double arg\n";
    doubleArgsExpression->left->accept(this);
    doubleArgsExpression->right->accept(this);
}

void EvaluationVisitor::visit(AdditionExpression *additionExpression) {
    std::cout << "Evaluating addition\n";
    additionExpression->left->accept(this);
    additionExpression->right->accept(this);
    handleOperation(additionExpression->operation);
}

void EvaluationVisitor::visit(MultiplyExpression *multiplyExpression) {
    std::cout << "Evaluating multiplying\n";
    multiplyExpression->left->accept(this);
    multiplyExpression->right->accept(this);
    handleOperation("*");
}

void EvaluationVisitor::visit(DivideExpression *divideExpression) {
    std::cout << "Evaluating division\n";
    divideExpression->left->accept(this);
    divideExpression->right->accept(this);
    handleOperation("/");
}

void EvaluationVisitor::visit(AssignExpression *assignExpression) {
    std::cout << "assigning\n";
    auto leftOperand = assignExpression->left;
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

    if (const auto value (std::get_if<std::string>(&result)); value) {
        std::cout << "result of subtree is int with value: " <<  value << '\n';
    }
    if (const auto value (std::get_if<double>(&result)); value) {
        std::cout << "result of subtree is int with value: " <<  value << '\n';
    }
    if (const auto value (std::get_if<int>(&result)); value) {
        std::cout << "result of subtree is int with value: " <<  value << '\n';
    }
}

void EvaluationVisitor::visit(VarDeclarationExpression *varDeclarationExpression) {
//    operands.push(std::make_shared<StrValue>(varDeclarationExpression->value));
}

void EvaluationVisitor::visit(TypeSpecifierExpression *typeSpecifierExpression) {
    typeSpecifierExpression->left->accept(this);
    auto& currentContext = ctx.back();
    auto op = currentContext.getOperandAndPopFromContext();
    if (const auto varName (std::get_if<std::string>(&op)); varName) {
//        op = getAssignedValueFromNearestContext(*varName);
        ctx.back().declarationMap[*varName] = typeSpecifierExpression->value;
    }
}

void EvaluationVisitor::visit(BooleanAndExpression *booleanAndExpression) {
    std::cout << "In boolean operator\n";
    booleanAndExpression->left->accept(this);
    booleanAndExpression->right->accept(this);
    handleOperation("&");
}

void EvaluationVisitor::visit(BooleanOrExpression *booleanOrExpression) {
    std::cout << "In boolean operator\n";
    booleanOrExpression->left->accept(this);
    booleanOrExpression->right->accept(this);
    handleOperation("|");
}

void EvaluationVisitor::visit(BooleanOperatorExpression *booleanOperatorExpression) {
    std::cout << "In boolean operator\n";
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
    for(auto statement : bodyExpression->statements) {
        statement->accept(this);
    }
}

void EvaluationVisitor::visit(IfExpression *ifExpression) {
    ctx.push_back({});
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
    ctx.pop_back();
}

void EvaluationVisitor::visit(ElseExpression *elseExpression) {
}

void EvaluationVisitor::visit(ForExpression *forExpression) {

}

void EvaluationVisitor::visit(WhileExpression *whileExpression) {
    ctx.push_back({});
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
    std::cout << "Visiting file\n";
    for(auto it : fileExpression->roots) {
        it->accept(this);
    }
}

void EvaluationVisitor::visit(FieldReferenceExpression *fieldReferenceExpression) {

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

}

void EvaluationVisitor::visit(SystemHandlerDeclExpression *systemHandlerDeclExpression) {
    auto handlerName = systemHandlerDeclExpression->name->value;
    auto& currentContext = ctx.back();
    ctx.back().systemHandlerDeclarations[handlerName] = std::make_shared<SystemHandlerExpression>();
}
