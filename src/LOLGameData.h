//
// Created by kingd on 11/8/2025.
//

#ifndef COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAMEDATA_H
#define COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAMEDATA_H

#include <vector>
#include "LOLGame.h"
#include <fstream>
#include "quicksort.h"
#include "heapsort.h"

class LOLGameData {
    // variables

    // functions

public:
    // variables
    vector<LOLGame*> games;

    //functions
    LOLGameData();
    void ReadDataFromFile();
};


#endif //COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAMEDATA_H