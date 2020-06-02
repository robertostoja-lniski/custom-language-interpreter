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
struct VarDeclarationStatement;
struct TypeSpecifierStatement;
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
// functions
struct FunctionArgExpression;
struct FunctionExpression;
struct FunctionCallExpression;
struct NoArgFunctionExpression;
// file organisation
struct NewLineOperator;
struct BodyStatement;
struct DoNode;
struct FileExpression;
struct SystemHandlerDeclStatement;

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
    virtual void visit(VarDeclarationStatement* varDeclarationExpression) = 0;
    virtual void visit(TypeSpecifierStatement* typeSpecifierExpression) = 0;

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
    virtual void visit(NewLineOperator* newLineExpression) = 0;
    virtual void visit(BodyStatement* bodyExpression) = 0;
    virtual void visit(DoNode* doExpression) = 0;

    //keywords
    virtual void visit(IfExpression* ifExpression) = 0;
    virtual void visit(ElseExpression* elseExpression) = 0;
    virtual void visit(WhileExpression* whileExpression) = 0;
    virtual void visit(SystemHandlerDeclStatement* systemHandlerDeclExpression) = 0;
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
    void visit(VarDeclarationStatement* varDeclarationExpression) override;
    void visit(TypeSpecifierStatement* typeSpecifierExpression) override;
    void visit(BooleanAndExpression* booleanAndExpression) override;
    void visit(BooleanOrExpression* booleanOrExpression) override;
    void visit(BooleanOperatorExpression* booleanOrExpression) override;
    void visit(FunctionArgExpression* functionArgExpression) override;
    void visit(FunctionExpression* functionExpression) override;
    void visit(FunctionCallExpression* functionCallExpression) override;
    void visit(NoArgFunctionExpression* noArgFunctionExpression) override;
    void visit(NewLineOperator* newLineExpression) override;
    void visit(BodyStatement* bodyExpression) override;
    void visit(IfExpression* ifExpression) override;
    void visit(ElseExpression* elseExpression) override;
    void visit(WhileExpression* whileExpression) override;
    void visit(DoNode* doExpression) override;
    void visit(FileExpression* fileExpression) override;
    void visit(FieldReferenceExpression* fieldReferenceExpression) override;
    void visit(PutExpression* putExpression) override;
    void visit(RetExpression* retExpression) override;
    void visit(SystemHandlerDeclStatement* systemHandlerDeclExpression) override;
};

struct Node {
    virtual void accept(Visitor* visitor) = 0;
};
struct DoNode : Node {
    // simple boundary for done.
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FileExpression : Node {
    std::deque <std::shared_ptr<RootExpression>> roots;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct NoArgFunctionExpression : Node {
    std::string name;
    NoArgFunctionExpression(std::string name) : name(name) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct IntExpression : Node {
    int value{};
    IntExpression(int value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct StringExpression : Node {
    std::string value{};
    StringExpression(std::string value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct FloatExpression : Node {
    double value{};
    FloatExpression(double value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct VarNameExpression : Node {
    std::string value;
    VarNameExpression(std::string value) : value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct PutExpression : Node {
    std::shared_ptr<Node> toPrint {};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct RetExpression : Node {
    std::shared_ptr<Node> toRet {};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct DoubleArgsExpression : Node {
    std::shared_ptr<Node> left{}, right{};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct WhileExpression : Node {
    std::shared_ptr<Node> condition {nullptr};
    std::shared_ptr<BodyStatement> block {nullptr};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct IfExpression : Node {
    std::shared_ptr<Node> condition {nullptr};
    std::shared_ptr<BodyStatement> ifBlock {nullptr};
    std::shared_ptr<BodyStatement> elseBlock {nullptr};
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct TypeSpecifierStatement : Node {
    std::string specifierName;
    std::string varName;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

struct RootExpression : Node {
    std::shared_ptr<Node> expr;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct BodyStatement: Node {
    std::deque<std::shared_ptr<Node>> statements;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct ElseExpression : Node {
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct NewLineOperator : DoubleArgsExpression {
    std::shared_ptr<Node> left{}, right{};
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
    std::shared_ptr<BodyStatement> body;
    std::shared_ptr<BodyStatement> args;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FunctionCallExpression : Node {
    std::string name;
    std::shared_ptr<Node> argListHead;
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
struct VarDeclarationStatement : DoubleArgsExpression {
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
struct AssignExpression : Node {
    std::string variable;
    // optional
    std::string fieldReference;
    std::shared_ptr<Node> toAssign;
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
struct FieldReferenceExpression : Node {
    std::string varName;
    std::string refName;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct SystemHandlerDeclStatement : Node {
    std::shared_ptr<VarNameExpression> name;
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

#endif //TKOM_VISITOR_H
