#pragma once


#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
// #include <atomic>
#include <thread>
#include <string>

#include "button.hpp"
#include "textbox.hpp"
#include "animation.hpp"
#include "loadingScreen.hpp"

#include "trie.h"
#include "readDataset.hpp"
#include "history.hpp"
#include "doublyLinkedList.hpp"
#include "SerializeDeserialize.h"
#include "maptable.hpp"
#include "wrapping.hpp"
#include "suggestionPanels.hpp"


#define SHADOWHOR 4
#define SHADOWVER 8
class instance
{
public:
    instance();
    ~instance();
    void operate();

private:
    TrieNode* trieRoot[6]{nullptr};
    HashMap invertedIndex[6];
    std::vector<std::string> word4Def[6];

    bool loadAutoSave = false;
    bool autoSave = true;
    static int definitionNum;
    static std::vector<std::pair<std::string, std::string>> searchResult;
    
    // for use later
    /* import mode error code
    0 is not initialized
    1 is no file found
    2 is successful
    4 is other (format not selected)
    */
    // int errorMode = 0;
    std::vector<std::string> history;
    linkedListNode* pRootFavourite = nullptr;
    linkedListNode* pCurrentFavourite = nullptr;


    enum Dataset
    {
        ENG_ENG,
        VIE_ENG,
        ENG_VIE,
        UNICODE_EMOJI,
        SLANG,
        OTHER
    };

    static int curDataset;

    // boolean to control loading
    bool loadDefinition[6]{false};
    bool loadHistory = false;
    long historyIndex = 0;
    // bool displayHistory = false;
    // bool displayFavourite = false;
    bool loadEmojiImage = false;
    bool getWordToDelete[6]{false};
    bool getWordToEdit[6]{false};

    // SFML
    sf::RenderWindow windowInstance;
    sf::View definitionView;
    private:
    int scrollOffset = 0;
    int maxScrollOffset = std::numeric_limits<int>::max();

    int page = 1; bool pageChange = false;
    bool mouseControl = true;
    bool loadedSave = false;
    bool loadGameMode = false;
    sf::Event event;

    // background (base)
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
    sf::Texture gameModeDef;
    sf::Texture gameModeHov;
    Button gameModeButton;
    sf::Texture emojiTexture;
    sf::Sprite emojiSprite;
    // int emojiNumber;

    // dataset option button
    class incrementalButton : public Button
    {
    private:
        sf::Texture textureDefault[6];
        sf::Texture textureHover[6];
        
    private:
        void hoverSwitchTexture(const sf::RenderWindow& window) override;

    public:
        void setTexture(const sf::Texture& textureDef1, const sf::Texture& textureDef2, const sf::Texture& textureDef3,
        const sf::Texture& textureDef4, const sf::Texture& textureDef5, const sf::Texture& textureDef6,
        const sf::Texture& textureHov1, const sf::Texture& textureHov2, const sf::Texture& textureHov3,
        const sf::Texture& textureHov4, const sf::Texture& textureHov5, const sf::Texture& textureHov6);
        int getNumber();
        void handleIncrementLogic(const sf::Event& event, const sf::RenderWindow& window);
    };

    incrementalButton datasetButton;

    enum DisplayMode
    {
        SEARCH,
        HISTORY,
        FAVOURITE
    };

    static DisplayMode displayMode;

    // search button
    sf::Texture searchTexDef; 
    sf::Texture searchTexHov; 
    sf::Texture searchTexClick;
    Button searchButton;

    // history button
    sf::Texture historyTexDef;
    sf::Texture historyTexHov;
    sf::Texture historyTexClick;
    Button historyButton;

    // favourite button
    sf::Texture favouriteTexDef;
    sf::Texture favouriteTexHov;
    sf::Texture favouriteTexClick;
    Button favouriteButton;

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
    sf::Font micross;
    sf::Font PatuaOne;
    // search box
    sf::Texture searchBoxTexture;
    textbox searchBox;

    // suggestion panels
    static SuggestionPanels suggestionPanels;

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
    static std::string headWordString;
    static std::string POSString;
    static std::string descriptionString;
    static bool displayDef; // control boolean
    static int numberOfResult;
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
    bool wrappedDescription = false;

