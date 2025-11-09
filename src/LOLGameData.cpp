//
// Created by kingd on 11/8/2025.
//

#include "LOLGameData.h"

void LOLGameData::ReadDataFromFile() {
    std::ifstream file("data/LOL_gameData_trimmed.csv"); // Open game data
    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        auto game = new LOLGame;
        game->ReadGameDataFromFile(stream);
        games.push_back(game);
    }
}
