/**\file Entity.cpp*/
#include "Entity.h"



void Entity::initVariables()
{
	//this->texture = NULL;
	
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	//this->movementSpeed = 100.f; //set entity speed
}

Entity::Entity()
{
	this->initVariables();
	
}


Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
}

//component functions
void Entity::setTexture(sf::Texture& texture)
{
	
	this->sprite.setTexture(texture);
	
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//functions
void Entity::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	//move entity in x & y directions multiplied by movementspeed and delta time
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); //set velocity

		//this->sprite->move(this->movementComponent->getVelocity() * dt); //use velocity
	}
}

void Entity::update(const float & dt)
{
	/*if (this->movementComponent)
		this->movementComponent->update(dt);*/
}

void Entity::render(sf::RenderTarget* target)
{
	
		target->draw(this->sprite); //render shape on window
	
}
