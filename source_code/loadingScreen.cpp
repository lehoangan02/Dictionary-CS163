#include "loadingScreen.hpp"

loadingScreen::loadingScreen() :
    loadingTexture(loadTexture("assets/images/loading.png")),
    loadingAnimation(loadingTexture, sf::Vector2u(1, 11), 0.1)
{
    loadingAnimation.setPosition(sf::Vector2u(230, 0));
    magarine.loadFromFile("assets/font/Margarine-Regular.ttf");
    loadingText.setFont(magarine);
    loadingText.setCharacterSize(96);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setString("loading");
    loadingText.setOutlineThickness(3);
    loadingText.setOutlineColor(sf::Color(94, 94, 94));
    loadingText.setPosition((int)((960 - loadingText.getGlobalBounds().width) / 2 - 5), 500.0f);
}
sf::Texture loadTexture(const std::string& filepath)
    {
        sf::Texture texture;
        texture.loadFromFile(filepath);
        texture.setSmooth(false);
        return texture;
    }
void loadingScreen::operate(sf::RenderWindow& window, std::atomic<bool>& controlLoaded)
{
    while (window.isOpen() && controlLoaded.load() == false)
    {
        // printf("%d\n", controlLoaded.load() ? 1 : 0);
        deltaTime = clock.restart().asSeconds();
        loadingAnimation.updateAnimation(deltaTime);
        window.clear(sf::Color(61, 109, 178));
        loadingAnimation.draw(window);
        window.draw(loadingText);
        window.display();
    }
}
void loadingWrapper(sf::RenderWindow& window, std::atomic<bool>& control)
{
    loadingScreen thisLoadingScreen;
    thisLoadingScreen.operate(window, control);
}