//
// Created by robert on 11.05.2020.
//

#ifndef TKOM_DECLARATIONREADER_H
#define TKOM_DECLARATIONREADER_H

#include "Scanner.h"

class DeclarationReader {

private:
    std::shared_ptr<Scanner> scanner;
    Token getTokenValFromScanner() {
        if(!scanner) {
            throw std::runtime_error("No scanner pointed");
        }
        scanner->getNextToken();
        scanner->readToken();
        return scanner->getTokenValue();
    }

public:
    DeclarationReader(std::shared_ptr<Scanner> scanner) {
        this->scanner = scanner;
    }
    std::shared_ptr<RootExpression> tryToBuildDeclaration(Token token) {
        if(token.getType() == T_SPECIFIER) {
            auto specifierExpr = getExpressionWithAssignedSpecifier(token);
            auto nextToken = getTokenValFromScanner();

            if(nextToken.getType() == T_OPENING_PARENTHESIS) {
                auto body = getParamsAsManyDeclarations(token);
                specifierExpr->right = body;
            }
            auto newRoot = std::make_shared<RootExpression>();
            newRoot->expr = specifierExpr;
            return newRoot;
        }
        return nullptr;
    }

    std::shared_ptr<TypeSpecifierExpression> getExpressionWithAssignedSpecifier(Token token) {
        auto specifierExpr = std::make_shared<TypeSpecifierExpression>(token.getValue());
        auto shouldBeIdentToken = getTokenValFromScanner();
        if(shouldBeIdentToken.getType() != T_USER_DEFINED_NAME || shouldBeIdentToken.getValue() == "$") {
            throw std::runtime_error("Type specifier without ident");
        }
        specifierExpr->left = std::make_shared<VarNameExpression>(shouldBeIdentToken.getValue());
        return specifierExpr;
    }
    std::shared_ptr<BodyExpression> getParamsAsManyDeclarations(Token nextToken) {
        auto argBlock = std::make_shared<BodyExpression>();
        while(nextToken.getType() != T_CLOSING_PARENTHESIS) {

            nextToken = getTokenValFromScanner();
            if(nextToken.getType() == T_CLOSING_PARENTHESIS) {
                return argBlock;
            }
            if(nextToken.getType() == T_SEMICON) {
                continue;
            }

            auto currentArg = std::make_shared<TypeSpecifierExpression>(nextToken.getValue());
            nextToken = getTokenValFromScanner();
            auto currentArgName = std::make_shared<VarNameExpression>(nextToken.getValue());

            currentArg->left = currentArgName;
            argBlock->statements.push_back(currentArg);
        }
        return nullptr;
    }
};
#endif //TKOM_DECLARATIONREADER_H
