/**\file MovementComponent.h*/
#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

class MovementComponent
{
private:
	//Variables
	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

	//initializer functions

public:
	MovementComponent(float maxVelocity);
	virtual ~MovementComponent();
	//accessors
	const sf::Vector2f& getVelocity() const;
	//functions
	void move(const float dir_x, const float dir_y);
	void update(const float& dt);
};

