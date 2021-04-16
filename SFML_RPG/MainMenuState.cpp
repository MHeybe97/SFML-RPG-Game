/**\file MainMenuState.cpp*/
#include "stdafx.h"
#include "MainMenuState.h"

//initializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
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

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf")) //load Kurri Island font from Fonts file
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //throw error if file was not found
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//New Game Button
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(11.7f, vm), gui::p2pY(28.6f, vm),
		gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "New Game", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

	//Settings Button
	this->buttons["SETTING_STATE"] = new gui::Button(
		gui::p2pX(11.7f, vm), gui::p2pY(41.6f, vm), 
		gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//Editor Button
	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(11.7f, vm), gui::p2pY(54.6f, vm),
		gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//Quit Game Button
	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(11.7f, vm), gui::p2pY(67.7f, vm),
		gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts(); //initialise fonts
	this->initKeybinds(); //initialise keybinds
	this->initButtons(); //initialise buttons
}

MainMenuState::~MainMenuState()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float & dt)
{
	
}

void MainMenuState::updateButtons()
{
	//updates all buttons in the state and handles their functionality
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTING_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions(); //update mouse position in menue state
	this->updateInput(dt); //update input in menu state

	this->updateButtons(); //update buttons in menu state

	
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
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
