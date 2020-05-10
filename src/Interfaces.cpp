//
// Created by robert on 19.04.2020.
//

#include "../include/Interfaces.h"
#include <utility>
#include <iostream>
#include <memory>
#include <fstream>

FileInterface::FileInterface(std::string path) : filepath(std::move(path)) {
    is = std::make_unique<std::ifstream>(filepath);
}
FileInterface::~FileInterface() {
    is->close();
}
void FileInterface::getNextSign() {
        if(currentIndex == currentLine.size()) {
            if(!currentLine.empty()) {
                sign = '?';
            }
            currentLine.clear();
            std::getline(*is, currentLine);
            currentIndex = 0;
            return;
        }

        sign = currentLine[currentIndex];

        position++;
        currentIndex++;
}
void TerminalInterface::getNextSign() {

        char c;
        std::cin.get(c);
        sign = c;
        position++;
        index++;
}

