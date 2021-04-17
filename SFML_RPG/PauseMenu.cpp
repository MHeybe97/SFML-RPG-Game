/**\PauseMenu.cpp*/
#include "stdafx.h"
#include "PauseMenu.h"



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


PauseMenu::~PauseMenu()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}



//Functions
const bool PauseMenu::isButtonPressed(const std::string key) 
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
	const std::string key, 
	const float y,
	const float width,
	const float height,
	const unsigned char_Size, 
	const std::string text)
{
	/*float width = 250.f;
	float height = 50.f;*/
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_Size,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const   sf::Vector2i& mousePosWindow)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

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
