//
// Created by robert on 08.05.2020.
//

#ifndef TKOM_REPRESENTATIONCONVERTER_H
#define TKOM_REPRESENTATIONCONVERTER_H
#include "Visitor.h"

class RepresentationConverter {

private:
    // operators by priority
    std::map<Type, int> prioritiesIn {

            {T_SEMICON, 4},
            {T_BOOLEAN_OPERATOR, 5},
            {T_ADD_OPERATOR, 6},
            {T_MULT_OPERATOR, 7},
            {T_BOOLEAN_OR, 8},
            {T_BOOLEAN_AND, 9},
            {T_FUNCTION_NAME, 10},
            {T_FOR, 10},
            {T_IF, 12},
            {T_WHILE, 13},
            {T_NEXT_LINE, 14},
            {T_OPENING_PARENTHESIS, 0}
    };

    std::map<Type, int> prioritiesOut {
            {T_NEXT_LINE, 2},
            {T_SEMICON, 3},
            {T_BOOLEAN_OPERATOR, 4},
            {T_ADD_OPERATOR, 5},
            {T_MULT_OPERATOR, 6},
            {T_BOOLEAN_OR, 7},
            {T_BOOLEAN_AND, 8},
            {T_FUNCTION_NAME, 9},
            {T_FOR,10},
            {T_IF, 11},
            {T_WHILE, 12},
            {T_NEXT_LINE, 13},
            {T_OPENING_PARENTHESIS, INT_MAX}
    };

    std::stack <std::shared_ptr<Token>> operators;
    std::deque <std::shared_ptr<Token>> postfixRepresentation;

    void handleOperatorToken(Token token) {
        // to new function for a better readability
        auto currentType = token.getType();
        // should be a do while
        // not a clean code, to be rewritten soon
        if(operators.empty() || prioritiesOut[currentType] > prioritiesIn[operators.top()->getType()]) {
            operators.push(std::make_shared<Token>(token));
        } else {
            while(!operators.empty() && prioritiesOut[currentType] < prioritiesIn[operators.top()->getType()]) {
                postfixRepresentation.push_back(operators.top());
                operators.pop();
            }
            operators.push(std::make_shared<Token>(token));
        }
    }

    void handleEmbeddedExpression() {
        if(operators.empty()) {
            return;
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

            return;
        }

        while(operators.top()->getType() != T_OPENING_PARENTHESIS) {
            postfixRepresentation.push_back(operators.top());
            operators.pop();

            if(operators.empty()) {
                throw std::runtime_error("Cannot find opening parenthesis");
            }
        }
        operators.pop();
    }

    void finalize() {
        // ugly as hell
        while(!operators.empty()) {
            postfixRepresentation.push_back(operators.top());
            operators.pop();
        }
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
    bool tryToGenerateFunctionCall(Token token) {
        if(postfixRepresentation.empty()) {
            return false;
        }
        if(token.getType() == T_OPENING_PARENTHESIS) {
            auto lastExpression = postfixRepresentation.back();
            if(lastExpression && lastExpression->getType() == T_USER_DEFINED_NAME) {
                lastExpression->setType(T_FUNCTION_NAME);
                postfixRepresentation.pop_back();
                handleOperatorToken(*lastExpression);
                handleOperatorToken(token);
                return true;
            }
        }
        return false;
    }
    bool tryToGenerateCondition(Token token) {
        // hehe terrible, why not to call handle operator ?
        if(token.isCondition()) {
            handleOperatorToken(token);
            return true;
        }
        return false;
    }
    void handleNextLine(Token token) {
        finalize();
        postfixRepresentation.push_back(std::make_unique<Token>(token));
    }

    void generatePostfixRepresentation(Token token) {
        if(token.getType() == T_NEXT_LINE) {
            handleNextLine(token);
            return;
        }
        if (token.isOperand()) {
            // should be handle etc..
            postfixRepresentation.push_back(std::make_unique<Token>(token));
        } else if (token.isOperator() || token.getValue() == "."
                || token.getValue() == ",") {
            handleOperatorToken(token);
        } else if (token.isClosingParenthesis()) {
            handleEmbeddedExpression();
        }
    }
};

#endif //TKOM_REPRESENTATIONCONVERTER_H
