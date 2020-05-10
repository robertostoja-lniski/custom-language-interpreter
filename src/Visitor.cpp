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
