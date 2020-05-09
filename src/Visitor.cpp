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
    rootExpression->next->accept(this);
}

void ExpressionVisitor::visit(VarDeclarationExpression *varDeclarationExpression) {
    std::cout << "Initialising: ";
    varDeclarationExpression->left->accept(this);
    varDeclarationExpression->right->accept(this);
}

void ExpressionVisitor::visit(TypeSpecifierExpression *typeSpecifierExpression) {
    std::cout << typeSpecifierExpression->value << '\n';
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
    std::cout << "In Boolean: " << booleanOperatorExpression->value;
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
    if(functionArgExpression->right) {
        functionArgExpression->right->accept(this);
    } else {
        std::cout << "End of args.\n";
    }
}

