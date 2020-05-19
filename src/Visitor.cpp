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
    auto varName = varNameExpression->value;
    if(variableAssignmentMap.find(varName) == variableAssignmentMap.end()) {
        throw std::runtime_error(varName + " is not defined.");
    }

    auto assignedVar = variableAssignmentMap[varName];
    operands.push(assignedVar);
}

void EvaluationVisitor::visit(DoubleArgsExpression *doubleArgsExpression) {

}

void EvaluationVisitor::visit(AdditionExpression *additionExpression) {
    std::cout << "Evaluating multiplying\n";
    additionExpression->left->accept(this);
    additionExpression->right->accept(this);

    std::shared_ptr<PrimitiveValue> leftOperand = operands.front();
    operands.pop();
    std::shared_ptr<PrimitiveValue> rightOperand = operands.front();
    operands.pop();

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

    operands.front();
    variableAssignmentMap[varName] = valueToBeAssigned;
}

void EvaluationVisitor::visit(RootExpression *rootExpression) {
    rootExpression->expr->accept(this);
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
//    typeSpecifierExpression->right->accept(this);
    auto varName = operands.front();
    auto strVarName = std::dynamic_pointer_cast<StrValue>(varName);
    if(!strVarName) {
        throw std::runtime_error("Unknown token to be declared");
    }
    operands.pop();
    declarationMap[strVarName->value] = typeSpecifierExpression->value;
}

void EvaluationVisitor::visit(BooleanAndExpression *booleanAndExpression) {

}

void EvaluationVisitor::visit(BooleanOrExpression *booleanOrExpression) {

}

void EvaluationVisitor::visit(BooleanOperatorExpression *booleanOrExpression) {

}

void EvaluationVisitor::visit(FunctionArgExpression *functionArgExpression) {

}

void EvaluationVisitor::visit(FunctionExpression *functionExpression) {

}

void EvaluationVisitor::visit(NoArgFunctionExpression *noArgFunctionExpression) {

}

void EvaluationVisitor::visit(NewLineExpression *newLineExpression) {

}

void EvaluationVisitor::visit(BodyExpression *bodyExpression) {

}

void EvaluationVisitor::visit(IfExpression *ifExpression) {

}

void EvaluationVisitor::visit(ElseExpression *elseExpression) {

}

void EvaluationVisitor::visit(ForExpression *forExpression) {

}

void EvaluationVisitor::visit(WhileExpression *whileExpression) {

}

void EvaluationVisitor::visit(DoExpression *doExpression) {

}

void EvaluationVisitor::visit(FileExpression *fileExpression) {
    std::cout << "Visiting file\n";
    for(auto it : fileExpression->roots) {
        it->accept(this);
    }

}

void EvaluationVisitor::visit(FieldReferenceExpression *fieldReferenceExpression) {

}
