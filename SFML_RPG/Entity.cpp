/**\file Entity.cpp*/
#include "Entity.h"



void Entity::initVariables()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movementSpeed = 100.f; //set entity speed
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
	if (this->sprite)
	{
		this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
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
