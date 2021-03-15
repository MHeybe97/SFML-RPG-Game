/**\file SettingsState.h*/
#pragma once
#include "State.h"
#include "Gui.h"
#include "GraphicsSettings.h"
class SettingsState : public State
{
private:
	//Variables
	GraphicsSettings& gfxSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background; //window background
	sf::Font font; // button font

	//Button* gamestate_btn;
	std::map<std::string, gui::Button*> buttons; //button map
	std::map<std::string, gui::DropDownList*> dropDownLists;
	
	sf::Text optionText;
	std::vector<sf::VideoMode> modes;

	//functions
	void initVariables();
	void initBackground();
	void initFonts(); //initialise fonts
	void initKeybinds(); //initialise keybinds
	void initGui(); //initialise buttons
	void initText();

public:
	SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	
	//Accessors

    //Functions
	void updateInput(const float& dt); //update input in menu state
	void updateGui(const float& dt); //update buttons in menu state
	void update(const float& dt); //update menu state
	void renderGui(sf::RenderTarget& target); //render button to the screen
	void render(sf::RenderTarget* target = nullptr); //render menu state window
};

