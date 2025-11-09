//
// Created by kingd on 11/8/2025.
//

#ifndef COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAME_H
#define COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAME_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

class LOLGame {
    public:
    struct Player {
        int assists;
        int championLevel;
        string championName;
        int deaths;
        int goldEarned;
        int goldSpent;
        int itemsPurchased;
        int kills;
        int totalDamageDealtToChampions;

        Player(const int a, const int cl, const string& cn, const int d, const int ge, const int gs, const int ip, const int k, const int tddc) {
            assists = a;
            championLevel = cl;
            championName = cn;
            deaths = d;
            goldEarned = ge;
            goldSpent = gs;
            itemsPurchased = ip;
            kills = k;
            totalDamageDealtToChampions = tddc;
        }


        void PrintPlayer();
    };

    int gameDuration;
    string gameID;
    vector<Player*> players;
    string team0Win;
    int team0BaronKills;
    int team0ChampionKills;
    int team0DragonKills;
    int team0HordeKills;
    int team0RiftHeraldKills;
    string team1Win;
    int team1BaronKills;
    int team1ChampionKills;
    int team1DragonKills;
    int team1HordeKills;
    int team1RiftHeraldKills;

    // functions
    LOLGame() {}

    void ReadGameDataFromFile(istringstream& stream);

    void PrintGameData();
};


#endif //COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAME_H