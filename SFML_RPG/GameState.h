/**\file GameState.h*/
#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GraphicsSettings.h"
#include "PlayerGUI.h"

class PausMenu;
class Player;
class PlayerGUI;
class TileMap;

class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState : public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;
	sf::Shader core_shader;
	sf::Text gameOverText;

	//Player
	Player* player; //player
	PlayerGUI* playerGUI;
	sf::Texture texture;

	//TileMap
	TileMap* tileMap;


	//functions
	void initDeferredRender();
	void initView();
	void initKeybinds(); //initialise keybinds
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initTileMap();

public:
	GameState(StateData* state_data); //constructor
	virtual ~GameState(); //destructor

	//functions

	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt); //update player input
	void updatePlayerGUI(const float& dt);
	void updatePausedMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt); //update gamestate
	void render(sf::RenderTarget* target = nullptr); //render to gamestate window
};

