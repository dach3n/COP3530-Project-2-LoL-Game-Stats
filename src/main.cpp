//
// Created by kingd on 11/4/2025.
//

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "quicksort.h"
#include "heapsort.h"
#include <chrono>


int main() {
    // TODO
    // read data from LoL csv
    LOLGameData gameData;
    std::string file = "../../data/LOL_gameData_trimmed.csv";
    gameData.ReadDataFromFile(file);
    // enter user interface loop

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("../../resources/images/LOL_bg.jpg")) {
        std::cerr << "Error loading file. Check path and file name." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Sprite bgSprite(bgTexture);
    // Calculate scale to fit the sprite to the window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = bgTexture.getSize();
    float scaleX = (float)windowSize.x / (float)textureSize.x;
    float scaleY = (float)windowSize.y / (float)textureSize.y;
    // Set the scale using the two-float overload
    sf::Vector2f scaleFactors(scaleX, scaleY);
    bgSprite.setScale(scaleFactors);
    sf::Font font;
    if (!font.openFromFile("../../resources/font.ttf")) {
        std::cerr << "Error loading file. Check path and file name." << std::endl;
        return EXIT_FAILURE;
    }
    sf::String focus = "HI";
    sf::Text sortfocus(font,focus, 0);
    sortfocus.setString("Sort by Which Stat?");
    sortfocus.setCharacterSize(50);
    sortfocus.setFillColor(sf::Color::Yellow);
    sf::Vector2f qpos(120.f, 100.f);
    sortfocus.setPosition(qpos);

    sf::Texture boxTexture;
    if (!boxTexture.loadFromFile("../../resources/images/Box.jpg")) {
        std::cerr << "Error loading file. Check path and file name." << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite boxSprite1(boxTexture);
    sf::Sprite boxSprite2(boxTexture);
    sf::Sprite boxSprite3(boxTexture);
    float boxWidth = boxTexture.getSize().x;
    float boxHeight = boxTexture.getSize().y;
    float windowWidth = (float)windowSize.x;

    // --- Calculate Positions ---
    float boxY = 600.f - boxHeight - 30.f;
    float totalBoxesWidth = 3.f * boxWidth;
    float padding = 50.f;
    float gapSpace = windowWidth - totalBoxesWidth - (2.f * padding);
    float gap = gapSpace / 2.f;

    // Set the positions
    float box1X = padding;
    sf::Vector2f b1pos(box1X, boxY);
    boxSprite1.setPosition(b1pos);

    float box2X = box1X + boxWidth + gap;
    sf::Vector2f b2pos(box2X, boxY);
    boxSprite2.setPosition(b2pos);

    float box3X = box2X + boxWidth + gap;
    sf::Vector2f b3pos(box3X, boxY);
    boxSprite3.setPosition(b3pos);

    sf::Text textKills(font,"Kills", 30);
    sf::Text textGold( font,"Gold", 30);
    sf::Text textTime( font,"Time", 30);

    // Common Text Customization
    textKills.setFillColor(sf::Color::White);
    textGold.setFillColor(sf::Color::White);
    textTime.setFillColor(sf::Color::White);

    // Position = Box X + (Box Width/2) - (Text Width/2)
    sf::Vector2f t1pos(boxSprite1.getPosition().x + (boxWidth / 2.f)-40.f,
        boxSprite1.getPosition().y + (boxHeight / 2.f)-20.f);
    textKills.setPosition(t1pos);

    // --- 3. Center Text Over Box 2 (Gold) ---
    sf::Vector2f t2pos(boxSprite2.getPosition().x + (boxWidth / 2.f)-40.f,
        boxSprite2.getPosition().y + (boxHeight / 2.f)-20.f);
    textGold.setPosition(t2pos);

    // --- 4. Center Text Over Box 3 (Time) ---
    sf::Vector2f t3pos(boxSprite3.getPosition().x + (boxWidth / 2.f)-40.f,
        boxSprite3.getPosition().y + (boxHeight / 2.f)-20.f);
    textTime.setPosition(t3pos);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional eventOpt = window.pollEvent())
        {
            //Close Window Logic
            if (eventOpt->is<sf::Event::Closed>())
            {
                window.close();
            }

            // CLICK HANDLING
            else if (eventOpt->is<sf::Event::MouseButtonPressed>())
            {
                // We extract the basic button event to check which button was pressed
                if (const auto* mouseEvent = eventOpt->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseEvent->button == sf::Mouse::Button::Left)
                    {
                        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                        if (boxSprite1.getGlobalBounds().contains(mousePos))
                        {
                            std::cout << "Kills box clicked! Sorting by Kills..." << std::endl;
                            auto start = chrono::high_resolution_clock::now();
                            vector<LOLGame*> quick = gameData.QuickSortByKills();
                            auto stop = chrono::high_resolution_clock::now();
                            auto quicksort_time = chrono::duration_cast<chrono::milliseconds>(stop - start);
                            cout << "Quick sort: " << quicksort_time.count() << " milliseconds" << endl;
                            start = chrono::high_resolution_clock::now();
                            vector<LOLGame*> heap = gameData.HeapSortByKills();
                            stop = chrono::high_resolution_clock::now();
                            auto heapsort_time = chrono::duration_cast<chrono::milliseconds>(stop - start);
                            cout << "Heap sort: " << heapsort_time.count() << " milliseconds" << endl;
                            int minKills = quick[0]->team0ChampionKills + quick[0]->team1ChampionKills, maxKills = quick[quick.size() - 1]->team0ChampionKills + quick[quick.size() - 1]->team1ChampionKills;
                            cout << "Minimum kills: " << minKills << " | Maximum kills: " << maxKills << endl;
                        }
                        else if (boxSprite2.getGlobalBounds().contains(mousePos))
                        {
                            std::cout << "Gold box clicked! Sorting by Gold..." << std::endl;
                            auto start = chrono::high_resolution_clock::now();
                            vector<LOLGame*> quick = gameData.QuickSortByGold();
                            auto stop = chrono::high_resolution_clock::now();
                            auto quicksort_time = chrono::duration_cast<chrono::milliseconds>(stop - start);
                            cout << "Quick sort: " << quicksort_time.count() << " milliseconds" << endl;
                            start = chrono::high_resolution_clock::now();
                            vector<LOLGame*> heap = gameData.HeapSortByGold();
                            stop = chrono::high_resolution_clock::now();
                            auto heapsort_time = chrono::duration_cast<chrono::milliseconds>(stop - start);
                            cout << "Heap sort: " << heapsort_time.count() << " milliseconds" << endl;
                            int minGold = 0, maxGold = 0;
                            for (int i = 0; i < 10; i++) {
                                minGold += quick[0]->players[i]->goldEarned;
                                maxGold += quick[quick.size() - 1]->players[i]->goldEarned;
                            }
                            cout << "Minimum gold: " << minGold << " | Maximum gold: " << maxGold << endl;
                        }
                        else if (boxSprite3.getGlobalBounds().contains(mousePos))
                        {
                            std::cout << "Time box clicked! Sorting by Time..." << std::endl;
                            auto start = chrono::high_resolution_clock::now();
                            vector<LOLGame*> quick = gameData.QuickSortByTime();
                            auto stop = chrono::high_resolution_clock::now();
                            auto quicksort_time = chrono::duration_cast<chrono::milliseconds>(stop - start);
                            cout << "Quick sort: " << quicksort_time.count() << " milliseconds" << endl;
                            start = chrono::high_resolution_clock::now();
                            vector<LOLGame*> heap = gameData.HeapSortByTime();
                            stop = chrono::high_resolution_clock::now();
                            auto heapsort_time = chrono::duration_cast<chrono::milliseconds>(stop - start);
                            cout << "Heap sort: " << heapsort_time.count() << " milliseconds" << endl;
                            int minTime = quick[0]->gameDuration, maxTime = quick[quick.size() - 1]->gameDuration;
                            cout << "Minimum time (s): " << minTime << " | Maximum time (s): " << maxTime << endl;
                        }
                    }
                }
            }
        }


        // Clear screen
        window.clear();
        window.draw(bgSprite);
        window.draw(sortfocus);
        window.draw(boxSprite1);
        window.draw(boxSprite2);
        window.draw(boxSprite3);
        window.draw(textKills);
        window.draw(textGold);
        window.draw(textTime);
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