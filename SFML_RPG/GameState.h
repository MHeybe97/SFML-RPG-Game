/**\file GameState.h*/
#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GraphicsSettings.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Enemy.h"
#include "EnemiesInclude.h"
#include "EnemySpawner.h"
#include "EnemySystem.h"
#include "TextTagSystem.h"


class GameState : public State
{
private:
	sf::View view;
	sf::Vector2i viewGridPosition;
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

	//Enemy
	std::vector<Enemy*> activeEnemies;
	EnemySystem *enemySystem;

	//Systems
	TextTagSystem* tts;
	

	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds(); //initialise keybinds
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initEnemySystem();
	void initTileMap();
	void initSystems();
	void initGameOverScreen();

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
	void updatePlayer(const float& dt);
	void updateCombatAndEnemies(const float& dt);
	void updateCombat(Enemy* enemy, const int index, const float& dt);
	void update(const float& dt); //update gamestate
	void render(sf::RenderTarget* target = nullptr); //render to gamestate window
};

