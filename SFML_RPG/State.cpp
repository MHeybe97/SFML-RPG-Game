/**\file State.cpp*/
#include "State.h"



State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window; //Application window
	this->supportedKeys = supportedKeys; //supported keys for our application
	this->states = states; //different gamestates 
	this->quit = false; //quitting the application
}

//destructor
State::~State()
{
}

const bool & State::getQuit() const
{
	return this->quit; //quitting the application
}

void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition(); //the mouse position on the screen
	this->mousePosWindow = sf::Mouse::getPosition(*this->window); //the mouse position on the window
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)); //mouse position on the view
}
