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
    Position position;
    char sign;
    bool isVerbose {false};

    bool removeWhiteSigns();

    void createTokenFromValue(std::string val);
    std::string appendValWhileIsDigit(std::string);

    bool tryToBuildNumToken();
    bool tryToBuildAlphaTokens();
    bool tryToBuildNotDefinedToken();
    bool tryToBuildAssignmentOrBooleanToken();
    bool tryToBuildGreaterOrLessBoolean();
    bool tryToBuildAssignOrCompare();
    bool tryToBuildSpecialSignToken();
    std::string returnIntegerPrefixIfBuildPossible();
    bool tryToBuildRealNumWithGivenPrefix(std::string);
    bool tryToBuildNonQuotedSign();
    bool tryToBuildQuotedSign();

    std::map<std::string, std::function<void(std::string value)>> complexTokensHandlers {
            {"int", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER, position));}},
            {"unsigned_int", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER, position));}},
            {"float", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER, position));}},
            {"string", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SPECIFIER, position));}},
            {"system_handler", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SYSTEM_HANDLER, position));}},
            {"while", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_WHILE, position));}},
            {"for", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_FOR, position));}},
            {"if", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_IF, position));}},
            {"do", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_DO, position));}},
            {"else", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_ELSE, position));}},
            {"done", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_DONE, position));}},
            {"put", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_PUT, position));}},
            {"register", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_REGISTER, position));}},
            {"send_raport", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_SEND_RAPORT, position));}},
            {"backup", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_BACKUP, position));}},
            {"check_system", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_CHECK_SYSTEM, position));}},
            {"start", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_RUN, position));}},
            {"run", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_RUN_SCRIPT, position));}},
            {"path", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_PATH, position));}},
            {"raport_dir", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_RAPORT_DIR, position));}},
            {"raport_type", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_RAPORT_TYPE, position));}},
            {"mail", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_MAIL, position));}},
            {"ret", [&](std::string value) {tokens.push(std::make_shared<Token>(std::move(value), T_RET, position));}},

    };

    std::map<char, std::function<void(char currentSing)>> simpleTokensHandlers {
            {EOF, [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_END, position));}},
            {'*', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_MULT_OPERATOR, position));}},
            {'/', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_MULT_OPERATOR, position));}},
            {'&', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_BOOLEAN_AND, position));}},
            {'.', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_DOT, position));}},
            {'+', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_ADD_OPERATOR, position));}},
            {'-', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_ADD_OPERATOR, position));}},
            {'|', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_BOOLEAN_OR, position));}},
            {'\n', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_NEXT_LINE, position));}},
            {')', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_CLOSING_PARENTHESIS, position));}},
            {'(', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_OPENING_PARENTHESIS, position));}},
            {'{', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_OPENING_BRACKET, position));}},
            {'}', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_CLOSING_BRACKET, position));}},
            {',', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_SEMICON, position));}},
            {':', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_CON, position));}},
            {'$', [&](char currentSing) {tokens.push(std::make_shared<Token>(currentSing, T_END, position));}},
    };

    bool tryToBuildNextLine();
    char getNextSign();
    char getSignAndReadNext();
    void getNextToken();
    void readToken();
public:
    Scanner(Configuration configuration);
    // simple printing tokens
    void scan();
    Token getTokenValue();
    Token seeNextTokenValue();
};
#endif //TKOM_SCANNER_H
