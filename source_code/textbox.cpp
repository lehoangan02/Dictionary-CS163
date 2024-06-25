#include "textbox.hpp"

textbox::textbox(sf::RenderWindow& w)
{
    font.loadFromFile("assets/font/PlayfairDisplay-VariableFont_wght.ttf");
    text.setFont(font);
    thebox.setSize(sf::Vector2f(670, 65));
    //position: 145, 40
    text.setCharacterSize(24);
    thebox.setPosition(145, 40);
    text.setPosition(165, 60);
}

void textbox::show(sf::RenderWindow &w)
{
    w.draw(thebox);
    w.draw(text);
}

//either shows the cursor at the end of the textbox text if it is active, and don't if it isn't
void textbox::checkstate()
{
    if (!active)
    {
        if (searchoption.length() != 0) text.setString(searchoption);
        else text.setString(std::string("Type here"));
    }
    else text.setString(searchoption + cursor);
}

//click out of the textbox and this function triggers
void textbox::flipstate()
{
    active = active ^ false;
    checkstate();
}

//when pollevent on the instance fetches a TextEntered as active is true, this function is triggered
void textbox::reupdateword(sf::Event ev)
{
    if (ev.text.unicode < 128 && active)
    {
        char c = static_cast<char>(ev.text.unicode);
        if (c >= 32) searchoption += c;
        else if (c == 8) searchoption = searchoption.substr(0, searchoption.length() - 1);
        else if (c == 13) active = false;
        checkstate();
    }
}