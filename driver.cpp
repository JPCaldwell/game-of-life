#include "life.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

int main() {
    Life* game = new Life();
    std::vector<int>* startLocs = new std::vector<int>();
    int x, y;
    std::string inp, strDone;
    bool done = 0;
    while(!done) { //TODO do input checking (including range checking)
        std::cout << "Enter the column (starting with 1): ";
        std::cin >> inp;
        x = atoi(inp.c_str()) - 1;
        std::cout << x << std::endl;
       
        std::cout << "Enter the row (starting with 1): ";
        std::cin >> inp;
        y = atoi(inp.c_str()) - 1;
        std::cout << y << std::endl;

        std::cout << "Adding " << x << "," << y << " to list..." << std::endl;
        startLocs->push_back(x + y*COLS);
        std::cout << "Added raw index " << x + y*COLS << std::endl;        

        std::cout << "Done? (y/n): ";
        std::cin >> strDone;
        while(strDone != "y" && strDone != "n") {
            std::cout << "y/n only: ";
            std::cin >> strDone;
        }
        done = strDone == "y" ? 1 : 0;
    }

    
    game->init(startLocs);
    return 0;
}
