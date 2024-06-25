#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
class instance
{
    public:
    instance();
    void operate();
    private:
    sf::RenderWindow windowInstance;
    int page = 1;
    sf::Event event;
    sf::Texture baseLayer; 
    sf::Sprite baseLayerSprite;
    sf::Texture modeTexDef;
    sf::Texture modeTexHov; 
    sf::Texture modeTexClick; 
    Button modeButton;
    bool active = false;
    sf::Texture searchModeDef;
    sf::Texture searchModeHov;
    Button searchModeButton;
    sf::Texture importModeDef; 
    sf::Texture importModeHov; 
    Button importModeButton;
    sf::Texture definitionModeDef; 
    sf::Texture definitionModeHov; 
    Button definitionModeButton;
    sf::Texture searchTexDef; 
    sf::Texture searchTexHov; 
    sf::Texture searchTexClick;
    Button searchButton;

    private:
    sf::Texture loadTexture(const std::string& filepath)
    {
        sf::Texture texture;
        texture.loadFromFile(filepath);
        return texture;
    }
    void operatePage1();
    void operatePage2();
    void drawPage1();
    void drawPage2();
};