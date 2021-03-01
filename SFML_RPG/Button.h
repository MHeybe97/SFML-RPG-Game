/**\file Button.h*/
#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE}; //enum for button states
class Button
{
private:
	short unsigned buttonState; //button states

	sf::RectangleShape shape; //button shape
	sf::Font* font; //button font
	sf::Text text; //button text

	sf::Color idleColor; // button idle-color
	sf::Color hoverColor; //button hover-color
	sf::Color activeColor; //button active-color

public:
	Button(float x, float y, float width, float height, 
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor); //constructor
	~Button(); //destructor

	//Accessors
	const bool isPressed() const; //check if button is pressed

	//functions
	void update(const sf::Vector2f mousePos); //update buttons
	void render(sf::RenderTarget* target); //render buttons
};
