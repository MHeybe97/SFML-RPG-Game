/**\file GameState.h*/
#pragma once

#include "State.h"
class GameState : public State
{
private:
	Player* player; //player

	//functions
	void initKeybinds(); //initialise keybinds
	void initTextures();
	void initPlayers();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states); //constructor
	virtual ~GameState(); //destructor

	//functions

	

	void updateInput(const float& dt); //update player input
	void update(const float& dt); //update gamestate
	void render(sf::RenderTarget* target = nullptr); //render to gamestate window
};

