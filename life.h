#ifndef LIFE_H_
#define LIFE_H_

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

#define ROWS 10
#define COLS 10

class Life {
    public:   

        void init(std::vector<int>* startLocs);
        Life();
    private:
        int grid[ROWS * COLS];
        std::vector<int> birthRefs, deathRefs;
        std::ofstream log;

        void makeGrid(std::vector<int>* startLocs);
        void death();
        void birth();
        void tick();
        void checkGrid();
        int checkAdj(int index);

   

};

#endif
