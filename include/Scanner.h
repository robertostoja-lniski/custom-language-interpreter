//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H

#include <memory>
#include <iostream>
#include <fstream>
#include <queue>
#include "Configuration.h"
#include "Interfaces.h"
#include "Token.h"

class Scanner {

private:

    std::unique_ptr<SourceInterface> sourceInterface;
    std::queue<std::shared_ptr<Token>> tokens;
    char sign;
    bool isVerbose {false};

    void removeWhiteSigns();

    std::shared_ptr<Token> createTokenFromValue(std::string val);
    std::shared_ptr<Token> createSpecialSignToken(std::string c);
    std::string appendValWhileIsDigit(std::string);

    bool tryToBuildSimpleToken();
    bool tryToBuildNumToken();
    bool tryToBuildAlphaTokens();
    bool tryToBuildNotDefinedToken();


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
