/**\file EditorState*/
#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GraphicsSettings.h"
#include "EditorMode.h"
#include "DefaultEditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class EditorStateData;
class DefaultEditorMode;

enum EditorModes {DEFAULT_MODE = 0, ENEMY_MODE};



class EditorState : public State
{
private:
	//Variables
	EditorStateData editorStateData;

	sf::View view;
	sf::Font font; // button font
	PauseMenu* pmenu;

	//Button* gamestate_btn;
	std::map<std::string, gui::Button*> buttons; //button map

	TileMap* tileMap;

	float cameraSpeed;
	/*sf::Text cursorText;
	sf::RectangleShape sidebar;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;
	float cameraSpeed;
	bool collision;
	short type;
	int layer;
	bool tileAddLock;*/

	std::vector<EditorMode*> modes;

	//functions
	void initVariables();
	void initEditorStateData();
	void initView();
	void initFonts(); //initialise fonts
	void initText();
	void initKeybinds(); //initialise keybinds
	void initPauseMenu();
	void initButtons(); //initialise buttons
	void initGui();
	void initTileMap();
	void initModes();

public:
	EditorState(StateData* state_data); //contructor
	virtual ~EditorState(); //destructor

	//functions


	void updateInput(const float& dt); //update input in editor state

	void updateButtons(); //update buttons in editor state
	void updateEditorInput(const float& dt);
	void updateGui(const float& dt);
	void updatePausedMenuButtons();
	void updateModes(const float&  dt);
	void update(const float& dt); //update editor state
	void renderButtons(sf::RenderTarget& target); //render button to the screen
	void renderGui(sf::RenderTarget& target);
	void renderModes(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr); //render editor state window
};

