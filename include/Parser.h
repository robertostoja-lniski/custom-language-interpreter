//
// Created by robert on 06.05.2020.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H
#include "Token.h"
#include <memory>
#include <stack>
#include <vector>
#include <map>
#include <functional>
#include <queue>
#include "boost/lexical_cast.hpp"
#include "RepresentationConverter.h"
#include "Visitor.h"
using boost::lexical_cast;

class Parser {
private:
    //tmp just for one subtree
    std::unique_ptr<RepresentationConverter> converter;
    // right not used
    std::shared_ptr<RootExpression> root;
    std::stack <std::shared_ptr<Expression>> recentExpressions;

    void tryToBuildExpression(Token token);
    void createAndAddIntExpression(Token token);
    void createAndAddFloatExpression(Token token);
    void createAndAddAdditionExpression(Token token);
    void createAndAddMultExpression(Token token);
    void createAndAddAssignExpression(Token token);
    void createAndAddVarNameExpression(Token token);
    void addDoubleArgsExpression(std::unique_ptr<DoubleArgsExpression> doubleArgsExpression);

    std::map<Type, std::function<void(Token)>> tokensToNode {
            {T_INT_NUM, [&](Token token) {createAndAddIntExpression(token);}},
            {T_REAL_NUM, [&](Token token) {createAndAddFloatExpression(token);}},
            {T_ADD_OPERATOR, [&](Token token) {createAndAddAdditionExpression(token);}},
            {T_MULT_OPERATOR, [&](Token token) {createAndAddMultExpression(token);}},
            {T_ASSIGN_OPERATOR, [&](Token token) {createAndAddAssignExpression(token);}},
            {T_USER_DEFINED_NAME, [&](Token token) {createAndAddVarNameExpression(token);}},
    };

public:
    void parseToken(Token tokenToParse);
    Parser() { converter = std::make_unique<RepresentationConverter>(); };
    void generateTree();
    void analyzeTree();
};


#endif //TKOM_PARSER_H
