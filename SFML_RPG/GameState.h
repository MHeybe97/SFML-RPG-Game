/**\file GameState.h*/
#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState : public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;

	Player* player; //player

	TileMap* tileMap;
	//functions
	void initKeybinds(); //initialise keybinds
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	GameState(StateData* state_data); //constructor
	virtual ~GameState(); //destructor

	//functions

	
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt); //update player input
	void updatePausedMenuButtons();
	void update(const float& dt); //update gamestate
	void render(sf::RenderTarget* target = nullptr); //render to gamestate window
};

