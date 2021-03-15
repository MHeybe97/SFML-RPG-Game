/**\file State.cpp*/
#include "stdafx.h"
#include "State.h"



State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window; //Application window
	this->supportedKeys = state_data->supportedKeys; //supported keys for our application
	this->states = state_data->states; //different gamestates 
	this->quit = false; //quitting the application
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 100.f;
	this->gridSize = state_data->gridSize;
}

//destructor
State::~State()
{
}

//Accessors
const bool & State::getQuit() const
{
	return this->quit; //quitting the application
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//Functions
void State::endState()
{
	this->quit = true;
}

void State::pausedState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition(); //the mouse position on the screen
	this->mousePosWindow = sf::Mouse::getPosition(*this->window); //the mouse position on the window
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)); //mouse position on the view
	this->mousePosGrid =
		sf::Vector2u(
			static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
			static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
		);
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 200.f * dt;
}
