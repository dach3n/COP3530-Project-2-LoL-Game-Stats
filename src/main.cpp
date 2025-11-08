//
// Created by kingd on 11/4/2025.
//

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "quicksort.h"
#include "heapsort.h"
using namespace std;

int main() {
    // TODO
    // read data from LoL csv
    // enter user interface loop
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("files/images/LOL_BG.jpg");
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::RenderWindow welcome(sf::VideoMode(1000, 1000), "Welcome");
    float scaleX = static_cast<float>(welcome.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(welcome.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    while(welcome.isOpen()) {
        sf::Event event;
        while(welcome.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcome.close();
            }

        }
        welcome.clear();
        welcome.draw(backgroundSprite);
        welcome.display();
    }
        /* GUI menu
         * sort by game time
         * sort by total game kills
         * sort by winning team kill difference
         * sort by total game gold
         * sort by winning team gold difference
         * sort by total damage dealt
         */
        // new screen: graph with data displayed
        // buttons for mean, median, mode, range, etc.
        // buttons to return to graph selection, quit
    return 0;
}