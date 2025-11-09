//
// Created by kingd on 11/8/2025.
//

#include "LOLGameData.h"

void LOLGameData::ReadDataFromFile(string& filePath) {
    std::ifstream file(filePath); // Open game data
    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        auto game = new LOLGame;
        game->ReadGameDataFromFile(stream);
        games.push_back(game);
    }
}
