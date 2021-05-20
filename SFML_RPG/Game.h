/**\file Game.h*/
//#include "GameState.h"
#include "MainMenuState.h"
#pragma once

/*!\class Game
\brief the main class for the system
*/
class Game
{
private:

	//Variables
	GraphicsSettings gfxSettings; //!< graphics settings for the winfow
	StateData stateData; //!< all data for all states
	sf::RenderWindow *window; //!<application window
	sf::Event sfEvent; //!<sfml events
	
	

	sf::Clock dtClock; //!<clock for delta time
	float dt; //!<delta time

	std::stack<State*> states; //!<a stack for different game states

	std::map<std::string, int> supportedKeys; //!<map for supported keys

	float gridSize; //!< size of the tile grid

	//Initialization
	void initVariables(); //!< initialising private variables
	void initGraphicsSettings();
	void initWindow(); //!<initialising the window
	void initKeys(); //!<initialising the window
	void initStateData(); //!< initialising the stateData
	void initStates(); //!<initialising the window
	

public:
	//Contructor & Destructor
	Game();
	virtual ~Game();

	//functions

	//regular 
	void endAppliation(); //!< quitting the window application

	//update
	void updateDt(); //!< update delta time
	void updateSFMLEvents(); //!< update sfml events
	void update(); //!< update system

	//render
	void render(); //!< render window

	//run
	void run(); //!< update all functions
};

