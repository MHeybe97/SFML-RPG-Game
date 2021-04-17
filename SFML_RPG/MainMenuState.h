/**\file MainMenuState.h*/
#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class MainMenuState : public State
{
private:
	//Variables
	
	sf::Texture backgroundTexture;
	sf::RectangleShape background; //window background
	sf::Font font; // button font

	//Button* gamestate_btn;
	std::map<std::string, gui::Button*> buttons; //button map

	//functions
	void initVariables();
	void initFonts(); //initialise fonts
	void initKeybinds(); //initialise keybinds
	void initGui(); //initialise buttons
	void resetGui();

public:
	MainMenuState(StateData* state_data); //contructor
	virtual ~MainMenuState(); //destructor

	//functions


	void updateInput(const float& dt); //update input in menu state
	void updateButtons(); //update buttons in menu state
	void update(const float& dt); //update menu state
	void renderButtons(sf::RenderTarget& target); //render button to the screen
	void render(sf::RenderTarget* target = nullptr); //render menu state window
};


