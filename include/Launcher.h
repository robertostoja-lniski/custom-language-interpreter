//
// Created by robert on 04.04.2020.
//

#ifndef TKOM_LAUNCHER_H
#define TKOM_LAUNCHER_H

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Configuration.h"

class Launcher {

private:
    unsigned int minArgc {1};
    Configuration configuration;
    std::vector<std::string> filePathFlags = {"-f", "-o"};
    std::vector<std::string> nonFilePathFlags = {"-v"};

    std::unique_ptr<Scanner> scanner;
    std::unique_ptr<Parser> parser;

    bool isPathFlag(std::string potentialFlag);
    bool isNonPathFile(std::string potentialFlag);

    //checks to be added in final project stage
    bool isFilePathProper(std::string filepath);
    bool isPathToUpperDirProper(std::string filepath);

public:

    Launcher() = default;

    void readFlags(int argc, char* argv[]);
    void run();
};


#endif //TKOM_LAUNCHER_H
