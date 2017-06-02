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

//removes cells that die on this tick
void Life::death() {
}

//removes cells that are born on this tick
void Life::birth() {

}

//perform one tick of the game, i.e. remove cells that die and add cells that are born
void Life::tick() {
    checkGrid();
}

//checks the adjacencies for the 
void Life::checkGrid() {
    for(int i = 0; i < COLS * ROWS -1; i++) {
        int adj = checkAdj(i);
        //check if current cell is alive or dead; dead cells ony care about if they are born
        if(grid[i] == 1) {
            //current cell is alive
            if(adj < 2) {
                //cell will die with <2 neighbor(s)
                deathRefs->push_back(i);
            }
            else if (adj > 3) {
                //cell will die with >3 neigbors
                deathRefs->push_back(i);
            }
        }

        else {
            //current cell is dead
            if(adj == 3) {
                //dead cell with exactly 3 neighbors will be born
                birthRefs->push_back(i);
            }
        }
    }

}

//returns the number of adjacent live cells
int Life::checkAdj(int index) {
    int adj = 0;
    bool left, right, top, bottom;
    left = index % COLS == 0 ? 1 : 0;
    right = index % (COLS - 1) == 0 ? 1 : 0;
    top = index < COLS ? 1 : 0;
    bottom = ((index > COLS * ROWS - ROWS - 1) && (index < COLS * ROWS - 1)) ? 1 : 0;
    //TL corner
    if(left && top) {
        adj = grid[index+1] + grid[index+COLS] + grid[index+COLS+1];
    }
    //Top edge
    else if(top && !left && !right) {
        adj = grid[index-1] + grid[index+1] + grid[index+COLS-1] + grid[index+COLS] + grid[index+COLS+1];
    }
    //TR corner
    else if(top && right) {
        adj = grid[index-1] + grid[index+COLS-1] + grid[index+COLS];
    }
    //Left edge
    else if(left && !top && !bottom) {
        adj = grid[index-COLS] + grid[index-COLS+1] + grid[index+1] + grid[index+COLS] + grid[index+COLS+1];
    }
    //Right edge
    else if(right && !top && !bottom) {
        adj = grid[index-COLS-1] + grid[index-COLS] + grid[index-1] + grid[index+COLS-1] + grid[index+COLS];
    }
    //BL corner
    else if(bottom && left) {
        adj = grid[index-COLS] + grid[index-COLS+1] + grid[index+1];
    }
    //Bottom edge
    else if(bottom && !left && !right) {
        adj = grid[index-COLS-1] + grid[index-COLS] + grid[index-COLS+1] + grid[index-1] + grid[index+1];
    }
    else if(bottom && right) {
        adj = grid[index-COLS-1] + grid[index-COLS] + grid[index-1];
    }
    //not on any edge
    else {
        adj = grid[index-COLS-1] + grid[index-COLS] + grid[index-COLS+1] + grid[index-1] + grid[index+1] + \
              grid[index+COLS-1] + grid[index+COLS] + grid[index+COLS+1];
    }
    return adj;
}

void Life::init() {
    makeGrid();
    tick(); //TODO call tick user supplied number of times
    for(int i = 1; i < COLS * ROWS; i++) {
        cout << grid[i] << " ";
        if (i % (COLS - 1) == 0 && i > 0)
            cout << endl;
    }
    cout << endl;
}

Life::Life() : birthRefs() 
               , deathRefs() { }

