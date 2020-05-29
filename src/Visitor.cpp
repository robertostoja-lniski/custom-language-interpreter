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


/*
 * Evaluation visitor used for execution of instructions
 */
void EvaluationVisitor::visit(IntExpression *intExpression) {
    operands.push(std::make_shared<IntValue>(intExpression->value));
}

void EvaluationVisitor::visit(FloatExpression *floatExpression) {
    operands.push(std::make_shared<RealValue>(floatExpression->value));
}

void EvaluationVisitor::visit(VarNameExpression *varNameExpression) {
    operands.push(std::make_shared<StrValue>(varNameExpression->value));
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

    std::shared_ptr<PrimitiveValue> leftOperand = operands.front();
    operands.pop();
    std::shared_ptr<PrimitiveValue> rightOperand = operands.front();
    operands.pop();

    auto leftOpToStr = std::dynamic_pointer_cast<StrValue>(leftOperand);
    auto rightOpToStr = std::dynamic_pointer_cast<StrValue>(rightOperand);

    if(leftOpToStr) {
        if(variableAssignmentMap.find(leftOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(leftOpToStr->value + " not declared");
        }
        leftOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[leftOpToStr->value]);
    }

    if(rightOpToStr) {
        if(variableAssignmentMap.find(rightOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(rightOpToStr->value + " not declared");
        }
        rightOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[rightOpToStr->value]);
    }

    auto leftOpToInt = std::dynamic_pointer_cast<IntValue>(leftOperand);
    auto rightOpToInt = std::dynamic_pointer_cast<IntValue>(rightOperand);
    if(leftOpToInt && rightOpToInt) {
        if(additionExpression->operation == "-") {
            rightOpToInt->value *= -1;
        }
        operands.push(std::make_shared<IntValue>(leftOpToInt->value + rightOpToInt->value));
        return;
    }
    auto leftOpToReal = std::dynamic_pointer_cast<RealValue>(leftOperand);
    auto rightOpToReal = std::dynamic_pointer_cast<RealValue>(rightOperand);

    if(leftOpToReal && rightOpToReal) {
        if(additionExpression->operation == "-") {
            rightOpToReal->value *= -1;
        }
        operands.push(std::make_shared<RealValue>(leftOpToReal->value + rightOpToReal->value));
        return;
    }
    if(leftOpToReal && rightOpToInt) {
        if(additionExpression->operation == "-") {
            rightOpToInt->value *= -1;
        }
        operands.push(std::make_shared<RealValue>(leftOpToReal->value + rightOpToInt->value));
        return;
    }
    if(leftOpToInt && rightOpToReal) {
        if(additionExpression->operation == "-") {
            rightOpToReal->value *= -1;
        }
        operands.push(std::make_shared<RealValue>(leftOpToInt->value + rightOpToReal->value));
        return;
    }

}

void EvaluationVisitor::visit(MultiplyExpression *multiplyExpression) {
    std::cout << "Evaluating multiplying\n";
    multiplyExpression->left->accept(this);
    multiplyExpression->right->accept(this);

    std::shared_ptr<PrimitiveValue> leftOperand = operands.front();
    operands.pop();
    std::shared_ptr<PrimitiveValue> rightOperand = operands.front();
    operands.pop();

    auto leftOpToStr = std::dynamic_pointer_cast<StrValue>(leftOperand);
    auto rightOpToStr = std::dynamic_pointer_cast<StrValue>(rightOperand);

    if(leftOpToStr) {
        if(variableAssignmentMap.find(leftOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(leftOpToStr->value + " not declared");
        }
        leftOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[leftOpToStr->value]);
    }

    if(rightOpToStr) {
        if(variableAssignmentMap.find(rightOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(rightOpToStr->value + " not declared");
        }
        rightOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[rightOpToStr->value]);
    }

    auto leftOpToInt = std::dynamic_pointer_cast<IntValue>(leftOperand);
    auto rightOpToInt = std::dynamic_pointer_cast<IntValue>(rightOperand);
    if(leftOpToInt && rightOpToInt) {
        operands.push(std::make_shared<IntValue>(leftOpToInt->value * rightOpToInt->value));
        return;
    }
    auto leftOpToReal = std::dynamic_pointer_cast<RealValue>(leftOperand);
    auto rightOpToReal = std::dynamic_pointer_cast<RealValue>(rightOperand);
    if(leftOpToReal && rightOpToReal) {
        operands.push(std::make_shared<RealValue>(leftOpToReal->value * rightOpToReal->value));
        return;
    }
    if(leftOpToReal && rightOpToInt) {
        operands.push(std::make_shared<RealValue>(leftOpToReal->value * rightOpToInt->value));
        return;
    }
    if(leftOpToInt && rightOpToReal) {
        operands.push(std::make_shared<RealValue>(leftOpToInt->value * rightOpToReal->value));
        return;
    }
    throw std::runtime_error("Wrong types of multiplication operands");
}

