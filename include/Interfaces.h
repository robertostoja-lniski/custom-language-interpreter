//
// Created by robert on 19.04.2020.
//

#ifndef TKOM_INTERFACES_H
#define TKOM_INTERFACES_H

#include <iostream>
#include <string>
#include <memory>

struct SourceInterface {

    off64_t position {0};
    char sign;
    virtual void getNextSign() = 0;
    SourceInterface() = default;
};
struct FileInterface : public SourceInterface {

    std::string filepath;
    std::unique_ptr<std::ifstream> is;
    std::string currentLine;
    off64_t currentIndex {0};

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
