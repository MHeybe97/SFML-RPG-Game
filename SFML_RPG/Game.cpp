/**\file Game.cpp*/
#include "stdafx.h"
#include "Game.h"

//Static functions

void Game::initVariables()
{
	this->window = NULL;
	
	this->dt = 0.f;

	this->gridSize = 64.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
	
	
}

//Initializer functions
void Game::initWindow()
{
	//create a SFML window using options from a window.ini file

	

	if (this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title, 
			sf::Style::Fullscreen, 
			this->gfxSettings.contextSettings); //create new window with information read from window.ini
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title, 
			sf::Style::Titlebar | sf::Style::Close, 
			this->gfxSettings.contextSettings);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit); //set the framelimit
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync); //set vsync to false disabeling it
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini"); //read from supported_keys.ini file

	if (ifs.is_open()) //check if file is open
	{
		std::string key = " "; //what the supported key is
		int key_value = 0; //the value of the key

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();


	//for debugging remove later
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n"; //print supported keys to screen
	}
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData)); //initialise mainmenu state
	//this->states.push(new GameState(this->window, &this->supportedKeys));
}


//constructor & Destructor
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow(); //initialse the window
	this->initKeys(); //initialise the keys
	this->initStateData();
	this->initStates(); //initialise the states
	
}


Game::~Game()
{
	delete this->window; //delete the window

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//functions
void Game::endAppliation()
{
	std::cout << "Ending Application" << "\n"; //display when application is quit
}


void Game::updateDt()
{
	
	this->dt = this->dtClock.restart().asSeconds(); //updates dt variable with the time it takes to render one frame

}

void Game::updateSFMLEvents()
{	
	//close the window 
		while (this->window->pollEvent(this->sfEvent))
		{
			if (this->sfEvent.type == sf::Event::Closed)
				this->window->close();
		}	
}

void Game::update()
{
	this->updateSFMLEvents(); //update sfml events

	if (!this->states.empty()) //if state is not empty
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt); //update the state
			{
				if (this->states.top()->getQuit()) //quit the state
				{
					this->states.top()->endState(); //the state at the top
					delete this->states.top(); //delete state at the top of the stack
					this->states.pop(); //pop the state
				}
			}
		}
	}
	//if states empty then Application end
	else
	{
		this->endAppliation(); //end the application
		this->window->close(); //close the window
	}
}

void Game::render()
{
	this->window->clear(); //clear the window

	//Render items
	if (!this->states.empty()) //if state is not empty
		this->states.top()->render(); // then render the state

	this->window->display(); //display window
}

void Game::run()
{
	while (this->window->isOpen()) //while the window is open
	{
		this->updateDt(); //update Dt
		this->render(); //render window
		this->update(); //update window
	}
}


