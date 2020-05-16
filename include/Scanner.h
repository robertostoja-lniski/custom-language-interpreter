//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H

#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include "Configuration.h"
#include "Interfaces.h"
#include "Token.h"

class Scanner {

private:

    std::unique_ptr<SourceInterface> sourceInterface;
    std::queue<std::shared_ptr<Token>> tokens;
    off64_t position;
    char sign;
    bool isVerbose {false};

    void removeWhiteSigns();

    void createTokenFromValue(std::string val);
    std::shared_ptr<Token> createSpecialSignToken(std::string c);
    std::string appendValWhileIsDigit(std::string);

    bool tryToBuildSimpleToken();
    bool tryToBuildNumToken();
    bool tryToBuildAlphaTokens();
    bool tryToBuildNotDefinedToken();
    bool tryToBuildAssignmentOrBooleanToken();
    bool tryToBuildSpecialSignToken();

    std::map<std::string, std::function<void(std::string value)>> complexTokensHandlers {
            {"int", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER));}},
            {"unsigned_int", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER));}},
            {"float", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER));}},
            {"string", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER));}},
            {"system_handler", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER));}},
            {"while", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_WHILE));}},
            {"for", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_FOR));}},
            {"if", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_IF));}},
            {"do", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_DO));}},
            {"else", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_ELSE));}},
            {"done", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_DONE));}},
    };

    std::map<char, std::function<void(char currentSing)>> simpleTokensHandlers {
            {EOF, [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_END));}},
            {'*', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_MULT_OPERATOR));}},
            {'/', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_MULT_OPERATOR));}},
            {'&', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_BOOLEAN_AND));}},
            {'.', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_DOT));}},
            {'+', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_ADD_OPERATOR));}},
            {'-', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_ADD_OPERATOR));}},
            {'|', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_BOOLEAN_OR));}},
            {'?', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_NEXT_LINE));}},
            {')', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_CLOSING_PARENTHESIS));}},
            {'(', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_OPENING_PARENTHESIS));}},
            {'{', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_OPENING_BRACKET));}},
            {'}', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_CLOSING_BRACKET));}},
            {',', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_SEMICON));}},
            {':', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_CON));}},
            {'$', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_END));}},
    };

    char getNextSign();
    std::string appendVal(std::string val);
public:
    Scanner(Configuration configuration);
    void getNextToken();
    // simple printing tokens
    void readToken();
    Token getTokenValue();
    Token seeTokenValue();
};
#endif //TKOM_SCANNER_H
