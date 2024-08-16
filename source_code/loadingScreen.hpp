#pragma once
#include <SFML/Graphics.hpp>
#include <atomic>
#include "animation.hpp"

// void loadingWrapper(sf::RenderWindow& window, std::atomic<bool>& control);
void loadingWrapper(sf::RenderWindow& window, std::atomic<bool> control[], const size_t& numThreads);
sf::Texture loadTexture(const std::string& filepath);

class loadingScreen
{
    private:
    float deltaTime = 0.0f;
    sf::Texture loadingTexture;
    sf::Font magarine;
    sf::Text loadingText;
    // sf::Event event;
    sf::Clock clock;
    AnimationVertical loadingAnimation;
    public:
    loadingScreen();
    // void operate(sf::RenderWindow& window, std::atomic<bool>& controlLoaded);
    void operate(sf::RenderWindow& window, std::atomic<bool> controlLoaded[], const size_t& numThreads);
};