#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "application.h"
#include "button.h"

int main()
{
	//Setup window
	sf::RenderWindow window(sf::VideoMode(650, 500), "TodoApp", sf::Style::Close);
	//Setup font
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	//Create app
	Application app;
	app.load();
	//Add title
	sf::Text title;
	title.setString("TodoApp");
	title.setPosition(245, 50);
	title.setCharacterSize(40);
	title.setFillColor(sf::Color::Black);
	title.setFont(font);
	//Add text
	sf::Text txt;
	txt.setString("Add task:");
	txt.setPosition(115, 100);
	txt.setCharacterSize(20);
	txt.setFillColor(sf::Color::Black);
	txt.setFont(font);
	//Adding cards
	Button add(10, 460, 90, 30, "Add card");
	bool addingCard = false;
	sf::Text cardText;
	cardText.setPosition(215, 100);
	cardText.setCharacterSize(20);
	cardText.setFillColor(sf::Color::Black);
	cardText.setFont(font);
	std::string input = "";
	//Reset scrolling
	Button reset(525, 460, 115, 30, "Back to top");
	//Loop
	while (window.isOpen())
	{
		//Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				app.move(event.mouseWheel.delta * 3);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (add.hovering(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					addingCard = true;
				}
				else if (reset.hovering(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					app.resetScrolling();
				}
				else
				{
					for (int i = 0; i < app.num; i++)
					{
						if (sf::Mouse::getPosition(window).y > app.cards[i]->y && sf::Mouse::getPosition(window).y < app.cards[i]->y + 40)
						{
							app.removeCard(i);
							app.save();
						}
					}
				}
			}
			if (addingCard == true)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (std::isprint(event.text.unicode))
					{
						input += event.text.unicode;
						cardText.setString(input);
					}
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::BackSpace)
					{
						if (!input.empty())
						{
							input = input.substr(0, input.size() - 1);
							cardText.setString(input);
						}
					}
					if (event.key.code == sf::Keyboard::Return)
					{
						app.addCard(input);
						input = "";
						cardText.setString(input);
						addingCard = false;
						app.save();
					}
				}
			}
		}
		//Rendering
		window.clear(sf::Color::White);
		app.render(window);
		window.draw(title);
		window.draw(add.rect);
		window.draw(add.text);
		window.draw(reset.rect);
		window.draw(reset.text);
		if (addingCard == true)
		{
			window.draw(cardText);
			window.draw(txt);
		}
		window.display();
	}
	return 0;
}