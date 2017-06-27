#include "life.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>

int main(int argc, char* argv[]) {
    Life* game = new Life();
    std::vector<int>* startLocs = new std::vector<int>();
    int x, y;
    std::string inp, strDone;
    bool done = 0;
    if(argc < 2) { //take user supplied input from command line
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
    }
    else if(!strcmp(argv[1], "-f") && argc >= 3) {  //strcmp returns 0 on equality
        std::string line;
        char cLine[10]; 
        char* lineTok;
        std::ifstream input (argv[2]);
        if(input.is_open()) {
            while(getline(input, line)) {
                strcpy(cLine, line.c_str());
                lineTok = strtok(cLine, " ,");
                if(lineTok == NULL) {
                    std::cerr << "Malformed Line. Line is: " << line << std::endl;
                    continue; //line is malformed, skip to reading next line
                }
                x = atoi(lineTok);
                lineTok = strtok(NULL, " ,");
                if(lineTok == NULL) {
                    std::cerr << "Malformed Line. Line is: " << line << std::endl;
                    continue; //line is malformed, skip to reading next line
                }

                y = atoi(lineTok);
                if(x >= 0 && x <= COLS - 1 && y >= 0 && y <= ROWS - 1) {
                    startLocs->push_back(x + y*COLS);
                }
                else {
                    std::cerr << x << ", " << y << " is an invalid index. Moving to next line..." << std::endl;
                }

            }
        }
    }
    game->init(startLocs);
    return 0;
}