    // history and favourite
    sf::Texture pageUpDef;
    sf::Texture pageUpHov;
    sf::Texture pageUpClick;
    spongyButton pageUpButton;
    sf::Texture pageDownDef;
    sf::Texture pageDownHov;
    sf::Texture pageDownClick;
    spongyButton pageDownButton;
    sf::Text wordNotInThisDataSet;
    sf::Texture  bookmarkTextureDef;
    sf::Texture  bookmarkTextureClick;
    switchButton bookmarkButton;

    // correct the user input
    static bool showCorrection;
    sf::Texture selectCorrectionTexDef;
    sf::Texture selectCorrectionTexHov;
    Button selectCorrectionButton;
    sf::Text correctUserInput;
    sf::String correctUserInputString;

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

    // delete word page
    sf::Text currentWordText;
    sf::Texture deleteThisWordDef;
    sf::Texture deleteThisWordHov;
    Button deleteThisWordButton;

    // add word page
    sf::Texture modifyTextboxTexture;
    textbox headwordBox;
    textbox POSBox;
    sf::Texture descriptionBoxTexture;
    largeTextbox descriptionBox;
    sf::Texture cancelTexDef;
    sf::Texture cancelTexHov;
    Button cancelButton;
    sf::Texture addTexDef;
    sf::Texture addTexHov;
    Button addButton;
    sf::Texture saveTexDef;
    sf::Texture saveTexHov;
    Button saveButton; // for saving edited words
    sf::Texture changedSuccessfulTexture;
    sf::Texture changedFailedTexture;
    sf::Sprite changedSuccessfulSprite;
    sf::Sprite changedFailedSprite;
    bool changedSuccessful = false;
    bool changedFailed = false;

    // Game mode
    int gameMode = 0; // 1 for random word, 2 for random word4Def
    bool correctAnswer = false;
    bool wrongAnswer = false;
    std::string multipleChoices[4];
    bool validMultipleChoices = false;
    // Animations
    sf::Texture penguinTexture;
    Animation penguinAnimation;
    sf::Texture rainbowStarTexture;
    Animation rainbowStarAnimation;
    sf::Texture scenery;
    Animation sceneryAnimation;
    sf::Texture knightTexture;
    Animation knightAnimation;
    float deltaTime = 0;
    sf::Clock clock;
    float knightTotalTime = 0;
    std::string correctAnswerString = "";
    sf::Texture congratulationsTexture;
    AnimationVertical congratulationsAnimation;
    sf::Texture wrongAnswerTexture;
    sf::Sprite wrongAnswerSprite;

public:
    void moveKnight();
    void resetGameMode(int mode);
    
private:
    // Buttons
    sf::Texture answerButtonTexture;
    Button answerButton1st;
    Button answerButton2nd;
    Button answerButton3rd;
    Button answerButton4th;
    sf::Texture checkAnswerTextureDef;
    sf::Texture checkAnswerTextureHov;
    Button checkAnswerButton;
    sf::Texture gameSearchBoxTexture;
    textbox gameSearchBox;
    sf::Texture choseGameModeTexture;
    Button gameMode1st;
    Button gameMode2nd;
    Button gameMode3rd;
    sf::Texture exitTexture;
    Button exitButton;

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
    int getEmojiNumber(std::string POSString)
    {
        if (POSString.substr(0, 14) != "emoji number: ") return -1;
        int number = 0;
        POSString.erase(0, 14);
        number = std::stoi(POSString);
        printf("[DEBUG] opening: %d\n", number);
        return number;
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
    Page 9 game mode
    */
    void operatePage1();
    void operatePage2();
    void operatePage3();
    void operatePage4();
    void operatePage5();
    void operatePage6();
    void operatePage7();
    void operatePage8();
    void operatePage9();
    void drawPage1();
    void drawPage2();
    void drawPage3();
    void drawPage4();
    void drawPage5();
    void drawPage6();
    void drawPage7();
    void drawPage8();
    void drawPage9();

    void switchPage();
    void drawSubModes();
    void hoverSubModes();
    void drawSwitchMode();
    void handleSwitchModeLogic();
    void drawDefinition();
    void loadAutoSaveSetting();
    void saveAutoSaveSetting();
    static void resetSearchResult();
    void drawLoadingPage();
    void handleSearchSignal(std::string input);
    void handleHistory();
    void initiateSearch();
    void setUpErrorText();
    void handleFavourite();
    void setUpGameModeAnimation();
};
