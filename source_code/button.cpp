#include "button.hpp"
// for non-text, non-hover buttons
Button::Button(const sf::Texture& texture)
    {
        this -> textureDefault = texture;
        buttonSprite.setTexture(textureDefault);
    }
// for non-hover, text button
Button::Button(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize)
{
    this -> textureDefault = texture;
    buttonSprite.setTexture(textureDefault);
    haveText = true;
    this -> characterSize = characterSize;
    buttonText.setFont(font);
    buttonText.setCharacterSize(characterSize);
    buttonText.setString(textString);
    centerText();
}
// for non-text, hover buttons
Button::Button(const sf::Texture& textureDefault, const sf::Texture& textureHover)
{
    hover = true;
    this -> textureDefault = textureDefault;
    buttonSprite.setTexture(textureDefault);
    this -> textureHover = textureHover;
}
// for non-text, hover and persistent click button
Button::Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick)
{
    hover = true;
    persistentClick = true;
    this -> textureDefault = textureDefault;
    buttonSprite.setTexture(textureDefault);
    this -> textureHover = textureHover;
    this -> textureClick = textureClick;
}
// for text and hover buttons
Button::Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
std::string textString, int characterSize)
{
    haveText = true;
    hover = true;
    // set up the sprite
    this -> textureDefault = textureDefault;
    buttonSprite.setTexture(textureDefault);
    this -> textureHover = textureHover;
    // set up the text
    buttonText.setFont(font);
    this -> characterSize = characterSize;
    buttonText.setCharacterSize (characterSize);
    buttonText.setString(textString);
    centerText();
}
void Button::setPosition(sf::Vector2u position)
{
    buttonPosition = position;
    buttonSprite.setPosition((float)position.x, (float)position.y);
    centerText();
}
void Button::draw(sf::RenderWindow& window)
{
    window.draw(buttonSprite);
    window.draw(buttonText);
}
bool Button::isClicked(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
    && mousePosition.x > (int)buttonPosition.x && mousePosition.x < (int)buttonPosition.x + (int)buttonSprite.getGlobalBounds().width
    && mousePosition.y > (int)buttonPosition.y && mousePosition.y < (int)buttonPosition.y + (int)buttonSprite.getGlobalBounds().height)
    {
        return true;
    }
    return false;
}
bool Button::isHovering(const sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (mousePosition.x > (int)buttonPosition.x && mousePosition.x < (int)buttonPosition.x + (int)buttonSprite.getGlobalBounds().width
    && mousePosition.y > (int)buttonPosition.y && mousePosition.y < (int)buttonPosition.y + (int)buttonSprite.getGlobalBounds().height)
    {
        return true;
    }
    return false;
    
}
void Button::hoverSwitchTexture(const sf::RenderWindow& window)
{
    if (!hover) return;
    if (selected) return;
    if (isHovering(window))
    {
        buttonSprite.setTexture(textureHover);
        if (haveText)
        {
            buttonText.setStyle(sf::Text::Style::Underlined);
        }
    }
    else
    {
        buttonSprite.setTexture(textureDefault);
        if (haveText)
        {
            buttonText.setStyle(sf::Text::Style::Regular);
        }
    }
}
void Button::centerText()
    {
        buttonText.setPosition((int)(buttonPosition.x + (buttonSprite.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2),
        (int)(buttonPosition.y + (buttonSprite.getGlobalBounds().height - characterSize) / 2));
    }
void Button::select(bool mode)
{
    selected = mode;
    if (selected)
    {
        buttonSprite.setTexture(textureClick);
    }
}
void Button::click(sf::RenderWindow& window)
{
    if (isClicked(window))
    {
        select(true);
    }
    else
    {
        select(false);
    }
    return;
}