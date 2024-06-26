#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>

#define SHADOWHOR 4
#define SHADOWVER 8
#define SFMLTEXPADDING 6

/*
Press Escape to deselect.
You (should) use the select() function when Enter/Return is pressed.
Use getString.
*/

class textbox
{
private:
    sf::Sprite textboxSprite;
    sf::Texture textboxTexture;
    sf::Text displayText;
    std::string textString = "";
    std::stringstream textStream;
    std::string guideString = "Type here";
    sf::Font font;
    int characterSize = 0;
    bool active = false;
    std::string textCursor = "_";
    bool full = false;
    int limit = 0;
    int numChar = 0;
public:
    textbox(sf::Texture& textboxTexture, sf::Font& font, int characterSize, int limit ,sf::Vector2u position);
    void setPosition(sf::Vector2u position);
    void handleInputLogic(const sf::Event envent, sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);
    std::string getString();
private:
    void insertChar(char newInput);
    void deleteChar();
    void handleColor();
    void select();
    void deselect();
    void manageFullness();
    void setLimit(int limit);
};