void EvaluationVisitor::visit(DivideExpression *divideExpression) {
    std::cout << "Evaluating division\n";
    divideExpression->left->accept(this);
    auto isLeftInt = std::dynamic_pointer_cast<IntExpression>(divideExpression->left);
    divideExpression->right->accept(this);

    std::shared_ptr<PrimitiveValue> leftOperand = operands.front();
    operands.pop();
    std::shared_ptr<PrimitiveValue> rightOperand = operands.front();
    operands.pop();

    auto leftOpToStr = std::dynamic_pointer_cast<StrValue>(leftOperand);
    auto rightOpToStr = std::dynamic_pointer_cast<StrValue>(rightOperand);

    if(leftOpToStr) {
        if(variableAssignmentMap.find(leftOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(leftOpToStr->value + " not declared");
        }
        leftOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[leftOpToStr->value]);
    }

    if(rightOpToStr) {
        if(variableAssignmentMap.find(rightOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(rightOpToStr->value + " not declared");
        }
        rightOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[rightOpToStr->value]);
    }

    auto leftOpToInt = std::dynamic_pointer_cast<IntValue>(leftOperand);
    auto rightOpToInt = std::dynamic_pointer_cast<IntValue>(rightOperand);
    if(rightOpToInt->value == 0) {
        throw std::runtime_error("Division by zero!");
    }
    if(leftOpToInt && rightOpToInt) {
        operands.push(std::make_shared<IntValue>(leftOpToInt->value / rightOpToInt->value));
        return;
    }
    auto leftOpToReal = std::dynamic_pointer_cast<RealValue>(leftOperand);
    auto rightOpToReal = std::dynamic_pointer_cast<RealValue>(rightOperand);
    if(rightOpToInt->value == 0) {
        throw std::runtime_error("Division by zero!");
    }
    if(leftOpToReal && rightOpToReal) {
        operands.push(std::make_shared<RealValue>(leftOpToInt->value / rightOpToReal->value));
        return;
    }
    if(leftOpToReal && rightOpToInt) {
        operands.push(std::make_shared<IntValue>(leftOpToReal->value / rightOpToInt->value));
        return;
    }
    if(leftOpToInt && rightOpToReal) {
        operands.push(std::make_shared<RealValue>(leftOpToReal->value / rightOpToReal->value));
        return;
    }
    throw std::runtime_error("Wrong types of multiplication operands");
}

void EvaluationVisitor::visit(AssignExpression *assignExpression) {
    std::cout << "assigning\n";
    auto leftOperand = assignExpression->left;
    auto isVarName = std::dynamic_pointer_cast<VarNameExpression>(leftOperand);
    if(!isVarName) {
        return;
    }

    auto varName = isVarName->value;
    if(declarationMap.find(varName) == declarationMap.end()) {
        throw std::runtime_error("Error: " + varName + " Not declared");
    }

    assignExpression->right->accept(this);
    auto valueToBeAssigned = operands.front();
    operands.pop();
    auto isValueToBeAssignedInt = std::dynamic_pointer_cast<IntValue>(valueToBeAssigned);
    auto isValueToBeAssignedReal = std::dynamic_pointer_cast<RealValue>(valueToBeAssigned);
    auto isValueToBeAssignedStr = std::dynamic_pointer_cast<StrValue>(valueToBeAssigned);

    if(isValueToBeAssignedInt && declarationMap[varName] != "int") {
        throw std::runtime_error("Type cast error");
    }
    if(isValueToBeAssignedReal && declarationMap[varName] != "float") {
        throw std::runtime_error("Type cast error");
    }
    if(isValueToBeAssignedStr && declarationMap[varName] != "string") {
        throw std::runtime_error("Type cast error");
    }

    variableAssignmentMap[varName] = valueToBeAssigned;
}

void EvaluationVisitor::visit(RootExpression *rootExpression) {
    rootExpression->expr->accept(this);
    if(operands.empty()) {
        return;
    }
    auto result = operands.front();

    if(auto isInt =  std::dynamic_pointer_cast<IntValue>(result)) {
        std::cout << "result of subtree is int with value: " << isInt->value << '\n';
    } else if(auto isStr =  std::dynamic_pointer_cast<StrValue>(result)) {
        std::cout << "result of subtree is string with value: " << isStr->value << '\n';
    } else if(auto isReal =  std::dynamic_pointer_cast<RealValue>(result)) {
        std::cout << "result of subtree is real with value: " << isReal->value << '\n';
    }

    operands.pop();
}

