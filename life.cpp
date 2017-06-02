#include "life.h"

using std::vector;
using std::pair;
using std::cout;
using std::endl;

//int grid[ROWS][COLS];
//vector<pair<int,int>> birthRefs, deathRefs;

//performs initial setup of grid
void Life::makeGrid() {
    grid[COLS + 1] = 1;
    grid[COLS + 2] = 1;
    grid[COLS * 2 + 1] = 1;
}

//creates list of cells that will die on next tick
void Life::death() {
    for(int i = 0; i < COLS * ROWS -1; i++) {
       // if
    }
}


void Life::birth() {

}

int checkAdj() {

}

void Life::init() {
    makeGrid();
    for(int i = 1; i < COLS * ROWS; i++) {
        cout << grid[i] << " ";
        if (i % (COLS - 1) == 0 && i > 0)
            cout << endl;
    }
    cout << endl;
}

Life::Life() : birthRefs() 
                , deathRefs() { }

