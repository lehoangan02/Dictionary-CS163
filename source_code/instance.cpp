#include<SFML/Graphics.hpp>
#include "instance.h"

instance::instance() : windowInstance(sf::VideoMode(960, 720), "Dictionary, in a nutshell", sf::Style::Close)
{

}
void instance::operate()
{
	while (windowInstance.isOpen())
	{
		sf::Event event;
		while (windowInstance.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				windowInstance.close();
				break;
			}
			default:
			break;
			}
		}
		windowInstance.clear();
		windowInstance.display();
	}
}