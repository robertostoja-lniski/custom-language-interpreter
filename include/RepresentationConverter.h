//
// Created by robert on 08.05.2020.
//

#ifndef TKOM_REPRESENTATIONCONVERTER_H
#define TKOM_REPRESENTATIONCONVERTER_H

#include <map>
#include <climits>
#include "Visitor.h"
#include "Token.h"
class RepresentationConverter {

private:
    // operators by priority
    struct Priority {
        int in;
        int out;
    };
    Token token;
    std::map<Type, Priority> priorities {
            {T_CON, {1,0}},
            {T_OPENING_PARENTHESIS, {0,INT_MAX}},
            {T_SEMICON, {2,1}},
            {T_SPECIFIER, {3,2}},
            {T_ASSIGN_OPERATOR,{4,3}},
            {T_BOOLEAN_OPERATOR, {5,4}},
            {T_ADD_OPERATOR, {6,5}},
            {T_MULT_OPERATOR, {7,5}},
            {T_BOOLEAN_OR, {8,7}},
            {T_BOOLEAN_AND, {9,8}},
            {T_FUNCTION_NAME, {10,9}},
            {T_SEMICON, {11,10}},
            {T_FOR,{12,11}},
            {T_IF, {13,12}},
            {T_ELSE, {14,13}},
            {T_WHILE, {15,14}},
            {T_DO, {16,15}},
            {T_DONE, {17,16}},
            {T_NEXT_LINE, {18,17}},
    };

    std::stack <std::shared_ptr<Token>> operators;
    std::deque <std::shared_ptr<Token>> postfixRepresentation;

    bool tryToHandleSpecialToken() {

        if(!token.isCondition() && !token.isOperator() && !token.isFunction()) {
            return false;
        }
        auto currentType = token.getType();

        if(operators.empty() || priorities[currentType].out > priorities[operators.top()->getType()].in) {
            operators.push(std::make_shared<Token>(token));
        } else {
            while(!operators.empty() && priorities[currentType].out < priorities[operators.top()->getType()].in) {
                postfixRepresentation.push_back(operators.top());
                operators.pop();
            }
            operators.push(std::make_shared<Token>(token));
        }
        return true;
    }
    bool tryToHandleEmbeddedExpression() {
        if(operators.empty() || token.getType()!=T_CLOSING_PARENTHESIS) {
            return false;
        }
        // should be do while
        // handle no-argument function
        if(operators.top()->getType() == T_OPENING_PARENTHESIS) {
            operators.pop();
            // check if it as no argument funtion
            // if so it can be treated as user defined name
            if(operators.size() && operators.top()->getType() == T_FUNCTION_NAME) {
                operators.top()->setType(T_NO_ARG_FUNCTION_NAME);
            }
            return true;
        }
        while(operators.top()->getType() != T_OPENING_PARENTHESIS) {
            postfixRepresentation.push_back(operators.top());
            operators.pop();

            if(operators.empty()) {
                throw std::runtime_error("Cannot find opening parenthesis");
            }
        }
        operators.pop();
        return true;
    }
    bool tryToHandleEmbeddedDo() {
        if(token.getType() != T_DO) {
            return false;
        }
        if(operators.empty()) {
            postfixRepresentation.push_back(std::make_shared<Token>(token));
            return true;
        }

        auto cond = operators.top();
        postfixRepresentation.push_back(cond);
        operators.pop();
        postfixRepresentation.push_back(std::make_shared<Token>(token));
        return true;
    }
    bool tryToHandleEmbeddedDone() {
        if(token.getType() != T_DONE) {
            return false;
        }
        while(!operators.empty()) {
            auto cond = operators.top();
            postfixRepresentation.push_back(cond);
            operators.pop();
        }
        postfixRepresentation.push_back(std::make_shared<Token>(token));
        return true;
    }
    void finalize() {
        // ugly as hell
        while(!operators.empty()) {
            postfixRepresentation.push_back(operators.top());
            operators.pop();
        }
    }
    bool tryToGenerateFunctionCall() {
        if(postfixRepresentation.empty()) {
            return false;
        }
        if(token.getType() == T_OPENING_PARENTHESIS) {
            auto lastExpression = postfixRepresentation.back();
            if(lastExpression && lastExpression->getType() == T_USER_DEFINED_NAME) {
                lastExpression->setType(T_FUNCTION_NAME);
                postfixRepresentation.pop_back();
                auto currentToken = token;
                token = *lastExpression;
                tryToHandleSpecialToken();
                token = currentToken;
                tryToHandleSpecialToken();

                return true;
            }
        }
        return false;
    }
    bool tryToGenerateCondition() {
        // treat conditions as operators
        if(token.isCondition()) {
            tryToHandleSpecialToken();
            return true;
        }
        return false;
    }
    bool tryToHandleNextLine() {
        if(token.getType() != T_NEXT_LINE) {
            return false;
        }
        finalize();
        postfixRepresentation.push_back(std::make_unique<Token>(token));
        return true;
    }
    bool tryToHandleOperand() {
        if (token.isOperand()) {
            postfixRepresentation.push_back(std::make_unique<Token>(token));
            return true;
        }
        return false;
    }
public:
    void printPostfix() {
        // should be iterator - to be changed soon
        auto copiedRepresentation = postfixRepresentation;
        while(!copiedRepresentation.empty()) {
            std::cout << copiedRepresentation.front()->getValue() << ' ';
            copiedRepresentation.pop_front();
        }
    }
    std::deque<std::shared_ptr<Token>> getPostfixRepresentation() {
        finalize();
        printPostfix();
        return postfixRepresentation;
    }
    bool generatePostfixRepresentation(Token token) {
        this->token = token;
        return tryToGenerateFunctionCall() || tryToGenerateCondition() || tryToHandleNextLine() || tryToHandleEmbeddedDo() || tryToHandleEmbeddedDone()
            || tryToHandleOperand() || tryToHandleSpecialToken() || tryToHandleEmbeddedExpression();
    }
};

#endif //TKOM_REPRESENTATIONCONVERTER_H
