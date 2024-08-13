#include "button.hpp"
// for non-text, non-hover buttons
Button::Button(const sf::Texture& texture)
    {
        this -> textureDefault = texture;
        buttonSprite.setTexture(textureDefault);
        clickToChange = false;
    }
    
/// for non-hover, text button
Button::Button(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize)
{
    clickToChange = false;
    this -> textureDefault = texture;
    buttonSprite.setTexture(textureDefault);
    haveText = true;
    this -> characterSize = characterSize;
    buttonText.setFont(font);
    buttonText.setCharacterSize(characterSize);
    buttonText.setString(textString);
    centerText();
}

/// for non-text, hover buttons
Button::Button(const sf::Texture& textureDefault, const sf::Texture& textureHover)
{
    hover = true;
    this -> textureDefault = textureDefault;
    buttonSprite.setTexture(textureDefault);
    this -> textureHover = textureHover;
    clickToChange = false;
}

/// for non-text, hover and menu-click button
Button::Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick)
{
    hover = true;
    this -> textureDefault = textureDefault;
    buttonSprite.setTexture(textureDefault);
    this -> textureHover = textureHover;
    this -> textureClick = textureClick;
}

/// for text and hover buttons
Button::Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
std::string textString, int characterSize)
{
    clickToChange = false;
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
    buttonText.setStyle(sf::Text::Style::Bold);
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
bool Button::isClicked(const sf::RenderWindow& window)
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
        buttonSprite.setTexture(textureHover, true);
        if (haveText)
        {
            buttonText.setStyle(sf::Text::Style::Underlined | sf::Text::Style::Bold);
        }
    }
    else
    {
        buttonSprite.setTexture(textureDefault, true);
        if (haveText)
        {
            buttonText.setStyle(sf::Text::Style::Bold);
        }
    }
}
void Button::centerText()
    {
        if (!haveText) return;
        if (shadow)
        {
            buttonText.setPosition((int)(buttonPosition.x + (buttonSprite.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2),
        (int)(buttonPosition.y + (buttonSprite.getGlobalBounds().height - SHADOWVER - characterSize) / 2 - SFMLTEXPADDING));
        }
        else
        {
            buttonText.setPosition((int)(buttonPosition.x + (buttonSprite.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2),
        (int)(buttonPosition.y + (buttonSprite.getGlobalBounds().height - characterSize) / 2 - SFMLTEXPADDING));
        }
    }

void Button::setText(std::string text)
{
    this -> buttonText.setString(text);
    std::cout << "setting suggestion text: " << text << std::endl;
    centerText();
}
void Button::select(bool mode)
{
    selected = mode;
    if (selected)
    {
        if (clickToChange)
        {
            buttonSprite.setTexture(textureClick, true);
        }
    }
    else
    {
        if (!hover)
        {
            buttonSprite.setTexture(textureDefault, true);
        }
    }
}

/// @brief set up the button, only use this when you know what you are doing
/// @param texture 
/// @param font 
/// @param textString 
/// @param characterSize 
void Button::setUpHoverText(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
std::string textString, int characterSize)
{
    clickToChange = false;
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
    buttonText.setStyle(sf::Text::Style::Bold);
    centerText();
}

/// @brief set up the button, only use this when you know what you are doing
/// @param texture 
/// @param font 
/// @param textString 
/// @param characterSize 
void Button::setUpNonHoverText(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize)
{
    clickToChange = false;
    this -> textureDefault = texture;
    buttonSprite.setTexture(textureDefault);
    haveText = true;
    this -> characterSize = characterSize;
    buttonText.setFont(font);
    buttonText.setCharacterSize(characterSize);
    buttonText.setString(textString);
    centerText();
}

void Button::setTextFillColor(sf::Color color)
{
    this -> buttonText.setFillColor(color);
}

/// use this for stable ordinary button.
/// stable meaning it does not disapplear when interacting in the same page.
/// ordinary meaning it does not have persistent characteristic.
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
DualChoiceButton::DualChoiceButton(sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick, DualChoiceButton* ButtonToLink) :
    Button(textureDefault, textureHover, textureClick)
{
    this -> textureDefault.setSmooth(true);
    this -> textureClick.setSmooth(true);
    buttonSprite.setTexture(this -> textureDefault);
    this -> ButtonToLink = ButtonToLink;
}
void DualChoiceButton::click(sf::RenderWindow& window)
{
    if (isClicked(window))
    {
        if (selected) return;
        select(true);
        buttonSprite.move(offset);
        if (!(*ButtonToLink).selected) return;
        ButtonToLink -> select(false);
        (*ButtonToLink).buttonSprite.move(offsetNeg);
    }
}
bool DualChoiceButton::getSelected()
{
    return selected;
}


switchButton::switchButton(sf::Texture& textureDefault, const sf::Texture& textureClick) :
    Button(textureDefault, textureDefault, textureClick)
{
    selected = true;
}

/// @brief use is button for clicking logic, instead of the default base class's function with the same name
/// @param window 
/// @param mouseControl 
void switchButton::click(sf::RenderWindow& window, bool& mouseControl)
{
    if (isClicked(window) && mouseControl)
    {
        // printf("[DEBUG] clicked\n");
        selected = !selected;
        select();
        mouseControl = false;
    }
    return;
}
void switchButton::select()
{
    if (selected)
    {
        // printf("[DEBUG] on\n");
        buttonSprite.setTexture(textureClick, true);
    }
    else
    {
        // printf("[DEBUG] off\n");
        buttonSprite.setTexture(textureDefault, true);
    }
}
bool switchButton::getMode()
{
    return selected;
}
void switchButton::setMode(bool mode)
{
    selected = mode;
    select();
}


spongyButton::spongyButton(sf::Texture& textureDefault, const sf::Texture& textureHov, const sf::Texture& textureClick) :
    Button(textureDefault, textureHov, textureClick)
    {
        return;
    }
void spongyButton::setOffset(float x, float y)
{
    offset.x = x;
    offset.y = y;
}
void spongyButton::click(sf::RenderWindow& window)
{
    if (isClicked(window))
    {
        select(true);
        if (offsetControl[0])
        {
            buttonSprite.move(offset);
            offsetControl[0] = false;
            offsetControl[1] = true;
        }
    }
    else
    {
        select(false);
        if (offsetControl[1] == true)
        {
            buttonSprite.move(-offset);
            offsetControl[1] = false;
            offsetControl[0] = true;
        }
    }
    return;
}

void suggestionButton::centerText()
{
    if (shadow)
        {
            buttonText.setPosition(positionLeft + 20,
        (int)(buttonPosition.y + (buttonSprite.getGlobalBounds().height - SHADOWVER - characterSize) / 2 - SFMLTEXPADDING));
        }
        else
        {
            buttonText.setPosition(positionLeft + 20,
        (int)(buttonPosition.y + (buttonSprite.getGlobalBounds().height - characterSize) / 2 - SFMLTEXPADDING));
        }
}

void suggestionButton::setPosition(sf::Vector2u position)
{
    buttonPosition = position;
    buttonSprite.setPosition((float)position.x, (float)position.y);
    centerText();
    positionLeft = position.x;
}

void suggestionButton::setTexture(sf::Texture& textureDef, sf::Texture& textureHov, bool shadow)
{
    this -> textureDefault = textureDef;
    this -> textureHover = textureHov;
    buttonSprite.setTexture(textureDefault, true);
    if (shadow) 
    {
        buttonSprite.setPosition(positionLeft - SHADOWHOR, buttonPosition.y);
    }
    else 
    {
        buttonSprite.setPosition(positionLeft, buttonPosition.y);
    }
    this -> shadow = shadow;
    centerText();
}

void incrementalButton::setTexture(const sf::Texture& textureDef1, const sf::Texture& textureDef2, const sf::Texture& textureDef3,
    const sf::Texture& textureDef4, const sf::Texture& textureDef5, const sf::Texture& textureDef6,
    const sf::Texture& textureHov1, const sf::Texture& textureHov2, const sf::Texture& textureHov3,
    const sf::Texture& textureHov4, const sf::Texture& textureHov5, const sf::Texture& textureHov6)
    {
        textureDefault[0] = textureDef1; textureHover[0] = textureHov1;
        textureDefault[1] = textureDef2; textureHover[1] = textureHov2;
        textureDefault[2] = textureDef3; textureHover[2] = textureHov3;
        textureDefault[3] = textureDef4; textureHover[3] = textureHov4;
        textureDefault[4] = textureDef5; textureHover[4] = textureHov5;
        textureDefault[5] = textureDef6; textureHover[5] = textureHov6;

        buttonSprite.setTexture(textureDefault[0]);
    }

void incrementalButton::hoverSwitchTexture(const sf::RenderWindow& window)
{
    if (isHovering(window))
    {
        buttonSprite.setTexture(textureHover[incrementTracker]);
    }
    else
    {
        buttonSprite.setTexture(textureDefault[incrementTracker]);
    }
}

void incrementalButton::handleIncrementLogic(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed && isClicked(window))
    {
        if (incrementTracker < 5)
        {
            ++incrementTracker;
        }
        else
        {
            incrementTracker = 0;
        }
    }
    hoverSwitchTexture(window);
}

int incrementalButton::getNumber()
{
    return incrementTracker;
}
