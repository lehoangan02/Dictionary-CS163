#include <iostream>
#include "loadingScreen.hpp"

loadingScreen::loadingScreen() :
    loadingTexture(loadTexture("assets/images/loading.png")),
    loadingAnimation(loadingTexture, sf::Vector2u(1, 11), 0.1)
{
    loadingAnimation.setPosition(sf::Vector2u(230, 0));
    magarine.loadFromFile("assets/font/Margarine-Regular.ttf");
    loadingText.setFont(magarine);
    loadingText.setCharacterSize(96);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setString("loading");
    loadingText.setOutlineThickness(3);
    loadingText.setOutlineColor(sf::Color(94, 94, 94));
    loadingText.setPosition((int)((960 - loadingText.getGlobalBounds().width) / 2 - 5), 500.0f);
}

sf::Texture loadTexture(const std::string& filepath)
{
    sf::Texture texture;
    texture.loadFromFile(filepath);
    texture.setSmooth(false);
    return texture;
}

void loadingScreen::operate(sf::RenderWindow& window, std::atomic<bool> controlLoaded[], const size_t& numThreads)
{
    bool allFinished = false;
    while (window.isOpen() && !allFinished)
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // std::cout << "Event\n";

            if (event.type == sf::Event::Closed) 
                window.close();
        }

        allFinished = true;
        for (int i = 0; i < numThreads; ++i)
        {
            if (controlLoaded[i] == false)
            {
                allFinished = false;
                break;
            }
        }

        deltaTime = clock.restart().asSeconds();
        loadingAnimation.updateAnimation(deltaTime);
        window.clear(sf::Color(61, 109, 178));
        loadingAnimation.draw(window);
        window.draw(loadingText);
        window.display();
    }

    window.setActive(false);
}

void loadingWrapper(sf::RenderWindow& window, std::atomic<bool> control[], const size_t& numThreads)
{
    window.setActive(true);
    loadingScreen thisLoadingScreen;
    thisLoadingScreen.operate(window, control, numThreads);
}