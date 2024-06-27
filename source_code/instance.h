#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "button.hpp"
#include "textbox.hpp"

#define SHADOWHOR 4
#define SHADOWVER 8
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

    // mode buttons
    sf::Texture modeTexDef;
    sf::Texture modeTexHov; 
    sf::Texture modeTexClick; 
    Button modeButton;
    bool modeButtonActive = false;
    sf::Texture searchModeDef;
    sf::Texture searchModeHov;
    Button searchModeButton;
    sf::Texture importModeDef; 
    sf::Texture importModeHov; 
    Button importModeButton;
    sf::Texture definitionModeDef; 
    sf::Texture definitionModeHov; 
    Button definitionModeButton;

    // search button
    sf::Texture searchTexDef; 
    sf::Texture searchTexHov; 
    sf::Texture searchTexClick;
    Button searchButton;

    // import button
    sf::Texture importTexDef;
    sf::Texture importTexHov;
    sf::Texture importTexClick;
    Button importButton;

    // "import file path" text
    sf::Texture importPromptTexture;
    sf::Sprite importPromptSprite;

    // fonts
    sf::Font PlayfairDisplay;
    sf::Font SourceSans3;
    
    // search box
    sf::Texture searchBoxTexture;
    textbox searchBox;

    // import box
    sf::Texture importBoxTexture;
    textbox importBox;
    private:
    sf::Texture loadTexture(const std::string& filepath)
    {
        sf::Texture texture;
        texture.loadFromFile(filepath);
        return texture;
    }
    sf::Font loadFont(const std::string& filepath)
    {
        sf::Font font;
        font.loadFromFile(filepath);
        return font;
    }
    void switchPage();
    void operatePage1();
    void operatePage2();
    void operatePage3();
    void drawPage1();
    void drawPage2();
    void drawPage3();
};