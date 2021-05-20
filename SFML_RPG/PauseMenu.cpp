/**\PauseMenu.cpp*/
#include "stdafx.h"
#include "PauseMenu.h"


//Constructor
//! PauseMenu class constructor
	/*!
	\param vm a sf::VideoMode object - to get the screen properties
	\param font a sf::Font - the font for the menu
	*/
PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
		static_cast<float>(vm.width), 
		static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f(
		static_cast<float>(vm.width) / 4.f, 
		static_cast<float>(vm.height) - gui::p2pY(13.f, vm)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 100));
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	//Init text
	this->manuText.setFont(font);
	this->manuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->manuText.setCharacterSize(gui::calcCharSize(vm));
	this->manuText.setString("PAUSED");
	this->manuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->manuText.getGlobalBounds().width / 2.f, 
		this->container.getPosition().y + gui::p2pY(2.6f, vm)
	);
}

//Destructor
//! PauseMenu class destructor
	/*!
	*/
PauseMenu::~PauseMenu()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//! Function to return buttons
	/*!
	*/
std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}



//Functions
//! Function to check if button is pressed
	/*!
	\param key a std::string - the name of the button 
	*/
const bool PauseMenu::isButtonPressed(const std::string key) 
{
	//check if the button is pressed
	return this->buttons[key]->isPressed();
}

//! Function to return enemySpawner
	/*!
	\param key a std:string - the name of the button
	\param y a float - position of button in y-axis
	\param width a float - the width of the button
	\param height a float - the height of the button
	\param char_size an unsigned - size of button letters
	\param text a std::string - button text
	*/
void PauseMenu::addButton(
	const std::string key, 
	const float y,
	const float width,
	const float height,
	const unsigned char_Size, 
	const std::string text)
{

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_Size,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

//! Function to update menu
	/*!
	\param mousePosWindow a sf::vector2i - for where the button is clicked
	*/
void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

//! Function to render the pause menu
	/*!
	\param target a sf::RenderTarget - the menu target to be rendered
	*/
void PauseMenu::render(sf::RenderTarget & target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->manuText);
}
