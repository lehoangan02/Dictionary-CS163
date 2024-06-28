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
    int page = 1; bool pageChange = false;
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
    sf::Texture settingModeDef; 
    sf::Texture settingModeHov; 
    Button settingModeButton;
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

    // dataset format boxes
    sf::Texture TXTTextureDef;
    sf::Texture TXTTextureClick;
    DualChoiceButton TXTButton;
    sf::Texture CSVTextureDef;
    sf::Texture CSVTextureClick;
    DualChoiceButton CSVButton;

    // "select file format" prompt
    sf::Texture formatPromptTexture;
    sf::Sprite formatPromptSprite;

    // Sub-mode buttons in setting (setting is import mode)
    sf::Texture importModeDef;
    sf::Texture importModeHov;
    Button importModeButton;
    sf::Texture addModeDef;
    sf::Texture addModeHov;
    Button addModeButton;
    sf::Texture deleteModeDef;
    sf::Texture deleteModeHov;
    Button deleteModeButton;
    sf::Texture editModeDef;
    sf::Texture editModeHov;
    Button editModeButton;
    sf::Texture saveModeDef;
    sf::Texture saveModeHov;
    Button saveModeButton;
    sf::Texture serializeModeDef;
    sf::Texture serializeModeHov;
    Button serializeModeButton;

    // Definition elements
    sf::Texture definitionBackground;
    sf::Sprite definitionBackgroundSprite;
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
    void drawSubModes();
    void hoverSubModes();
    void drawSwitchMode();
    void handleSwitchModeLogic();
};