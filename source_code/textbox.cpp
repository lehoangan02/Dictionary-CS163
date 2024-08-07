#include "textbox.hpp"

textbox::textbox(sf::Texture& textboxTexture, sf::Font& font, int characterSize, int limit, sf::Vector2u position)
{
    this -> textboxTexture = textboxTexture;
    this -> textboxSprite.setTexture(textboxTexture);
    displayText.setFont(font);
    this -> characterSize = characterSize;
    this -> displayText.setString(guideString);
    textStream << guideString;
    setPosition(position);
    displayText.setStyle(sf::Text::Bold);
    displayText.setFillColor(sf::Color(138, 138, 141));
    setLimit(limit);
    
}
/// @brief only use if you know what you are doing
/// @param textboxTexture 
/// @param font 
/// @param characterSize 
/// @param limit 
/// @param position 
void textbox::setUp(sf::Texture& textboxTexture, sf::Font& font, int characterSize, int limit ,sf::Vector2u position)
{
    this -> textboxTexture = textboxTexture;
    this -> textboxSprite.setTexture(textboxTexture);
    displayText.setFont(font);
    this -> characterSize = characterSize;
    this -> displayText.setString(guideString);
    textStream << guideString;
    setPosition(position);
    displayText.setStyle(sf::Text::Bold);
    displayText.setFillColor(sf::Color(138, 138, 141));
    setLimit(limit);
}

