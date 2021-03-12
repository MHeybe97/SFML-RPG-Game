/**\file EditorState*/
#pragma once
#include "State.h"
#include "Gui.h"
class EditorState : public State
{
private:
	//Variables
	sf::Font font; // button font

	//Button* gamestate_btn;
	std::map<std::string, gui::Button*> buttons; //button map

	//functions
	void initVariables();
	void initBackground();
	void initFonts(); //initialise fonts
	void initKeybinds(); //initialise keybinds
	void initButtons(); //initialise buttons

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states); //contructor
	virtual ~EditorState(); //destructor

	//functions


	void updateInput(const float& dt); //update input in menu state
	void updateButtons(); //update buttons in menu state
	void update(const float& dt); //update menu state
	void renderButtons(sf::RenderTarget& target); //render button to the screen
	void render(sf::RenderTarget* target = nullptr); //render menu state window
};

