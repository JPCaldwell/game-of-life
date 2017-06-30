#include "life.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>



int main(int argc, char* argv[]) {
    Life* game;
    if(argc == 4) { //user supplied maximum cycles
        char cycles[10];
        strcpy(cycles, argv[3]);
        std::cout << atoi(cycles) << " cycles" << std::endl;
        game = new Life(atoi(cycles)+1);
    }
    else {  //no user supplied maximum cycles 


        std::cout << "default" << std::endl;
        game = new Life();
    }
    
    std::vector<int>* startLocs = new std::vector<int>();
    int x, y;
    std::string inp, strDone;
    bool done = 0;
    if(argc < 2) {
        std::cerr << "Incorrect usage: specify either -m for manual input or -f and a filename"
            << " to read inputs from a file" << std::endl;
    }
    //take user supplied input from command line
    //Mostly depreciated, input this way is horribly slow and cumbersome

    if((argc == 2 || argc == 3) && !strcmp(argv[1], "-m")) {        
        while(!done) { 
            bool validInp = 0;
            while(!validInp) {
                std::cout << "Enter the column (starting with 0): ";
                std::cin >> inp;

                x = atoi(inp.c_str());
                //              std::cout << x << std::endl;
                validInp = (x >= 0 && x <= COLS - 1);
                if(!validInp) {
                    std::cout << "invalid x value; please input a value 0 <= x <= " << COLS << std::endl;
                }
            }

            validInp = 0;
            while(!validInp) {
                std::cout << "Enter the row (starting with 0): ";
                std::cin >> inp;
                y = atoi(inp.c_str());
                //          std::cout << y << std::endl;
                validInp = (x >= 0 && x <= ROWS - 1);
                if(!validInp) {
                    std::cout << "invalid x value; please input a value 0 <= x <= " << COLS << std::endl;
                }

            }

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

    else if(!strcmp(argv[1], "-f") && (argc == 3 || argc == 4)) {  //strcmp returns 0 on equality
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
        else {
            std::cerr << "File could not be opened" << std::endl;
            return -1;
        }
    }
    game->init(startLocs);
    return 0;
}


