#include "suggestionPanels.hpp"

void SuggestionPanels::setUp(sf::Texture firstTrioPanelTextureDef, sf::Texture firstTrioPanelTextureHov,
    sf::Texture secondTrioPanelTextureDef, sf::Texture secondTrioPanelTextureHov,
    sf::Texture thirdTrioPanelTextureDef, sf::Texture thirdTrioPanelTextureHov,
    sf::Texture singlePanelTextureDef, sf::Texture singlePanelTextureHov, sf::Font& font)
{
        trioPanelTextureDef[0] = firstTrioPanelTextureDef;
        trioPanelTextureDef[1] = secondTrioPanelTextureDef;
        trioPanelTextureDef[2] = thirdTrioPanelTextureDef;
        trioPanelTextureHov[0] = firstTrioPanelTextureHov;
        trioPanelTextureHov[1] = secondTrioPanelTextureHov;
        trioPanelTextureHov[2] = thirdTrioPanelTextureHov;

        duoPanelTextureDef[0] = firstTrioPanelTextureDef;
        duoPanelTextureDef[1] = thirdTrioPanelTextureDef;
        duoPanelTextureHov[0] = firstTrioPanelTextureHov;
        duoPanelTextureHov[1] = thirdTrioPanelTextureHov;

        this -> singlePanelTextureDef[0] = singlePanelTextureDef;
        this -> singlePanelTextureHov[0] = singlePanelTextureHov;

        buttonStrings[0] = "button 1";
        buttonStrings[1] = "button 2";
        buttonStrings[2] = "button 3";

        ButtonArray[0].setUpHoverText(trioPanelTextureDef[0], trioPanelTextureHov[0], font, buttonStrings[0], 24);
        ButtonArray[1].setUpHoverText(trioPanelTextureDef[1], trioPanelTextureHov[1], font, buttonStrings[1], 24);
        ButtonArray[2].setUpHoverText(trioPanelTextureDef[2], trioPanelTextureHov[2], font, buttonStrings[2], 24);
}

void SuggestionPanels::setPosition(sf::Vector2u position)
{
    ButtonArray[0].setPosition(position);
    position.y += 65;
    ButtonArray[1].setPosition(position);
    position.y += 65;
    ButtonArray[2].setPosition(position);
}

void SuggestionPanels::hoverswitchTexture(sf::RenderWindow& window)
{
    for (int i = 0; i < numberOfButtons; ++i)
    {
        ButtonArray[i].hoverSwitchTexture(window);
    }
}

void SuggestionPanels::update(const sf::Event& event, std::string input, trieNode*& pRoot, sf::RenderWindow& window)
{
    if (event.type != sf::Event::KeyPressed && event.type != sf::Event::TextEntered) return;
    std::vector<std::string> suggestingWords = SuggestingWords(input, pRoot);
    int suggestingSize = (int)suggestingWords.size();
    printf("number of suggestions are: %d\n", (int)suggestingWords.size());
    if (suggestingSize >= 3)
    {
        numberOfButtons = 3;
        // for (int i = 0; i < 3; ++i)
        // {
        //     bool shadow = false;
        //     if (i == 2) shadow = true;
        //     ButtonArray[i].setTexture(trioPanelTextureDef[i], trioPanelTextureHov[i], shadow);
        // }
        ButtonArray[0].setTexture(trioPanelTextureDef[0], trioPanelTextureHov[0], false);
        ButtonArray[1].setTexture(trioPanelTextureDef[1], trioPanelTextureHov[1], false);
        ButtonArray[2].setTexture(trioPanelTextureDef[2], trioPanelTextureHov[2], true);
    }
    else if (suggestingSize == 2)
    {
        numberOfButtons = 2;
        ButtonArray[0].setTexture(trioPanelTextureDef[0], trioPanelTextureHov[0], false);
        ButtonArray[1].setTexture(trioPanelTextureDef[2], trioPanelTextureHov[2], true);
    }
    else if (suggestingSize == 1)
    {
        numberOfButtons = 1;
        ButtonArray[0].setTexture(singlePanelTextureDef[0], singlePanelTextureHov[0], true);
    }
    else if (suggestingSize == 0)
    {
        numberOfButtons = 0;
    }
    for (int i = 0; i < numberOfButtons; ++i)
    {
        buttonStrings[i] = suggestingWords[i];
        ButtonArray[i].setText(buttonStrings[i]);
    }
    hoverswitchTexture(window); // this may be removed later
}

void SuggestionPanels::draw(sf::RenderWindow& window)
{
    if (!display) return;
    for (int i = 0; i < numberOfButtons; ++i)
    {
        ButtonArray[i].draw(window);
    }
}
