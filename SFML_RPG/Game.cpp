/**\file Game.cpp*/
#include "Game.h"

//Static functions

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

//Initializer functions
void Game::initWindow()
{
	//create a SFML window using options from a window.ini file

	std::ifstream ifs("Config/window.ini"); //read from window.ini file in the config folder
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None"; //set the title as None
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode(); //set window size
	bool fullscreen = false;
	unsigned framerate_limit = 120; //set framerete to 120
	bool vertical_sync_enabled = false; //disable vsync
	unsigned antialiasing_level = 0;

	//check if file is open
	if (ifs.is_open())
	{
		std::getline(ifs, title); //get the window name title from window.ini
		ifs >> window_bounds.width >> window_bounds.height; //get the window height and width from window.ini
		ifs >> fullscreen;
		ifs >> framerate_limit; //get the framerate limit from ini
		ifs >> vertical_sync_enabled; //check whether vsync is enabled 
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings); //create new window with information read from window.ini
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(120); //set the framelimit
	this->window->setVerticalSyncEnabled(false); //set vsync to false disabeling it
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

	/*this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"] = sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S;*/

	//for debugging remove later
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n"; //print supported keys to screen
	}
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states)); //initialise mainmenu state
	//this->states.push(new GameState(this->window, &this->supportedKeys));
}


//constructor & Destructor
Game::Game()
{
	this->initWindow(); //initialse the window
	this->initKeys(); //initialise the keys
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