void EvaluationVisitor::visit(VarDeclarationExpression *varDeclarationExpression) {
//    operands.push(std::make_shared<StrValue>(varDeclarationExpression->value));
}

void EvaluationVisitor::visit(TypeSpecifierExpression *typeSpecifierExpression) {

    typeSpecifierExpression->left->accept(this);
    auto varName = operands.front();
    operands.pop();
    auto strVarName = std::dynamic_pointer_cast<StrValue>(varName);
    if(!strVarName) {
        throw std::runtime_error("Unknown token to be declared");
    }

    declarationMap[strVarName->value] = typeSpecifierExpression->value;
}

void EvaluationVisitor::visit(BooleanAndExpression *booleanAndExpression) {

}

void EvaluationVisitor::visit(BooleanOrExpression *booleanOrExpression) {

}

void EvaluationVisitor::visit(BooleanOperatorExpression *booleanOperatorExpression) {
    std::cout << "In boolean operator\n";
    booleanOperatorExpression->left->accept(this);
    booleanOperatorExpression->right->accept(this);

    std::shared_ptr<PrimitiveValue> leftOperand = operands.front();
    operands.pop();
    std::shared_ptr<PrimitiveValue> rightOperand = operands.front();
    operands.pop();

    auto leftOpToStr = std::dynamic_pointer_cast<StrValue>(leftOperand);
    auto rightOpToStr = std::dynamic_pointer_cast<StrValue>(rightOperand);

    if(leftOpToStr) {
        if(variableAssignmentMap.find(leftOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(leftOpToStr->value + " not declared");
        }
        leftOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[leftOpToStr->value]);
    }

    if(rightOpToStr) {
        if(variableAssignmentMap.find(rightOpToStr->value) == variableAssignmentMap.end()) {
            throw std::runtime_error(rightOpToStr->value + " not declared");
        }
        rightOperand = std::dynamic_pointer_cast<PrimitiveValue>(variableAssignmentMap[rightOpToStr->value]);
    }

    auto leftOpToInt = std::dynamic_pointer_cast<IntValue>(leftOperand);
    auto rightOpToInt = std::dynamic_pointer_cast<IntValue>(rightOperand);
    if(leftOpToInt && rightOpToInt) {
        if(booleanOperatorExpression->value == ">") {
            operands.push(std::make_shared<IntValue>(leftOpToInt->value > rightOpToInt->value));
        }
        return;
    }
    auto leftOpToReal = std::dynamic_pointer_cast<RealValue>(leftOperand);
    auto rightOpToReal = std::dynamic_pointer_cast<RealValue>(rightOperand);
    if(leftOpToReal && rightOpToReal) {
        operands.push(std::make_shared<RealValue>(leftOpToReal->value * rightOpToReal->value));
        return;
    }
    if(leftOpToReal && rightOpToInt) {
        operands.push(std::make_shared<RealValue>(leftOpToReal->value * rightOpToInt->value));
        return;
    }
    if(leftOpToInt && rightOpToReal) {
        operands.push(std::make_shared<RealValue>(leftOpToInt->value * rightOpToReal->value));
        return;
    }
    throw std::runtime_error("Wrong types of multiplication operands");

}

void EvaluationVisitor::visit(FunctionArgExpression *functionArgExpression) {
    functionArgExpression->left->accept(this);
    functionArgExpression->right->accept(this);
}

void EvaluationVisitor::visit(FunctionExpression *functionExpression) {

    functionExpression->left->accept(this);
    auto varName = operands.front();
    operands.pop();
    //checks if it is function
    auto isFunc = std::dynamic_pointer_cast<BodyExpression>(functionExpression->right);
    auto strVarName = std::dynamic_pointer_cast<StrValue>(varName);
    if(!strVarName) {
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
        functionDeclarationMap[strVarName->value] = functionDeclaration;
    }
}

void EvaluationVisitor::visit(NoArgFunctionExpression *noArgFunctionExpression) {

}

void EvaluationVisitor::visit(NewLineExpression *newLineExpression) {

}

void EvaluationVisitor::visit(BodyExpression *bodyExpression) {
    for(auto statement : bodyExpression->statements) {
        statement->accept(this);
    }
}

void EvaluationVisitor::visit(IfExpression *ifExpression) {

}

void EvaluationVisitor::visit(ElseExpression *elseExpression) {

}

