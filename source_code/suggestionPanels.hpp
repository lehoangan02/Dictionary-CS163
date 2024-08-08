#pragma once
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "trie.h"

class SuggestionPanels
{
    public:
    void setUp(sf::Texture firstTrioPanelTextureDef, sf::Texture firstTrioPanelTextureHov,
    sf::Texture secondTrioPanelTextureDef, sf::Texture secondTrioPanelTextureHov,
    sf::Texture thirdTrioPanelTextureDef, sf::Texture thirdTrioPanelTextureHov,
    sf::Texture singlePanelTextureDef, sf::Texture singlePanelTextureHov, sf::Font& font);
    void hoverswitchTexture(sf::RenderWindow& window);
    void setPosition(sf::Vector2u position);
    void update(const sf::Event& event, std::string input, trieNode*& pRoot, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    private:
    sf::Texture trioPanelTextureDef[3];
    sf::Texture trioPanelTextureHov[3];
    sf::Texture duoPanelTextureDef[2];
    sf::Texture duoPanelTextureHov[2];
    sf::Texture singlePanelTextureDef[1];
    sf::Texture singlePanelTextureHov[1];
    public:
    bool display = false;
    suggestionButton ButtonArray[3];
    int numberOfButtons = 0;
    std::string buttonStrings[3];
};
