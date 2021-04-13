/**\file GameState.cpp*/
#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width), 
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

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

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet1.png");
	this->tileMap->loadFromFile("text.slmp");
}

//Constructors / Destructors 
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds(); //initialise keybinds
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateView(const float & dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
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

void GameState::updateTileMap(const float & dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view); //update mouse position in gamestate
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt); //update input in game state

		this->updateTileMap(dt);

		this->player->update(dt); //update player
	}
	else //paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePausedMenuButtons();

	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

	this->player->render(this->renderTexture); //render the player on the window

	this->tileMap->renderDeffered(this->renderTexture);

	if (this->paused) //pause menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
