//
// Created by robert on 02.06.2020.
//

#ifndef TKOM_EXPRESSIONS_H
#define TKOM_EXPRESSIONS_H
#include <iostream>
#include <memory>
#include <stack>
#include <queue>
#include <variant>
#include <string>
#include <cassert>
#include <map>
#include <thread>
#include <zconf.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <sys/wait.h>
#include "Visitor.h"
struct Expression {
    virtual void accept(Visitor* visitor) = 0;
};
struct DoExpression : Expression {
    // simple boundary for done.
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FileExpression : Expression {
    std::deque <std::shared_ptr<RootExpression>> roots;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct NoArgFunctionExpression : Expression {
    std::string name;
    NoArgFunctionExpression(std::string name) : name(name) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct IntExpression : Expression {
    int value{};
    IntExpression(int value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct StringExpression : Expression {
    std::string value{};
    StringExpression(std::string value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct FloatExpression : Expression {
    double value{};
    FloatExpression(double value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct VarNameExpression : Expression {
    std::string value;
    VarNameExpression(std::string value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct PutExpression : Expression {
    std::shared_ptr<Expression> toPrint {};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct RetExpression : Expression {
    std::shared_ptr<Expression> toRet {};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct DoubleArgsExpression : Expression {
    std::shared_ptr<Expression> left{}, right{};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct WhileExpression : Expression {
    std::shared_ptr<Expression> condition {nullptr};
    std::shared_ptr<BodyExpression> block {nullptr};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct IfExpression : Expression {
    std::shared_ptr<Expression> condition {nullptr};
    std::shared_ptr<BodyExpression> ifBlock {nullptr};
    std::shared_ptr<BodyExpression> elseBlock {nullptr};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct TypeSpecifierExpression : Expression {
    std::string specifierName;
    std::string varName;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct RootExpression : Expression {
    std::shared_ptr<Expression> expr;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct BodyExpression:Expression {
    std::deque<std::shared_ptr<Expression>> statements;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct ElseExpression : Expression {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct NewLineExpression : DoubleArgsExpression {
    std::shared_ptr<Expression> left{}, right{};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct BooleanOperatorExpression : DoubleArgsExpression {
    std::string value;
    BooleanOperatorExpression(std::string value) :
            value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FunctionExpression : DoubleArgsExpression {
    std::string specifier;
    std::string name;
    std::shared_ptr<BodyExpression> body;
    std::shared_ptr<BodyExpression> args;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FunctionCallExpression : Expression {
    std::string name;
    std::shared_ptr<Expression> argListHead;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct AdditionExpression : DoubleArgsExpression {
    std::string operation;
    AdditionExpression(std::string operation) : operation(operation) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct VarDeclarationExpression : DoubleArgsExpression {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct DivideExpression : DoubleArgsExpression {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct MultiplyExpression : DoubleArgsExpression {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct AssignExpression : Expression {
    std::string variable;
    // optional
    std::string fieldReference;
    std::shared_ptr<Expression> toAssign;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct BooleanOrExpression : DoubleArgsExpression {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct BooleanAndExpression : DoubleArgsExpression {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FunctionArgExpression : DoubleArgsExpression {
    FunctionArgExpression() {
        right = nullptr;
    }
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FieldReferenceExpression : Expression {
    std::string varName;
    std::string refName;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct SystemHandlerDeclExpression : Expression {
    std::shared_ptr<VarNameExpression> name;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
#endif //TKOM_EXPRESSIONS_H
