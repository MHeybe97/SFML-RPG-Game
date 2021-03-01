/**\file Entity.cpp*/
#include "Entity.h"



void Entity::initVariables()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movementComponent = NULL;
	//this->movementSpeed = 100.f; //set entity speed
}

Entity::Entity()
{
	this->initVariables();
	
}


Entity::~Entity()
{
	delete this->sprite;
}

//component functions
void Entity::createSprite(sf::Texture * texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
	
}

void Entity::createMovementComponent(const float maxVelocity)
{
	this->movementComponent = new MovementComponent(maxVelocity);
}

//functions
void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	//move entity in x & y directions multiplied by movementspeed and delta time
	if (this->sprite && this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y); //set velocity
		this->sprite->move(this->movementComponent->getVelocity() * dt); //use velocity
	}
}

void Entity::update(const float & dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite); //render shape on window
	}
}
