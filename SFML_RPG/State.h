/**\file State.h*/
#pragma once
#include "Player.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	//variables
	float gridSize;
	sf::RenderWindow* window; 
	GraphicsSettings* gfxSettings;
	std::map < std::string, int > * supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states; //stack for the states
	sf::RenderWindow* window; //application window
	std::map<std::string, int>* supportedKeys; //map for the supported keys
	std::map<std::string, int> keybinds; // keybinds
	bool quit; // to check if we quit application
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen; //mouse position on the screen
	sf::Vector2i mousePosWindow; //mouse position on the window
	sf::Vector2f mousePosView; //mouse position on the view
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<sf::String, sf::Texture> textures;

	//functions
	virtual void initKeybinds() = 0; //initialise keybinds

public:
	State(StateData* state_data); //contructor
	virtual ~State(); //dstructor

	//Accessors
	const bool& getQuit() const; //quitting the app
	const bool getKeytime();

	//Functions
	void endState(); // end the state
	void pausedState();
	void unpauseState();

	virtual void updateMousePositions(); //update the mouse position
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0; //update the input
	virtual void update(const float& dt) = 0; //update window
	virtual void render(sf::RenderTarget* target = nullptr) = 0; //rendering to the window
};