void textbox::setPosition(sf::Vector2u position)
{
    this -> textboxSprite.setPosition((float)position.x, (float)position.y);
    sf::Vector2f displayTextPosition;
    displayTextPosition.x = (float)(int)(textboxSprite.getPosition().x + 20);
    // std::cout << (int)(textboxSprite.getGlobalBounds().height - SHADOWVER - (float)characterSize) / 2 << std::endl;
    displayTextPosition.y = (float)(int)(textboxSprite.getPosition().y + (textboxSprite.getGlobalBounds().height - SHADOWVER - (float)characterSize) / 2 - SFMLTEXPADDING);
    this -> displayText.setPosition(displayTextPosition);
}
void textbox::draw(sf::RenderWindow &window)
{
    window.draw(textboxSprite);
    window.draw(displayText);
}
void textbox::handleInputLogic(const sf::Event event, sf::RenderWindow& window)
{
    if (active)
    {
        if (event.type == sf::Event::TextEntered && !full
        && (int)event.text.unicode >= 32 && (int)event.text.unicode < 127)
        {
            // printf("[DEBUG] text pressed\n");
            insertChar((char)event.text.unicode);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::BackSpace)
            {
                // printf("[DEBUG] backspace pressed\n");
                deleteChar();
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                printf("[DEBUG] escape pressed\n");
                deselect();
            }
            else if (event.key.code == sf::Keyboard::Return)
            {
                printf("[DEBUG] enter pressed\n");
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        // std::cout << "[DEBUG] Sprite position: " << textboxSprite.getPosition().y << " - "
        // << textboxSprite.getPosition().y + textboxSprite.getGlobalBounds().height - SHADOWVER << " - "
        // << textboxSprite.getPosition().x + SHADOWHOR << " - "
        // << textboxSprite.getPosition().x + textboxSprite.getGlobalBounds().width - SHADOWHOR << std::endl;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        // std::cout << "[DEBUG] Mouse position: " << mousePosition.y << " - " << mousePosition.x << std::endl;
        if (mousePosition.y > textboxSprite.getPosition().y
        && mousePosition.y < textboxSprite.getPosition().y + textboxSprite.getGlobalBounds().height - SHADOWVER
        && mousePosition.x > textboxSprite.getPosition().x + SHADOWHOR
        && mousePosition.x < textboxSprite.getPosition().x + textboxSprite.getGlobalBounds().width - SHADOWHOR)
        {
            // std::cout << "[DEBUG] clicked in textbox\n";
            select();
        }
        else
        {
            deselect();
        }
    }

    handleColor();
    // convert textStream to textString
    textString = textStream.str();
    displayText.setString(textString);
}
void textbox::handleColor()
{
    // printf("[DEBUG] handle color ");
    if (!active)
    {
        if (textStream.str() == "")
        {
            displayText.setFillColor(sf::Color(138, 138, 141));
            textStream.str("");
            textStream << guideString;
            // printf("[DEBUG] set grey\n");
        }
    }
    else
    {
        displayText.setFillColor(sf::Color(0, 0, 0));
        // printf("[DEBUG] set black\n");
    }
}
void textbox::select() 
{
    if (active) return;
    // printf("[DEBUG] %d\n", limit);
    active = true;
    if (!full) // insert cursor
    {
        printf("[DEBUG] not full and selected\n");
        if (textStream.str() == guideString)
        {
            printf("[DEBUG] resetting\n");
            textStream.str("");
        }
        textStream << textCursor;
    }
}
void textbox::deselect()
{
    if (active)
    {
        active = false;
        if (!full && textStream.str() != guideString) // remove cursor
        {
            std::string temp = textStream.str();
            textStream.str("");
//            std::cout << "[DEBUG] " << (temp.empty()) << std::endl;
//            std::cout << "[DEBUG] " << temp.length() << std::endl;
            for (int i = 0; i < (int)temp.length() - 1; ++i)
            {
                textStream << temp[i];
            }
        }
    }
}
void textbox::insertChar(char newInput)
{
    if (full) return;
    std::string temp = textStream.str();
    textStream.str("");
    for (int i = 0; i < (int)temp.length() - 1; ++i)
    {
        textStream << temp[i];
    }
    textStream << newInput;
    // handle full logic here
    ++numChar;
    manageFullness();
    // std::cout << "[DEBUG]  after inserting it's "; 
    if (!full)
    {
        textStream << textCursor;
    }
}
void textbox::deleteChar()
{
    if (textStream.str() == textCursor) return;
    std::string temp = textStream.str();
    textStream.str("");
    if (!full)
    {
        for (int i = 0; i < (int)temp.length() - 2; ++i)
        {
            textStream << temp[i];
        }
    }
    else
    {
        for (int i = 0; i < (int)temp.length() - 1; ++i)
        {
            textStream << temp[i];
        }
    }
    textStream << textCursor;
    --numChar;
    manageFullness();
    
}
void textbox::manageFullness()
{
    if (numChar >= limit)
    {
        full = true;
    }
    else
    {
        full = false;
    }
//   if (displayText.getPosition().x + displayText.getGlobalBounds().width + characterSize * 2
//   > textboxSprite.getPosition().x + textboxSprite.getGlobalBounds().width)
//   {
//     full = true;
//   }
//   else
//   {
//     full = false;
//   }
}
void textbox::setLimit(int limit)
{
    this -> limit = limit;
}
std::string textbox::getString(bool deselectBox)
{
    if (textStream.str() == guideString)
    {
        return "";
    }
    if (deselectBox) deselect();
    if (active && !full)
        return textStream.str().substr(0, textStream.str().size()- 1);
    else
        return textStream.str();
}
void textbox::clear()
{
    // printf("[DEBUG] clearing ");
    textStream.str("");
    deselect();
    handleColor();
    textStream.str(guideString);
    numChar = 0;
    manageFullness();
    displayText.setString(textStream.str());
    return;
}


largeTextbox::largeTextbox(sf::Texture& textboxTexture, sf::Font& font, int characterSize, int lineLimit, int width, sf::Vector2u position) :
    textbox(textboxTexture, font, characterSize, std::numeric_limits<int>::max(), position)
    {
        this -> width = width;
        this  -> lineLimit = lineLimit;
        displayText.setPosition(position.x + 20, position.y + 10);
    }
bool textbox::isSelected() const
{
    return active;
}

/// @brief the only difference with the base class function is the displayText.setString at the end
void largeTextbox::select() 
{
    std::string temp = displayText.getString();
    textStream.str(temp);
    if (active) return;
    // printf("[DEBUG] %d\n", limit);
    active = true;
    if (!full) // insert cursor
    {
        printf("[DEBUG] not full and selected\n");
        if (textStream.str() == guideString)
        {
            printf("[DEBUG] resetting\n");
            textStream.str("");
        }
        temp = textStream.str();
        textStream.str(temp + textCursor);
        displayText.setString(textStream.str());
    }
}

/// @brief the only difference with the base class function is the displayText.setString at the end
void largeTextbox::deselect()
{
    std::string temp = displayText.getString();
    textStream.str(temp);
    if (active)
    {
        active = false;
        if (!full && textStream.str() != guideString) // remove cursor
        {
            std::string temp = textStream.str();
            textStream.str("");
//            std::cout << "[DEBUG] " << (temp.empty()) << std::endl;
//            std::cout << "[DEBUG] " << temp.length() << std::endl;
            for (int i = 0; i < (int)temp.length() - 1; ++i)
            {
                textStream << temp[i];
            }
        }
        displayText.setString(textStream.str());
    }
}

void largeTextbox::manageFullness()
{
    if (lineLimitReached)
    {
        full = true;
    }
    else
    {
        full = false;
    }
}

void largeTextbox::insertChar(char newInput)
{
    // printf("[DEBUG] trying to input\n");
    if (full) return;
    std::string temp = textStream.str();
    textStream.str("");
    for (int i = 0; i < (int)temp.length() - 1; ++i)
    {
        textStream << temp[i];
    }
    textStream << newInput;
    // handle full logic from here
    ++numChar;
    // wrap the text
    displayText.setString(textStream.str());
    lineLimitReached = wrapText(displayText, width, 6) ? true : false;
    temp = displayText.getString();
    textStream.str(temp);
    manageFullness();
    // std::cout << "[DEBUG]  after inserting it's "; 
    if (!full)
    {
        textStream.str(temp + textCursor);
    }
}
void largeTextbox::deleteChar()
{
    // printf("[DEBUG] trying to delete\n");
    if (textStream.str() == textCursor) return;
    std::string temp = textStream.str();
    textStream.str("");
    if (full)
    {
        temp.pop_back();
    }
    else
    {
        temp.pop_back();
        temp.pop_back();
    }
    lineLimitReached = wrapText(displayText, width, 6) ? true : false;
    manageFullness();
    if (!full)
        textStream.str(temp + textCursor);
    else
        textStream.str(temp);
    printf("[DELETE_TEST] %s\n", textStream.str().c_str());
    --numChar;
    // wrap the text
    displayText.setString(textStream.str());
    
    
}

void largeTextbox::clear()
{
    // printf("[DEBUG] clearing ");
    deselect();
    textStream.str("");
    // printf("[DEBUG] textStream: %s\n", textStream.str().c_str());
    handleColor();
    textStream.str(guideString);
    numChar = 0;
    manageFullness();
    full = false;
    displayText.setString(textStream.str());
    return;
}
