/**\file Game.h*/
//#include "GameState.h"
#include "MainMenuState.h"
#pragma once

class Game
{
private:


	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window; //application window
	sf::Event sfEvent; //sfml events
	
	

	sf::Clock dtClock; //clock for delta time
	float dt; // delta time

	std::stack<State*> states; //a stack for different game states

	std::map<std::string, int> supportedKeys; //map for supported keys

	float gridSize;

	//Initialization
	void initVariables(); 
	void initGraphicsSettings();
	void initWindow(); //initialising the window
	void initKeys(); //initialising the window
	void initStateData();
	void initStates(); //initialising the window
	

public:
	//Contructor & Destructor
	Game();
	virtual ~Game();

	//functions

	//regular 
	void endAppliation();

	//update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//render
	void render();

	//run
	void run();
};

