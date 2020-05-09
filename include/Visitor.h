//
// Created by robert on 06.05.2020.
//

#ifndef TKOM_VISITOR_H
#define TKOM_VISITOR_H

#include <memory>
#include <stack>
#include <queue>

struct VarDeclarationExpression;
struct TypeSpecifierExpression;
//lexical expression
struct VarNameExpression;
struct RootExpression;
//numeric expressions
struct IntExpression;
struct FloatExpression;

// generic structure for double args expressions
struct DoubleArgsExpression;
// numeric operations expressions
struct AdditionExpression;
struct SubtractExpression;
struct BooleanAndExpression;
struct BooleanOrExpression;
struct BooleanOperatorExpression;
struct MultiplyExpression;
struct DivideExpression;
// other
struct AssignExpression;
struct FunctionArgExpression;
struct FunctionExpression;

struct Visitor {
    // visit root
    virtual void visit(RootExpression* rootExpression) = 0;

    // numeric and lexical storage
    virtual void visit(IntExpression* intExpression) = 0;
    virtual void visit(FloatExpression* floatExpression) = 0;
    virtual void visit(VarNameExpression* varNameExpression) = 0;

    virtual void visit(DoubleArgsExpression* doubleArgsExpression) = 0;
    // numeric operations
    virtual void visit(AdditionExpression* additionExpression) = 0;
    virtual void visit(MultiplyExpression* multiplyExpression) = 0;
    virtual void visit(DivideExpression* divideExpression) = 0;

    // other
    virtual void visit(AssignExpression* assignExpression) = 0;
    virtual void visit(VarDeclarationExpression* varDeclarationExpression) = 0;
    virtual void visit(TypeSpecifierExpression* typeSpecifierExpression) = 0;

    // boolean
    virtual void visit(BooleanAndExpression* booleanAndExpression) = 0;
    virtual void visit(BooleanOrExpression* booleanOrExpression) = 0;
    virtual void visit(BooleanOperatorExpression* booleanOrExpression) = 0;
    virtual void visit(FunctionArgExpression* functionArgExpression) = 0;
    virtual void visit(FunctionExpression* functionExpression) = 0;
};

struct ExpressionVisitor : Visitor {
    void visit(IntExpression* intExpression) override;
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
};

struct Expression {
    virtual void accept(Visitor* visitor) = 0;
};
struct RootExpression : Expression {
    std::shared_ptr<Expression> next;
    RootExpression() = default;
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
struct TypeSpecifierExpression : Expression {
    std::string value;
    TypeSpecifierExpression(std::string value) : value(value) {}
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

struct BooleanOperatorExpression : DoubleArgsExpression {
    std::string value;
    BooleanOperatorExpression(std::string value) :
        value(value) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
struct FunctionExpression : DoubleArgsExpression {
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
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};



//struct FunctionExpression : Expression {
//    Expression *name;
//    std::queue<Expression*> args;
//    void accept(Visitor* visitor) override {
//        visitor->visit(this);
//    }
//};

#endif //TKOM_VISITOR_H
