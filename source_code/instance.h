#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "button.hpp"
#include "textbox.hpp"
#include "trie.h"
#include "readDatasetCSV.hpp"

#define SHADOWHOR 4
#define SHADOWVER 8
class instance
{
    public:
    instance();
    void operate();
    private:
    trieNode* pRoot = nullptr;
    bool autoSave = true;
    int definitionNum = 0;
    std::vector<std::pair<std::string, std::string>> searchResult;
    /*
    0 is not initialized
    1 is no file found
    2 is successful
    4 is other (format not selected)
    */
    int errorMode = 0;


    // SFML
    sf::RenderWindow windowInstance;
    int page = 1; bool pageChange = false;
    bool mouseControl = true;
    bool loadedSave = false;
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
    sf::Font PatuaOne;
    
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

    // import status message
    sf::Text importStatus;
    bool displayStatus = false;

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
    sf::Texture deserializeModeDef;
    sf::Texture deserializeModeHov;
    Button deserializeModeButton;

    // Definition elements
    std::string headWordString = "";
    std::string POSString = "";
    std::string descriptionString = "";
    bool displayDef = false; // control boolean
    int numberOfResult = 0;
    sf::Texture definitionBackground;
    sf::Sprite definitionBackgroundSprite;
    sf::Text headword;
    sf::Text POS;
    sf::Text description;
    sf::Texture nextPageDef;
    sf::Texture nextPageHov;
    sf::Texture nextPageClick;
    spongyButton nextPageButton;
    sf::Texture prevPageDef;
    sf::Texture prevPageHov;
    sf::Texture prevPageClick;
    spongyButton prevPageButton;


    // serialize button
    std::string serializeString = "Serialize";
    sf::Texture serializeTexture;
    Button serializeButton;

    // switch button
    sf::Texture onSwitch;
    sf::Texture offSwitch;
    switchButton autoSaveButton;
    
    // prompts in save mode
    sf::Texture toSaveCurrentTexture;
    sf::Sprite toSaveCurrentSprite;
    sf::Texture autoSaveTexture;
    sf::Sprite autoSaveSprite;

    // loading page
    sf::Texture loadingTexture;
    sf::Sprite loadingSprite;

    // deserialize button
    sf::Texture deserializeTexture;
    Button deserializeButton;

    // prompt in deserialize mode
    sf::Texture toLoadLastSaveTexture;
    sf::Sprite toLoadLastSaveSprite;

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
    
    /*
    Page 1 (main) searching
    Page 2 import
    Page 3 definition searching
    Page 4 words addition
    Page 5 words deletion
    Page 6 words editing
    Page 7 save (serialize)
    Page 8 load (deserialize)
    */
    void operatePage1();
    void operatePage2();
    void operatePage3();
    void operatePage7();
    void operatePage8();
    void drawPage1();
    void drawPage2();
    void drawPage3();
    void drawPage7();
    void drawPage8();

    void switchPage();
    void drawSubModes();
    void hoverSubModes();
    void drawSwitchMode();
    void handleSwitchModeLogic();
    void drawDefinition();
    void saveAutoSaveSetting();
    void resetSearchResult();
    void drawLoadingPage();
    void handleSearchSignal();
};