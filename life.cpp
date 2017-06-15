#include "life.h"

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::ofstream;

//int grid[ROWS][COLS];
//vector<pair<int,int>> birthRefs, deathRefs;

//performs initial setup of grid
void Life::makeGrid(vector<int>* startLocs) {
    for(vector<int>::iterator it = startLocs->begin(); it != startLocs->end(); ++it) {
        grid[*it] = 1;
    }
}

//removes cells that die on this tick
void Life::death() {
    wasChange = !deathRefs.empty(); //if deathRefs is nonempty, then there will be at least one change
    for(vector<int>::iterator it = deathRefs.begin(); it != deathRefs.end(); ++it) {
        grid[*it] = 0;
    }
    deathRefs.clear();
}

//adds cells that are born on this tick
void Life::birth() {
    wasChange = !birthRefs.empty(); //if birthRefs is nonempty, then there will be at least one change
    for(vector<int>::iterator it = birthRefs.begin(); it != birthRefs.end(); ++it) {
        grid[*it] = 1;
    }
    birthRefs.clear();
}

//perform one tick of the game, i.e. remove cells that die and add cells that are born
void Life::tick() {
    checkGrid();
    death();
    birth();
}

//checks the adjacencies for each cell and marks cells for death/birth 
void Life::checkGrid() {
    //    ofstream log;
    //    log.open("log.txt");
    for(int i = 0; i < COLS * ROWS; ++i) {
        int adj = checkAdj(i);

        //check if current cell is alive or dead; dead cells ony care about if they are born
        if(grid[i] == 1) {
            //current cell is alive
            if(adj < 2) {
                //cell will die with <2 neighbor(s)
                log << "    Cell " << i << " will die due to having " << adj << " neighbors" << endl; 
                deathRefs.push_back(i);
            }
            else if (adj > 3) {
                //cell will die with >3 neigbors
                log << "    Cell " << i << " will die due to having " << adj << " neighbors" << endl;
                deathRefs.push_back(i);
            }
        }

        else {
            //current cell is dead
            if(adj == 3) {
                //dead cell with exactly 3 neighbors will be born
                log << "    Cell " << i << " will be born due to having " << adj << " neighbors" << endl;
                birthRefs.push_back(i);
            }
        }
    }
    //    log.close();
}

//returns the number of adjacent live cells
int Life::checkAdj(int index) {
    int adj = 0;
    bool left, right, top, bottom;
    left = index % COLS == 0 ? 1 : 0;
    right = (index + 1) % COLS  == 0 && index != 0 ? 1 : 0;
    top = index < COLS ? 1 : 0;
    bottom = ((index > COLS * ROWS - ROWS - 1) && (index < COLS * ROWS - 1)) ? 1 : 0;
    //    log << "Cell: " << index << "\n\tLeft: " << left << "\n\tRight: " << right << "\n\tTop: " << top << "\n\tBottom : " << bottom << endl;
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
        adj = grid[index-COLS-1] + grid[index-COLS] + grid[index-COLS+1] + grid[index-1] + grid[index+1] + grid[index        +COLS-1] + grid[index+COLS] + grid[index+COLS+1];
    }
    return adj;
}

void Life::init(vector<int>* startLocs) {
    //    ofstream log;
    //    log.open("log.txt");
    makeGrid(startLocs);

    int i = 0;
    while(wasChange && i < 100) { //run until grid is stable (i.e. no changes were made last tick) or 100 ticks
        cout << "round " << i << "\n\n";
        log << "round " << i << "\n\n";
        for(int j = 0; j < COLS * ROWS; ++j) {
            cout << grid[j] << " ";
            if ((j + 1) % COLS == 0 && j > 0)
                cout << endl;
        }
        wasChange = 0;
        tick();
        ++i;
        cout << endl;

    }
    log.close();
}

    Life::Life() : birthRefs() 
                   , deathRefs()
                   , log("log.txt", std::ios::out | std::ios::trunc)
                   , wasChange(1) { }

