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
    struct player {
        int assists;
        int championLevel;
        string championName;
        int deaths;
        int goldEarned;
        int goldSpent;
        int itemsPurchased;
        int kills;
        int summonerLevel;
        int totalDamageDealtToChampions;

        player(const int a, const int cl, string cn, const int d, const int ge, const int gs, const int ip, const int k, const int sl, const int tddc) :
            assists(a), championLevel(cl), championName(std::move(cn)), deaths(d), goldEarned(ge), goldSpent(gs), itemsPurchased(ip), kills(k), summonerLevel(sl), totalDamageDealtToChampions(tddc) {}
    };

    int gameDuration;
    int gameID;
    vector<player*> players;
    bool team0Win;
    int team0BaronKills;
    int team0ChampionKills;
    int team0DragonKills;
    int team0HordeKills;
    int team0RiftHeraldKills;
    bool team1Win;
    int team1BaronKills;
    int team1ChampionKills;
    int team1DragonKills;
    int team1HordeKills;
    int team1RiftHeraldKills;

    // functions
    LOLGame();
    void ReadGameDataFromFile(istringstream& stream);
};


#endif //COP3530_PROJECT_2_LOL_GAME_STATS_LOLGAME_H