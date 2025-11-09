//
// Created by kingd on 11/4/2025.
//

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "quicksort.h"
#include "heapsort.h"


int main() {
    // TODO
    // read data from LoL csv
    // enter user interface loop

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();

        // Update the window
        window.display();
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