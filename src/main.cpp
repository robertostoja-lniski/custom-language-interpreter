#include <iostream>
#include "../include/Launcher.h"

int main(int argc, char* argv[]) {

    Launcher launcher;

    try{

        launcher.readFlags(argc, argv);
        launcher.run();

    } catch(std::exception& e){
        std::cout << e.what();
    }

    return 0;
}
