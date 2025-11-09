//
// Created by kingd on 11/8/2025.
//

#include "LOLGameData.h"

void LOLGameData::ReadDataFromFile(string& filePath) {
    ifstream file(filePath); // Open game data
    if (file.is_open()) {
        string line;
        getline(file, line); // skip header

        while (getline(file, line)) {
            istringstream stream(line);
            auto game = new LOLGame;
            game->ReadGameDataFromFile(stream);
            games.push_back(game);
        }
    }
    else {
        cout << "File could not be opened" << endl;
    }


}

vector<LOLGame*> LOLGameData::QuickSortByKills() {
    struct {
        bool operator()(LOLGame* a, LOLGame* b) {
            int aKills = a->team0ChampionKills + a->team1ChampionKills;
            int bKills = b->team0ChampionKills + b->team1ChampionKills;
            return aKills < bKills;
        }
    }
    lessKills;
    vector<LOLGame*> copy = games;
    LOLQuickSort(copy, 0, copy.size() - 1, lessKills);
    return copy;
}

vector<LOLGame *> LOLGameData::QuickSortByGold() {
    struct {
        bool operator()(LOLGame* a, LOLGame* b) {
            int aGold = 0, bGold = 0;
            for (int i = 0; i < 10; i++) {
                aGold += a->players[i]->goldEarned;
                bGold += b->players[i]->goldEarned;
            }
            return aGold < bGold;
        }
    }
    lessGold;
    vector<LOLGame*> copy = games;
    LOLQuickSort(copy, 0, copy.size() - 1, lessGold);
    return copy;
}

vector<LOLGame *> LOLGameData::QuickSortByTime() {
    struct {
        bool operator()(LOLGame* a, LOLGame* b) {
            return a->gameDuration < b->gameDuration;
        }
    }
    lessTime;
    vector<LOLGame*> copy = games;
    LOLQuickSort(copy, 0, copy.size() - 1, lessTime);
    return copy;
}

vector<LOLGame *> LOLGameData::HeapSortByKills() {
    struct {
        bool operator()(LOLGame* a, LOLGame* b) {
            int aKills = a->team0ChampionKills + a->team1ChampionKills;
            int bKills = b->team0ChampionKills + b->team1ChampionKills;
            return aKills < bKills;
        }
    }
    lessKills;
    vector<LOLGame*> copy = games;
    LOLHeapSort(copy, lessKills);
    return copy;
}

vector<LOLGame *> LOLGameData::HeapSortByGold() {
    struct {
        bool operator()(LOLGame* a, LOLGame* b) {
            int aGold = 0, bGold = 0;
            for (int i = 0; i < 10; i++) {
                aGold += a->players[i]->goldEarned;
                bGold += b->players[i]->goldEarned;
            }
            return aGold < bGold;
        }
    }
    lessGold;
    vector<LOLGame*> copy = games;
    LOLHeapSort(copy, lessGold);
    return copy;
}

vector<LOLGame *> LOLGameData::HeapSortByTime() {
    struct {
        bool operator()(LOLGame* a, LOLGame* b) {
            return a->gameDuration < b->gameDuration;
        }
    }
    lessTime;
    vector<LOLGame*> copy = games;
    LOLHeapSort(copy, lessTime);
    return copy;
}


