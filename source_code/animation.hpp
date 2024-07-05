#include <SFML/Graphics.hpp>

class Animation
{
    public:
    Animation(const sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
    sf::Sprite animationSprite;
    sf::Vector2u imageCount;
    protected:
    sf::IntRect currentRect;
    sf::Vector2u currentImage = sf::Vector2u(0, 0);
    float totalTime = 0;
    float switchTime = 0;
    public:
    virtual void updateAnimation(float deltatTime);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2u postion);
};
class AnimationVertical : public Animation
{
    public:
    AnimationVertical(const sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
    void updateAnimation(float deltaTime) override;
    void resetAnimation();
};