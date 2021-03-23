/**\file EditorState*/
#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GraphicsSettings.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState : public State
{
private:
	//Variables
	sf::View view;
	float cameraSpeed;

	sf::Font font; // button font
	sf::Text cursorText;
	PauseMenu* pmenu;

	//Button* gamestate_btn;
	std::map<std::string, gui::Button*> buttons; //button map

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	bool collision;
	short type;

	//functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts(); //initialise fonts
	void initText();
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
	void updateGui(const float& dt);
	void updatePausedMenuButtons();
	void update(const float& dt); //update editor state
	void renderButtons(sf::RenderTarget& target); //render button to the screen
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr); //render editor state window
};

