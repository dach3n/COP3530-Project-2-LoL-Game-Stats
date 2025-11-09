#include <catch2/catch_test_macros.hpp>
#include <iostream>

// uncomment and replace the following with your own headers
// David Chen 97345471
#include <algorithm>

#include "heapsort.h"
#include "quicksort.h"
#include "LOLGameData.h"
#include "LOLGame.h"
#include "catch2/internal/catch_windows_h_proxy.hpp"

using namespace std;

TEST_CASE("Read Data", "[LOL game data]") {
    LOLGameData data;
    string filePath = "../data/LOL_gameData_trimmed.csv";
    data.ReadDataFromFile(filePath);
    cout << data.games.size() << endl;
    data.games[0]->PrintGameData();
}

