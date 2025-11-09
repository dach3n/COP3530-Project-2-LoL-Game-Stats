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
