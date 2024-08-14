#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>

#include "wrapping.hpp"


#include "wrapping.hpp"

#include "wrapping.hpp"

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
protected:
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
    // only use if you know what you are doing
    textbox() {}
    // only use if you know what you are doing
    void setUp(sf::Texture& textboxTexture, sf::Font& font, int characterSize, int limit ,sf::Vector2u position);
    void setPosition(sf::Vector2u position);
    virtual void handleInputLogic(const sf::Event envent, sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);
    std::string getString(bool deselectBox = true);
    virtual void clear();
    bool isSelected() const;
    void setString(std::string input);
    bool isClicked(const sf::RenderWindow& window);
    virtual void select();
    virtual void deselect();
protected:
    virtual void insertChar(char newInput);
    virtual void deleteChar();
    void handleColor();
    virtual void manageFullness();
    void setLimit(int limit);
};
class largeTextbox : public textbox
{
    private:
    int width = 0;
    int lineLimit = 0;
    bool lineLimitReached = false;
    public:
    largeTextbox(sf::Texture& textboxTexture, sf::Font& font, int characterSize, int lineLimit, int width, sf::Vector2u position);
    // void handleInputLogic(const sf::Event event, sf::RenderWindow& window) override;
    void clear() override;
    private:
    void select() override;
    void deselect() override;
    void manageFullness() override;
    void insertChar(char newInput) override;
    void deleteChar() override;
};