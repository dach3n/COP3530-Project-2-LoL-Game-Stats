//
// Created by kingd on 11/8/2025.
//

#include "LOLGame.h"

void LOLGame::Player::PrintPlayer() {
    cout << "LVL "<<  championLevel << " " << championName << endl;
    cout << "K: " << kills << " D: " << deaths << " A: " << assists << endl;
    cout << "Gold: " << goldEarned << "(" << goldSpent << ") Items purchased: " << itemsPurchased << endl;
    cout << "Damage Dealt to Champions: " << totalDamageDealtToChampions << endl;
}

void LOLGame::ReadGameDataFromFile(istringstream &stream) {
    // Line format:
    /*
    gameDuration
    gameID
    for participants 0-9 in order: assists, championLevel, championName, deaths, goldEarned, goldSpent, itemsPurchased, kills, totalDamageDealtToChampions
    team0: team0Win, team0BaronKills, team0ChampionKills, team0DragonKills, team0HordeKills, team0RiftHeraldKills
    team1: team1Win, team1BaronKills, team1ChampionKills, team0DragonKills, team0HordeKills, team0RiftHeraldKills
    */
    string token;
    getline(stream, token, ',');
    gameDuration = stoi(token);
    getline(stream, gameID, ',');

    // Get and store all 10 participants data
    for (int i = 0; i < 10; i++) {
        getline(stream, token, ',');
        int a = stoi(token);

        getline(stream, token, ',');
        int cl = stoi(token);

        string cn;
        getline(stream, cn, ',');

        getline(stream, token, ',');
        int d = stoi(token);

        getline(stream, token, ',');
        int ge = stoi(token);

        getline(stream, token, ',');
        int gs = stoi(token);

        getline(stream, token, ',');
        int ip = stoi(token);

        getline(stream, token, ',');
        int k = stoi(token);

        getline(stream, token, ',');
        int tddc = stoi(token);

        players.push_back(new Player(a, cl, cn, d, ge, gs, ip, k, tddc));
    }

    // Team 0 (Blue) stats
    getline(stream, team0Win, ',');
    getline(stream, token, ',');
    team0BaronKills = stoi(token);
    getline(stream, token, ',');
    team0ChampionKills = stoi(token);
    getline(stream, token, ',');
    team0DragonKills = stoi(token);
    getline(stream, token, ',');
    team0HordeKills = stoi(token);
    getline(stream, token, ',');
    team0RiftHeraldKills = stoi(token);

    // Team 1 (Red) stats
    getline(stream, team1Win, ',');
    getline(stream, token, ',');
    team1BaronKills = stoi(token);
    getline(stream, token, ',');
    team1ChampionKills = stoi(token);
    getline(stream, token, ',');
    team1DragonKills = stoi(token);
    getline(stream, token, ',');
    team1HordeKills = stoi(token);
    getline(stream, token, ',');
    team1RiftHeraldKills = stoi(token);
}

void LOLGame::PrintGameData() {
    cout <<"Game ID: " << gameID << " Game duration: " << gameDuration << endl;
    for (Player* player : players) {
        cout << "\n";
        player->PrintPlayer();
    }
    cout << "\n";
    cout << "Team 0 Win: " << team0Win << " Kills: " << team0ChampionKills << " Barons: " << team0BaronKills << " Dragons: " << team0DragonKills << " Grubs: " << team0HordeKills << " Herald: " << team0RiftHeraldKills << endl;
    cout << "Team 1 Win: " << team1Win << " Kills: " << team1ChampionKills << " Barons: " << team1BaronKills << " Dragons: " << team1DragonKills << " Grubs: " << team1HordeKills << " Herald: " << team1RiftHeraldKills << endl;
}
