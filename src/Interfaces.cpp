//
// Created by robert on 19.04.2020.
//

#include "../include/Interfaces.h"
#include <utility>
#include <iostream>
#include <memory>
#include <fstream>

FileInterface::FileInterface(std::string path) : filepath(std::move(path)) {
    // appends end sign
    std::fstream uidlFile(filepath, std::fstream::in | std::fstream::out | std::fstream::app);
    const auto begin = uidlFile.tellg();
    uidlFile.seekg (0, std::ios::end);
    const auto end = uidlFile.tellg();
    size = end - begin;
    is = std::make_unique<std::ifstream>(filepath);

}
FileInterface::~FileInterface() {
    is->close();
}
void FileInterface::getNextSign() {

        if(charCount == size -1) {
            sign = '$';
            return;
        }
        if(positionInFile.column == currentLine.size() && !currentLine.empty()) {
            sign = '\n';
            positionInFile.column++;
            charCount++;
            return;
        }
        if(currentLine.empty() || positionInFile.column == currentLine.size() +1) {
            positionInFile.row++;
            currentLine.clear();
            std::getline(*is, currentLine);
            positionInFile.column = 0;
        }

        charCount++;
        sign = currentLine[positionInFile.column];
        positionInFile.column++;
}
void TerminalInterface::getNextSign() {

        char c;
        std::cin.get(c);
        sign = c;
        position.column++;
        index++;
}

