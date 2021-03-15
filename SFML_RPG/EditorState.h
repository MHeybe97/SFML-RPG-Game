/**\file EditorState*/
#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState : public State
{
private:
	//Variables
	sf::Font font; // button font
	PauseMenu* pmenu;
	//Button* gamestate_btn;
	std::map<std::string, gui::Button*> buttons; //button map
	TileMap* tileMap;
	sf::RectangleShape selectorRect;

	//functions
	void initVariables();
	void initBackground();
	void initFonts(); //initialise fonts
	void initKeybinds(); //initialise keybinds
	void initPauseMenu();
	void initButtons(); //initialise buttons
	void initGui();
	void initTileMap();

public:
	EditorState(StateData* state_data); //contructor
	virtual ~EditorState(); //destructor

	//functions


	void updateInput(const float& dt); //update input in editor state

	void updateButtons(); //update buttons in editor state
	void updateEditorInput(const float& dt);
	void updateGui();
	void updatePausedMenuButtons();
	void update(const float& dt); //update editor state
	void renderButtons(sf::RenderTarget& target); //render button to the screen
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr); //render editor state window
};

