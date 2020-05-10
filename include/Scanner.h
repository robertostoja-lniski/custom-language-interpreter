//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H

#include <memory>
#include <iostream>
#include <fstream>
#include "Configuration.h"
#include "Interfaces.h"
#include "Token.h"

class Scanner {

private:

    std::unique_ptr<SourceInterface> sourceInterface;
    std::unique_ptr<Token> token;
    char sign;
    bool isVerbose {false};

    void removeWhiteSigns();

    std::unique_ptr<Token> createTokenFromValue(std::string val);
    std::unique_ptr<Token> createSpecialSignToken(std::string c);
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
};
#endif //TKOM_SCANNER_H
