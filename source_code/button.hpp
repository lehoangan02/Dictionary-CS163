#include <SFML/Graphics.hpp>
#include <string>

class Button
{
    private:
    sf::Text buttonText;
    int characterSize;
    sf::Vector2u buttonPosition;
    sf::Sprite buttonSprite;
    sf::Texture textureDefault, textureHover;
    bool haveText = false;
    bool hover = false;
    public:
    Button(const sf::Texture& texture)
    {
        this -> textureDefault = texture;
        buttonSprite.setTexture(textureDefault);
    }
    Button(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize)
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
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover)
    {
        hover = true;
        this -> textureDefault = textureDefault;
        buttonSprite.setTexture(textureDefault);
        this -> textureHover = textureHover;
    }
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
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
    void setPosition(sf::Vector2u position)
    {
        buttonPosition = position;
        buttonSprite.setPosition((float)position.x, (float)position.y);
        centerText();
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(buttonSprite);
        window.draw(buttonText);
    }
    bool isClicked(sf::RenderWindow& window)
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
    bool isHovering(const sf::RenderWindow& window)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (mousePosition.x > (int)buttonPosition.x && mousePosition.x < (int)buttonPosition.x + (int)buttonSprite.getGlobalBounds().width
        && mousePosition.y > (int)buttonPosition.y && mousePosition.y < (int)buttonPosition.y + (int)buttonSprite.getGlobalBounds().height)
        {
            return true;
        }
        return false;
        
    }
    void hoverSwitchTexture(const sf::RenderWindow& window)
    {
        if (!hover) return;
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
    private:
    void centerText()
    {
        buttonText.setPosition(buttonPosition.x + (buttonSprite.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2,
        buttonPosition.y + (buttonSprite.getGlobalBounds().height - characterSize) / 2);
    }
};