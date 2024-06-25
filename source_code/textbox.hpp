#include <SFML/Graphics.hpp>
#include <string>

class textbox
{
private:
    sf::RectangleShape thebox;
    sf::Text text;
    std::string searchoption = "";
    sf::Font font;
    bool active = false;
    std::string cursor = "_";
public:
    textbox(sf::RenderWindow &w);
    void checkstate();
    void flipstate();
    void reupdateword(sf::Event ev);
    void show(sf::RenderWindow &w);
};