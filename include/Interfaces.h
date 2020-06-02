//
// Created by robert on 19.04.2020.
//

#ifndef TKOM_INTERFACES_H
#define TKOM_INTERFACES_H

#include <iostream>
#include <string>
#include <memory>
struct Position{
    off64_t row {0};
    off64_t column {0};
    Position() = default;
};

struct SourceInterface {

    Position position;
    char sign;
    virtual void getNextSign() = 0;
    SourceInterface() = default;
};
struct FileInterface : public SourceInterface {

    size_t charCount = 0;
    size_t size;
    std::string filepath;
    std::unique_ptr<std::ifstream> is;
    std::string currentLine;
    Position positionInFile;

    FileInterface(std::string path);
    ~FileInterface();
    void getNextSign();
};
struct TerminalInterface : public SourceInterface {

    size_t index {0};
    TerminalInterface() = default;
    void getNextSign();
};


#endif //TKOM_INTERFACES_H
