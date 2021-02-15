/**\file Entity.h*/
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

class Entity
{
private:
	void initVariables();
protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	//sf::RectangleShape shape; //entity shape
	float movementSpeed; //entity speed
public:
	Entity(); //constructor
	virtual ~Entity(); //destructor

	//component functions
	void createSprite(sf::Texture* texture);
	//functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y); //move the entity

	virtual void update(const float& dt); //update entity
	virtual void render(sf::RenderTarget* target); //render entity
};

