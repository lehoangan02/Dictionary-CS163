#include "window.h"

window::window()
{
	w = new sf::RenderWindow(sf::VideoMode(960, 720), "dictionary in a nutshell", sf::Style::Default);
}

void window::operate()
{
	while (this->w->isOpen())
	{
		while (this->w->pollEvent(ev))
		{
			switch (ev.type())
			{
			case sf::Event::Closed:
			{
				this->w->close();
				break;
			}
			}
		}
		w.clear();
		w.display();
	}
}