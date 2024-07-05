#include "animation.hpp"
Animation::Animation(const sf::Texture& texture, sf::Vector2u imageCount, float switchTime)
{
    this -> imageCount = imageCount;
    this -> switchTime = switchTime;
    currentRect.left = 0;
    currentRect.top = 0;
    currentRect.width = texture.getSize().x / imageCount.x;
    currentRect.height = texture.getSize().y / imageCount.y;
    animationSprite.setTexture(texture);
}

/// @brief update the currectRect of the animation
/// @param deltaTime 
void Animation::updateAnimation(float deltaTime)
{
    totalTime += deltaTime;
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        ++currentImage.x;
        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }
    currentRect.left = currentImage.x * currentRect.width;
    currentRect.top = 0;
    animationSprite.setTextureRect(currentRect);
}

/// @brief draw the sprite with currentRect as texture
/// @param window 
void Animation::draw(sf::RenderWindow& window)
{
    window.draw(animationSprite);
}

void Animation::setPosition(sf::Vector2u position)
{
    animationSprite.setPosition((float)position.x, (float)position.y);
}

AnimationVertical::AnimationVertical(const sf::Texture& texture, sf::Vector2u imageCount, float switchTime) :
    Animation(texture, imageCount, switchTime)
    {

    }
void AnimationVertical::updateAnimation(float deltaTime)
{
    totalTime += deltaTime;
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        ++currentImage.y;
        if (currentImage.y >= imageCount.y)
        {
            currentImage.y = 0;
        }
    }
    currentRect.top = currentImage.y * currentRect.height;
    currentRect.left = 0;
    animationSprite.setTextureRect(currentRect);
}

void AnimationVertical::resetAnimation()
{
    currentImage.y = 0;
    currentRect.top = 0;
}