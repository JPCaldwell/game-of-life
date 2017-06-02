#ifndef LIFE_H_
#define LIFE_H_

#include <vector>
#include <utility>
#include <iostream>

#define ROWS 10
#define COLS 10

class Life {
    public:
       

        void init();
        Life();
    private:
        int grid[ROWS * COLS];
        std::vector<int> *birthRefs, *deathRefs;

        void makeGrid();
        void death();
        void birth();
        void tick();
        void checkGrid();
        int checkAdj(int index);

   

};

#endif
