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
    uidlFile << "$";
    uidlFile.close();
    is = std::make_unique<std::ifstream>(filepath);

}
FileInterface::~FileInterface() {
    is->close();
}
void FileInterface::getNextSign() {

        if(positionInFile.column == currentLine.size() && !currentLine.empty()) {
            sign = '?';
            positionInFile.column++;
            return;
        }
        if(currentLine.empty() || positionInFile.column == currentLine.size() +1) {

            positionInFile.row++;
            currentLine.clear();
            std::getline(*is, currentLine);
            positionInFile.column = 0;
        }

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

