/**\PauseMenu.h*/
#pragma once

//#include <vector>
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <fstream>
//#include <sstream>
//#include <stack>
//#include <map>

#include "Gui.h"

//#include "SFML\System.hpp"
//#include "SFML\Window.hpp"
//#include "SFML\Graphics.hpp"
//#include "SFML\Audio.hpp"
//#include "SFML\Network.hpp"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text manuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	//Private functions
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessors
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const  sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);

};

