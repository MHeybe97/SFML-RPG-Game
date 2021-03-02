/**\file Entity.h*/
#pragma once

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	//sf::Texture* texture;
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	//float movementSpeed; //entity speed
public:
	Entity(); //constructor
	virtual ~Entity(); //destructor

	//component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	//functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt); //move the entity

	virtual void update(const float& dt); //update entity
	virtual void render(sf::RenderTarget* target); //render entity
};

