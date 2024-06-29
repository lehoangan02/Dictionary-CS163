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
            if (event.key.code == sf::Keyboard::Backspace)
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
    if (!active)
    {
        if (textStream.str() == "")
        {
            displayText.setFillColor(sf::Color(138, 138, 141));
            textStream.str("");
            textStream << guideString;
        }
    }
    else
    {
        displayText.setFillColor(sf::Color(0, 0, 0));
    }
}
void  textbox::select() 
{
    if (active) return;
    active = true;
    if (!full) // insert cursor
    {
        if (textStream.str() == guideString)
        {

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
            for (int i = 0; i < temp.length() - 1; ++i)
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
    for (int i = 0; i < temp.length() - 1; ++i)
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
        for (int i = 0; i < temp.length() - 2; ++i)
        {
            textStream << temp[i];
        }
    }
    else
    {
        for (int i = 0; i < temp.length() - 1; ++i)
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
std::string textbox::getString()
{
    if (textStream.str() == guideString)
    {
        return "";
    }
    deselect();
    return textStream.str();
}
void textbox::clear()
{
    textStream.str("");
    deselect();
    handleColor();
    textStream.str(guideString);
    displayText.setString(textStream.str());
    return;
}