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

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState; //button states
		short unsigned id;

		sf::RectangleShape shape; //button shape
		sf::Font* font; //button font
		sf::Text text; //button text

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor; // button idle-color
		sf::Color hoverColor; //button hover-color
		sf::Color activeColor; //button active-color

		sf::Color outlineidleColor; // button idle-color
		sf::Color outlinehoverColor; //button hover-color
		sf::Color outlineactiveColor; //button active-color

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
			sf::Color outline_idle_Color = sf::Color::Transparent, sf::Color outline_hover_Color = sf::Color::Transparent, sf::Color outline_active_Color = sf::Color::Transparent,
			short unsigned id = 0); //constructor
		~Button(); //destructor

		//Accessors
		const bool isPressed() const; //check if button is pressed
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned Id);

		//functions
		void update(const sf::Vector2f& mousePos); //update buttons
		void render(sf::RenderTarget& target); //render buttons
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;
		//functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt); //update buttons
		void render(sf::RenderTarget& target); //render buttons
	};
}