void EvaluationVisitor::visit(ForExpression *forExpression) {

}

void EvaluationVisitor::visit(WhileExpression *whileExpression) {
    whileExpression->left->accept(this);
    auto condition = operands.front();
    operands.pop();
    auto conditionToInt = std::dynamic_pointer_cast<IntValue>(condition);
    while(conditionToInt->value != 0) {
        whileExpression->right->accept(this);
        whileExpression->left->accept(this);
        auto currentCondition = operands.front();
        operands.pop();
        conditionToInt = std::dynamic_pointer_cast<IntValue>(currentCondition);
    }

}

void EvaluationVisitor::visit(DoExpression *doExpression) {

}

void EvaluationVisitor::visit(FunctionCallExpression *functionCallExpression) {

    auto funcNameExpression = functionCallExpression->left;
    auto funcName = std::dynamic_pointer_cast<VarNameExpression>(funcNameExpression)->value;

    if(functionDeclarationMap.find(funcName) == functionDeclarationMap.end()) {
        throw std::runtime_error("Function not defined");
    }

    functionCallExpression->right->accept(this);
    auto functionDeclaration = functionDeclarationMap[funcName];

    if(operands.size() != functionDeclaration.args.size()) {
        throw std::runtime_error("Wrong number of arguments");
    }

    auto currentArg = functionDeclaration.args.cbegin();
    while(!operands.empty()) {
        auto calledArg = operands.front();
        auto isInt = std::dynamic_pointer_cast<IntValue>(calledArg);
        auto isReal = std::dynamic_pointer_cast<RealValue>(calledArg);
        auto isStr = std::dynamic_pointer_cast<StrValue>(calledArg);

        if(isInt && currentArg->specifier != "int") {
            throw std::runtime_error("Arg mismatch in function " + funcName + " call.");
        }

        if(isReal && currentArg->specifier != "float") {
            throw std::runtime_error("Arg mismatch in function " + funcName + " call.");
        }

        if(isStr && currentArg->specifier != "string") {
            throw std::runtime_error("Arg mismatch in function " + funcName + " call.");
        }
        operands.pop();
        currentArg++;

        if(currentArg == functionDeclaration.args.cend()) {
            break;
        }
    }

    functionDeclaration.body->accept(this);

}

void EvaluationVisitor::visit(FileExpression *fileExpression) {
    std::cout << "Visiting file\n";
    for(auto it : fileExpression->roots) {
        it->accept(this);
    }

}

void EvaluationVisitor::visit(FieldReferenceExpression *fieldReferenceExpression) {

}

void EvaluationVisitor::visit(PutExpression *putExpression) {
    putExpression->toPrint->accept(this);
    auto valueToPrint = operands.front();

    operands.pop();
    auto toInt = std::dynamic_pointer_cast<IntValue>(valueToPrint);
    auto toReal = std::dynamic_pointer_cast<RealValue>(valueToPrint);
    auto toStr = std::dynamic_pointer_cast<StrValue>(valueToPrint);


    if(toInt) {
        std::cout << toInt->value << " of int type.";
    }
    if(toReal) {
        std::cout << toReal->value << " of real type.";
    }
    if(toStr) {
        if(declarationMap.find(toStr->value) == declarationMap.end()
            && functionDeclarationMap.find(toStr->value) == functionDeclarationMap.end()) {
            throw std::runtime_error(toStr->value + " undefined");
        }

        if(functionDeclarationMap.find(toStr->value) != functionDeclarationMap.end()) {
            std::cout << toStr->value << " is a function with:\n";
            auto func = functionDeclarationMap[toStr->value];
            std::cout << "\t" << func.specifier << " specifier\n";
            std::cout << "and args:\n";
            for(auto [specifier, name] : func.args) {
                std::cout << "\t" << specifier << " " << name << '\n';
            }
            return;
        }

        if(variableAssignmentMap.find(toStr->value) == variableAssignmentMap.end()) {
            std::cout << "no value assigned to " + toStr->value + " variable.\n";
            return;
        }
        auto value = variableAssignmentMap[toStr->value];
        auto toIntValue = std::dynamic_pointer_cast<IntValue>(value);
        auto toRealValue = std::dynamic_pointer_cast<RealValue>(value);
        auto toStrValue = std::dynamic_pointer_cast<StrValue>(value);

        if(toIntValue) {
            std::cout << toIntValue->value << " of int type.";
        }
        if(toRealValue) {
            std::cout << toRealValue->value << " of real type.";
        }
        if(toStrValue) {
            std::cout << toStrValue->value << " of string type";
        }
    }

}
