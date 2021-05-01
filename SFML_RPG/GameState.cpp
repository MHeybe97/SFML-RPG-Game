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
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}

	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_ENEMY_TEXTURE!";
	}

}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(71.6f, vm), gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(220, 220, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER! PRESS ESC & QUIT");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f
	);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);

}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("text.slmp");
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
	this->initShaders();

	/*this->activeEnemies.push_back(new RatEnemy(200.f, 100.f, this->textures["RAT1_SHEET"]));
	this->activeEnemies.push_back(new RatEnemy(500.f, 100.f, this->textures["RAT1_SHEET"]));*/

	this->initPlayers();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();

	
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

void GameState::updateView(const float & dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 2.f), 
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 2.f)
	);

	if (this->tileMap->getMaxSize().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSize().x)
		{
			this->view.setCenter(this->tileMap->getMaxSize().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSize().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSize().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSize().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
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
	{
		this->player->move(0.f, -1.f, dt);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) //move pplayer down
	{
		this->player->move(0.f, 1.f, dt);
		/*if (this->getKeytime())
			this->player->loseHP(1);*/
	}
	
}

void GameState::updatePlayerGUI(const float & dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float & dt)
{
	this->tileMap->updateWorldBoundCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
	
	for (auto *i : this->activeEnemies)
	{
		this->tileMap->updateWorldBoundCollision(i, dt);
		this->tileMap->updateTileCollision(i, dt);
	}
}

void GameState::updatePlayer(const float & dt)
{
}

void GameState::updateEnemies(const float & dt)
{
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view); //update mouse position in gamestate
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused && !this->player->isAlive()) //unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt); //update input in game state

		this->updateTileMap(dt);

		this->player->update(dt, this->mousePosView); //update player

		this->playerGUI->update(dt);

		for (auto *i : this->activeEnemies)
		{
			i->update(dt, this->mousePosView);
		}
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
	this->tileMap->render(
		this->renderTexture, 
		this->viewGridPosition, 
		&this->core_shader,
		this->player->getCenter(),
		 false);

	for (auto *i : this->activeEnemies)
	{
		i->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}

	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false); //render the player on the window

	this->tileMap->renderDeffered(this->renderTexture, &this->core_shader, this->player->getCenter());

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	//Game Over Screen
	if (this->player->isAlive())
		this->renderTexture.draw(this->gameOverText);

	if (this->paused) //pause menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	

	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
