#include "../include/Launcher.h"

bool Launcher::isPathFlag(std::string potentialFlag) {
        return std::find(filePathFlags.begin(), filePathFlags.end(), potentialFlag.c_str()) != filePathFlags.end();
}

bool Launcher::isNonPathFile(std::string potentialFlag) {
    return std::find(nonFilePathFlags.begin(), nonFilePathFlags.end(), potentialFlag.c_str()) != nonFilePathFlags.end();
}

bool Launcher::isFilePathProper(std::string filepath){
    return true;
}

bool Launcher::isPathToUpperDirProper(std::string filepath){
    return true;
}

void Launcher::readFlags(int argc, char* argv[]) {

    if((unsigned int)argc < minArgc) {
        throw std::runtime_error("Not enough arguments provided");
    }

    for(int i = 1; i < argc; i++) {

        std::string potentialFlag(argv[i]);
        if(isPathFlag(potentialFlag)) {
            //if next argument is provided
            if(i + 1 >= argc) {
                throw std::runtime_error("File path not provided");
            }

            std::string filePath(argv[i+1]);

            if(potentialFlag == "-f") {
                if(!isFilePathProper(filePath)) {
                    throw std::runtime_error("Wrong path to config file");
                }
                configuration.inputPath = filePath;

            } else if(potentialFlag == "-o") {
                if(!isPathToUpperDirProper(filePath)) {
                    throw std::runtime_error("Wrong path to output file");
                }
                configuration.outputPath = filePath;
            }

            i++;

        } else if(isNonPathFile(potentialFlag)) {

            if(potentialFlag == "-v") {
                configuration.isVerbose = true;
            }
        }
    }
}

void Launcher::run() {

    scanner = std::make_shared<Scanner>(configuration);
    parser = std::make_unique<Parser>(scanner);

    parser->parseNextToken();
    parser->generateTree();
    parser->analyzeTree();
}