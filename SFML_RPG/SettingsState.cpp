/**\file SettingsState.cpp*/
#include "stdafx.h"
#include "SettingsState.h"



void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png"))
	{
		throw"ERROR::Main_Menu_State::FAILED_TO_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf")) //load Kurri Island font from Fonts file
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //throw error if file was not found
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini"); //read from mainmenustate_keybinds.ini

	if (ifs.is_open()) //if file is open
	{
		std::string key = " "; //string for what key does e.g. CLOSE
		std::string key2 = " "; //string for name of key e.g. Escape

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2); //keybinds is equal to supportedkeys
		}
	}

	ifs.close(); //close file
}

void SettingsState::initGui()
{
	

	//Quit Game Button
	this->buttons["BACK"] = new gui::Button(
		560.f, 520.f, 150.f, 50.f,
		&this->font, "Back", 20,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		860.f, 520.f, 150.f, 50.f,
		&this->font, "Apply", 20,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(800, 250, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionText.setFont(this->font);
	this->optionText.setPosition(sf::Vector2f(100.f, 270.f));
	this->optionText.setCharacterSize(30);
	this->optionText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionText.setString(
		"Resolution \n\nFullscreen \n\nVsync \nAntialiasing \n\n "
	);
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states) 
{
	this->initVariables();
	this->initBackground();
	this->initFonts(); //initialise fonts
	this->initKeybinds(); //initialise keybinds
	this->initGui(); //initialise buttons
	this->initText();
}


SettingsState::~SettingsState()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	
}

//Accessors

//Functions

void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float & dt)
{
	//updates all gui elements in the state and handles their functionality
	//Buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Button functionality
	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		//Test Remove later
		this->window->create(this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()], "test", sf::Style::Default);
			
	}

	// Dropdown lists
	for (auto &it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}
	//Dropdown lists functionality

	
}

void SettingsState::update(const float & dt)
{
	this->updateMousePositions(); //update mouse position in menue state
	this->updateInput(dt); //update input in menu state

	this->updateGui(dt); //update buttons in menu state

	
}

void SettingsState::renderGui(sf::RenderTarget & target)
{
	//this->gamestate_btn->render(target);
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget * target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	target->draw(this->background); //render background

	this->renderGui(*target); //render buttons
	
	target->draw(this->optionText);

	//MousePosition For Debugging
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}


