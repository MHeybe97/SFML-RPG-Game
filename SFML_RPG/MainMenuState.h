/**\file MainMenuState.h*/
#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
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
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states); //contructor
	virtual ~MainMenuState(); //destructor

	//functions


	void updateInput(const float& dt); //update input in menu state
	void updateButtons(); //update buttons in menu state
	void update(const float& dt); //update menu state
	void renderButtons(sf::RenderTarget* target = nullptr); //render button to the screen
	void render(sf::RenderTarget* target = nullptr); //render menu state window
};

