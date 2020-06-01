//
// Created by robert on 06.05.2020.
//

#ifndef TKOM_VISITOR_H
#define TKOM_VISITOR_H
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

struct FieldReferenceExpression;
struct VarDeclarationExpression;
struct TypeSpecifierExpression;
struct PutExpression;
// lexical expression
struct VarNameExpression;
struct RootExpression;
// numeric expressions
struct IntExpression;
struct FloatExpression;
struct RetExpression;
struct StringExpression;
// Secial words
struct IfExpression;
struct ElseExpression;
struct WhileExpression;

// generic structure for double args expressions
struct DoubleArgsExpression;
// numeric operations expressions
struct AdditionExpression;
struct BooleanAndExpression;
struct BooleanOrExpression;
struct BooleanOperatorExpression;
struct MultiplyExpression;
struct DivideExpression;
// other
struct AssignExpression;
struct DeclarationExpression;
// functions
struct FunctionArgExpression;
struct FunctionExpression;
struct FunctionCallExpression;
struct NoArgFunctionExpression;
// file organisation
struct NewLineExpression;
struct BodyExpression;
struct DoExpression;
struct FileExpression;
struct SystemHandlerExpression;
struct SystemHandlerDeclExpression;

struct Visitor {
    // visit root
    virtual void visit(RootExpression* rootExpression) = 0;
    virtual void visit(FileExpression* fileExpression) = 0;

    // numeric and lexical storage
    virtual void visit(IntExpression* intExpression) = 0;
    virtual void visit(FloatExpression* floatExpression) = 0;
    virtual void visit(StringExpression* stringExpression) = 0;
    virtual void visit(VarNameExpression* varNameExpression) = 0;
    virtual void visit(DoubleArgsExpression* doubleArgsExpression) = 0;

    // numeric operations
    virtual void visit(AdditionExpression* additionExpression) = 0;
    virtual void visit(MultiplyExpression* multiplyExpression) = 0;
    virtual void visit(DivideExpression* divideExpression) = 0;

    // other
    virtual void visit(FieldReferenceExpression* fieldReferenceExpression) = 0;
    virtual void visit(AssignExpression* assignExpression) = 0;
    virtual void visit(VarDeclarationExpression* varDeclarationExpression) = 0;
    virtual void visit(TypeSpecifierExpression* typeSpecifierExpression) = 0;

    // boolean
    virtual void visit(BooleanAndExpression* booleanAndExpression) = 0;
    virtual void visit(BooleanOrExpression* booleanOrExpression) = 0;
    virtual void visit(BooleanOperatorExpression* booleanOrExpression) = 0;

    // functions
    virtual void visit(FunctionCallExpression* functionCallExpression) = 0;
    virtual void visit(FunctionArgExpression* functionArgExpression) = 0;
    virtual void visit(FunctionExpression* functionExpression) = 0;
    virtual void visit(NoArgFunctionExpression* noArgFunctionExpression) = 0;
    virtual void visit(PutExpression* putExpression) = 0;
    virtual void visit(RetExpression* retExpression) = 0;

    // file organisation
    virtual void visit(NewLineExpression* newLineExpression) = 0;
    virtual void visit(BodyExpression* bodyExpression) = 0;
    virtual void visit(DoExpression* doExpression) = 0;

    //keywords
    virtual void visit(IfExpression* ifExpression) = 0;
    virtual void visit(ElseExpression* elseExpression) = 0;
    virtual void visit(WhileExpression* whileExpression) = 0;
    virtual void visit(SystemHandlerExpression* systemHandlerExpression) = 0;
    virtual void visit(SystemHandlerDeclExpression* systemHandlerDeclExpression) = 0;
};

struct ExpressionVisitor : Visitor {
    void visit(IntExpression* intExpression) override;
    void visit(StringExpression* stringExpression) override;
    void visit(FloatExpression* floatExpression) override;
    void visit(VarNameExpression* varNameExpression)  override;
    void visit(DoubleArgsExpression* doubleArgsExpression) override;
    void visit(AdditionExpression* additionExpression) override;
    void visit(MultiplyExpression* multiplyExpression)  override;
    void visit(DivideExpression* divideExpression) override;
    void visit(AssignExpression* assignExpression) override;
    void visit(RootExpression* rootExpression) override;
    void visit(VarDeclarationExpression* varDeclarationExpression) override;
    void visit(TypeSpecifierExpression* typeSpecifierExpression) override;
    void visit(BooleanAndExpression* booleanAndExpression) override;
    void visit(BooleanOrExpression* booleanOrExpression) override;
    void visit(BooleanOperatorExpression* booleanOrExpression) override;
    void visit(FunctionArgExpression* functionArgExpression) override;
    void visit(FunctionExpression* functionExpression) override;
    void visit(FunctionCallExpression* functionCallExpression) override;
    void visit(NoArgFunctionExpression* noArgFunctionExpression) override;
    void visit(NewLineExpression* newLineExpression) override;
    void visit(BodyExpression* bodyExpression) override;
    void visit(IfExpression* ifExpression) override;
    void visit(ElseExpression* elseExpression) override;
    void visit(WhileExpression* whileExpression) override;
    void visit(DoExpression* doExpression) override;
    void visit(FileExpression* fileExpression) override;
    void visit(FieldReferenceExpression* fieldReferenceExpression) override;
    void visit(PutExpression* putExpression) override;
    void visit(RetExpression* retExpression) override;
    void visit(SystemHandlerExpression* systemHandlerExpression) override;
    void visit(SystemHandlerDeclExpression* systemHandlerDeclExpression) override;
};

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
struct AssignExpression : DoubleArgsExpression {
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
struct FieldReferenceExpression : DoubleArgsExpression {
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

#endif //TKOM_VISITOR_H
