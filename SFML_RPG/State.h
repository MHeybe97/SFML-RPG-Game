/**\file State.h*/
#pragma once
#include "Player.h"

class State
{
private:

protected:
	std::stack<State*>* states; //stack for the states
	sf::RenderWindow* window; //application window
	std::map<std::string, int>* supportedKeys; //map for the supported keys
	std::map<std::string, int> keybinds; // keybinds
	bool quit; // to check if we quit application

	sf::Vector2i mousePosScreen; //mouse position on the screen
	sf::Vector2i mousePosWindow; //mouse position on the window
	sf::Vector2f mousePosView; //mouse position on the view

	//Resources
	std::map<sf::String, sf::Texture> textures;

	//functions
	virtual void initKeybinds() = 0; //initialise keybinds

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states); //contructor
	virtual ~State(); //dstructor

	const bool& getQuit() const; //quitting the app

	//virtual void endstateUpdate() = 0; //check if the application has been quit

	virtual void endState(); // end the state
	virtual void updateMousePositions(); //update the mouse position
	virtual void updateInput(const float& dt) = 0; //update the input
	virtual void update(const float& dt) = 0; //update window
	virtual void render(sf::RenderTarget* target = nullptr) = 0; //rendering to the window
};

