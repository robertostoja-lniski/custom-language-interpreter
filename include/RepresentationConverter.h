//
// Created by robert on 08.05.2020.
//

#ifndef TKOM_REPRESENTATIONCONVERTER_H
#define TKOM_REPRESENTATIONCONVERTER_H


class RepresentationConverter {

private:
    // operators by priority
    std::map<Type, int> prioritiesIn {
            {T_ADD_OPERATOR, 1},
            {T_MULT_OPERATOR, 2},
            {T_OPENING_PARENTHESIS, 0}
    };

    std::map<Type, int> prioritiesOut {
            {T_ADD_OPERATOR, 0},
            {T_MULT_OPERATOR, 1},
            {T_OPENING_PARENTHESIS, INT_MAX}
    };

    std::stack <Token> operators;
    std::queue <Token> postfixRepresentation;

    void handleOperatorToken(Token token) {
        // to new function for a better readability
        auto currentType = token.getType();
        // should be a do while
        // not a clean code, to be rewritten soon
        if(operators.empty() || prioritiesOut[currentType] > prioritiesIn[operators.top().getType()]) {
            operators.push(token);
        } else {
            while(!operators.empty() && prioritiesOut[currentType] < prioritiesIn[operators.top().getType()]) {
                postfixRepresentation.push(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    void handleEmbeddedExpression() {
        while(!operators.empty() && operators.top().getType() != T_OPENING_PARENTHESIS) {
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
            std::cout << copiedRepresentation.front().getValue() << ' ';
            copiedRepresentation.pop();
        }
    }

    std::queue<Token> getPostfixRepresentation() {
        finalize();
        printPostfix();
        return postfixRepresentation;
    }

    void generatePostfixRepresentation(Token token) {

        if(token.isOperand()) {
            // should be handle etc..
            postfixRepresentation.push(std::move(token));
        } else if(token.isOperator()) {
            handleOperatorToken(token);
        } else if(token.isClosingParenthesis()) {
            handleEmbeddedExpression();
        }

    }
};


#endif //TKOM_REPRESENTATIONCONVERTER_H
