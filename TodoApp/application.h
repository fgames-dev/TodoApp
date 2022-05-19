#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "button.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
public:
	std::vector<Button*> cards;
	int num, y, scrolled;
	Application();
	void addCard(std::string);
	void removeCard(int);
	void render(sf::RenderWindow& window);
	void move(int);
	void resetScrolling();
	void save();
	void load();
};

Application::Application()
{
	num = 0;
	y = 140;
	scrolled = 0;
	std::cout << "App initiated!" << std::endl;
}

void Application::addCard(std::string txt)
{
	cards.push_back(new Button(75, y, 500, 40, txt));
	num++;
	y += 45;
}

void Application::removeCard(int index)
{
	if (num > 1)
	{
		cards[index]->text.setString(cards[num - 1]->text.getString());
		cards.erase(cards.begin() + num - 1);
		num--;
	}
	else
	{
		cards.erase(cards.begin() + num - 1);
		num--;
	}
	y -= 45;
}

void Application::render(sf::RenderWindow& window)
{
	for (int i = 0; i < num; i++)
	{
		window.draw(cards[i]->rect);
		window.draw(cards[i]->text);
	}
}

void Application::move(int amount)
{
	for (int i = 0; i < num; i++)
	{
		cards[i]->y += amount;
		cards[i]->rect.setPosition(cards[i]->x, cards[i]->y);
		cards[i]->text.setPosition(cards[i]->x + 5, cards[i]->y + 3);
	}
	y += amount;
	scrolled += amount;
}

void Application::resetScrolling()
{
	move(-scrolled);
}

void Application::save()
{
	std::ofstream saveFile("tasks.txt");
	if (saveFile.is_open())
	{
		for (int i = 0; i < num; i++)
		{
			saveFile << cards[i]->text.getString().toAnsiString() + "\n";
		}
		saveFile.close();
	}
}

void Application::load()
{
	std::ifstream saveFile("tasks.txt");
	std::string line;
	if (saveFile.is_open())
	{
		while(getline(saveFile, line))
		{
			addCard(line);
		}
		saveFile.close();
	}
}

#endif