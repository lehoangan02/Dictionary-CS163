#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define SHADOWHOR 4
#define SHADOWVER 8
#define SFMLTEXPADDING 6

class Button
{
    protected:
    int characterSize;
    sf::Vector2u buttonPosition;
    sf::Sprite buttonSprite;
    sf::Texture textureDefault, textureHover, textureClick;
    bool clickToChange = true;
    bool haveText = false;
    bool hover = false;
    bool selected = false;
    public:
    sf::Text buttonText;
    bool shadow = true;
    public:
    Button() {}
    Button(const sf::Texture& texture);
    Button(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize);
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover);
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick);
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
    std::string textString, int characterSize);
    virtual void setPosition(sf::Vector2u position);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::RenderWindow& window);
    bool isHovering(const sf::RenderWindow& window);
    virtual void hoverSwitchTexture(const sf::RenderWindow& window);
    // void setOffset(float x, float y);
    void select(bool mode);
    void setTextFillColor(sf::Color color);
    void setText(std::string text);

    // only use these when you know what you are doing
    void setUpHoverText(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
std::string textString, int characterSize);
    void setUpNonHoverText(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize);
    virtual void click(sf::RenderWindow& window);
    protected:
    virtual void centerText();
};
class DualChoiceButton : public Button
{
    public:
    DualChoiceButton(sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick, DualChoiceButton* ButtonToLink);
    void click(sf::RenderWindow& window) override;
    bool getSelected();
    private:
    DualChoiceButton* ButtonToLink;
    sf::Vector2f offset = sf::Vector2f(8.0f, 4.0f);
    sf::Vector2f offsetNeg = sf::Vector2f(-8.0f, -4.0f);
};
class switchButton : public Button
{
    public:
    switchButton(sf::Texture& textureDefault, const sf::Texture& textureClick);
    void click(sf::RenderWindow& window, bool& mouseControl);
    void select();
    bool getMode();
    void setMode(bool mode);
};
class spongyButton : public Button
{
    public:
    spongyButton(sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick);
    sf::Vector2f offset = sf::Vector2f(0.0f, 0.0f);
    void click(sf::RenderWindow& window);
    void setOffset(float x, float y);
    private:
    bool offsetControl[2] = {true, false};
};
class suggestionButton : public Button
{
    private:
    int positionLeft = 0;
    public:
    void centerText() override;
    void setPosition(sf::Vector2u position) override;
    void setTexture(sf::Texture& textureDef, sf::Texture& textureHov, bool shadow);
};