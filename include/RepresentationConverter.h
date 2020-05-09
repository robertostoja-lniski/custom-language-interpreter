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
            {T_ADD_OPERATOR, 1},
            {T_MULT_OPERATOR, 2},
            {T_BOOLEAN_OPERATOR, 3},
            {T_BOOLEAN_OR, 4},
            {T_BOOLEAN_AND, 5},
            {T_SEMICON, 6},
            {T_OPENING_PARENTHESIS, 0}
    };

    std::map<Type, int> prioritiesOut {
            {T_ADD_OPERATOR, 0},
            {T_MULT_OPERATOR, 1},
            {T_BOOLEAN_OPERATOR, 2},
            {T_BOOLEAN_OR, 3},
            {T_BOOLEAN_AND, 4},
            {T_SEMICON, 6},
            {T_OPENING_PARENTHESIS, INT_MAX}
    };

    std::stack <std::shared_ptr<Token>> operators;
    std::queue <std::shared_ptr<Token>> postfixRepresentation;

    void handleOperatorToken(Token token) {
        // to new function for a better readability
        auto currentType = token.getType();
        // should be a do while
        // not a clean code, to be rewritten soon
        if(operators.empty() || prioritiesOut[currentType] > prioritiesIn[operators.top()->getType()]) {
            operators.push(std::make_shared<Token>(token));
        } else {
            while(!operators.empty() && prioritiesOut[currentType] < prioritiesIn[operators.top()->getType()]) {
                postfixRepresentation.push(operators.top());
                operators.pop();
            }
            operators.push(std::make_shared<Token>(token));
        }
    }

    void handleEmbeddedExpression() {
        if(operators.empty()) {
            return;
        }

        while(operators.top()->getType() != T_OPENING_PARENTHESIS) {
            postfixRepresentation.push(operators.top());
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
            postfixRepresentation.push(operators.top());
            operators.pop();
        }
    }

public:


    void printPostfix() {
        // should be iterator - to be changed soon
        auto copiedRepresentation = postfixRepresentation;
        while(!copiedRepresentation.empty()) {
            std::cout << copiedRepresentation.front()->getValue() << ' ';
            copiedRepresentation.pop();
        }
    }
    std::queue<std::shared_ptr<Token>> getPostfixRepresentation() {

        finalize();
        printPostfix();
        return postfixRepresentation;
    }
    bool tryToGenerateFunctionCall(Token token) {
        if(token.getType() == T_OPENING_PARENTHESIS) {
            auto lastExpression = postfixRepresentation.back();
            if(lastExpression->getType() == T_USER_DEFINED_NAME) {
                lastExpression->setType(T_FUNCTION_NAME);
                operators.push(std::make_shared<Token>(token));
                return true;
            }
        }
        return false;
    }

    void generatePostfixRepresentation(Token token) {

        if (token.isOperand()) {
            // should be handle etc..
            postfixRepresentation.push(std::make_unique<Token>(token));
        } else if (token.isOperator() || token.getValue() == "." || token.getValue() == ",") {
            handleOperatorToken(token);
        } else if (token.isClosingParenthesis()) {
            handleEmbeddedExpression();
        }
    }
};

#endif //TKOM_REPRESENTATIONCONVERTER_H
