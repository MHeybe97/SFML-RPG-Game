/**\file GameState.cpp*/
#include "stdafx.h"
#include "GameState.h"

//Initializer functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini"); //read from filie gamestate_keybinds

	if (ifs.is_open()) //check if file is open
	{
		std::string key = " "; //string for what key does e.g. CLOSE
		std::string key2 = " "; //string for name of key e.g. Escape

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2); //keybinds is equal to the supported keys
		}
	}

	ifs.close(); //close file

}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf")) //load Kurri Island font from Fonts file
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //throw error if file was not found
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 550.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

//Constructors / Destructors 
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds(); //initialise keybinds
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pausedState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float & dt)
{
	//this->checkForQuit(); //check if esc has been pressed

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) //move player left
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) //move player right
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) //move player up
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) //move pplayer down
		this->player->move(0.f, 1.f, dt);

	
}

void GameState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(); //update mouse position in gamestate
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //unpaused update
	{
		
		this->updatePlayerInput(dt); //update input in game state

		this->player->update(dt); //update player
	}
	else //paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePausedMenuButtons();

	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	//this->map.render(*target);

	this->player->render(*target); //render the player on the window

	if (this->paused) //pause menu render
	{
		this->pmenu->render(*target);
	}
}
