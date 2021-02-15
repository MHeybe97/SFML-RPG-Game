/**\file Game.h*/
//#include "GameState.h"
#include "MainMenuState.h"
#pragma once

class Game
{
private:
	//Variables
	sf::RenderWindow *window; //application window
	sf::Event sfEvent; //sfml events
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock; //clock for delta time
	float dt; // delta time

	std::stack<State*> states; //a stack for different game states

	std::map<std::string, int> supportedKeys; //map for supported keys

	//Initialization
	void initVariables(); 
	void initWindow(); //initialising the window
	void initKeys(); //initialising the window
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

