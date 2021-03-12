/**\file SettingsState.h*/
#pragma once
#include "State.h"
#include "Button.h"
class SettingsState : public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background; //window background
	sf::Font font; // button font

	//Button* gamestate_btn;
	std::map<std::string, Button*> buttons; //button map

	//functions
	void initVariables();
	void initBackground();
	void initFonts(); //initialise fonts
	void initKeybinds(); //initialise keybinds
	void initButtons(); //initialise buttons

public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	
	//Accessors

    //Functions
	void updateInput(const float& dt); //update input in menu state
	void updateButtons(); //update buttons in menu state
	void update(const float& dt); //update menu state
	void renderButtons(sf::RenderTarget& target); //render button to the screen
	void render(sf::RenderTarget* target = nullptr); //render menu state window
};
