//
// Created by robert on 19.04.2020.
//

#include "../include/Scanner.h"
#include "../include/Interfaces.h"
#include <utility>

FileInterface::FileInterface(std::string path) : filepath(std::move(path)) {
    is = std::make_unique<std::ifstream>(filepath);
}

FileInterface::~FileInterface() {
    is->close();
}

void FileInterface::getNextSign() {
        char c;
        is->get(c);
        sign = c;
        position++;
}

void TerminalInterface::getNextSign() {
        if(!isAnyCharLeftInLine) {
            getline(std::cin, input);
            index = 0;
            isAnyCharLeftInLine = true;
        }

        sign = input[index];
        position++;
        index++;

        if(index == input.size()) {
            isAnyCharLeftInLine = false;
        }
}
