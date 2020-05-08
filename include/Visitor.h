//
// Created by robert on 06.05.2020.
//

#ifndef TKOM_VISITOR_H
#define TKOM_VISITOR_H

#include <memory>

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
struct MultiplyExpression;
struct DivideExpression;
// other
struct AssignExpression;

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

    //other
    virtual void visit(AssignExpression* assignExpression) = 0;
};

struct ExpressionVisitor : Visitor {
    // numeric and lexical storage
    static unsigned int num;
    ExpressionVisitor() {
        num = 1;
    }

    void printTabs(unsigned int num) {
        while(num--) {
            std::cout << '\t';
        }
    }
    void visit(IntExpression* intExpression) override;
    void visit(FloatExpression* floatExpression) override;
    void visit(VarNameExpression* varNameExpression)  override;
    void visit(DoubleArgsExpression* doubleArgsExpression) override;
    void visit(AdditionExpression* additionExpression) override;
    void visit(MultiplyExpression* multiplyExpression)  override;
    void visit(DivideExpression* divideExpression) override;
    void visit(AssignExpression* assignExpression) override;
    void visit(RootExpression* rootExpression) override;
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

struct DoubleArgsExpression : Expression {
    std::shared_ptr<Expression> left{}, right{};
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

#endif //TKOM_VISITOR_H
