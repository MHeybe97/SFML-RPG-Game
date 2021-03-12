/**\file SettingsState.cpp*/
#include "SettingsState.h"



void SettingsState::initVariables()
{
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

void SettingsState::initButtons()
{
	

	//Quit Game Button
	this->buttons["EXIT_STATE"] = new Button(
		160.f, 520.f, 150.f, 50.f,
		&this->font, "Quit", 20,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states) 
{
	this->initVariables();
	this->initBackground();
	this->initFonts(); //initialise fonts
	this->initKeybinds(); //initialise keybinds
	this->initButtons(); //initialise buttons
}


SettingsState::~SettingsState()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Accessors

//Functions

void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateButtons()
{
	//updates all buttons in the state and handles their functionality
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}


	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void SettingsState::update(const float & dt)
{
	this->updateMousePositions(); //update mouse position in menue state
	this->updateInput(dt); //update input in menu state

	this->updateButtons(); //update buttons in menu state
}

void SettingsState::renderButtons(sf::RenderTarget & target)
{
	//this->gamestate_btn->render(target);
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget * target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	target->draw(this->background); //render background

	this->renderButtons(*target); //render buttons

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


