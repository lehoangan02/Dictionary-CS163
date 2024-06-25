#include <SFML/Graphics.hpp>
#include <string>

class Button
{
    private:
    sf::Text buttonText;
    int characterSize;
    sf::Vector2u buttonPosition;
    sf::Sprite buttonSprite;
    sf::Texture textureDefault, textureHover, textureClick;
    bool haveText = false;
    bool hover = false;
    bool persistentClick = false;
    bool selected = false;
    public:
    Button(const sf::Texture& texture);
    Button(const sf::Texture& texture, const sf::Font& font, std::string textString, int characterSize);
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover);
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Texture& textureClick);
    Button(const sf::Texture& textureDefault, const sf::Texture& textureHover, const sf::Font& font,
    std::string textString, int characterSize);
    void setPosition(sf::Vector2u position);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window);
    bool isHovering(const sf::RenderWindow& window);
    void hoverSwitchTexture(const sf::RenderWindow& window);
    void select(bool mode);
    void click(sf::RenderWindow& window);
    private:
    virtual void centerText();
};