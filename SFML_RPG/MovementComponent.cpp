/**\file MovementComponent.cpp*/
#include "MovementComponent.h"


//construtor
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

//destructor
MovementComponent::~MovementComponent()
{
}

const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

//functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*accelerating a sprite until max velocity is reached*/

	//Acceleration

	this->velocity.x += this->acceleration * dir_x;

	

	this->velocity.y += this->acceleration * dir_y;
}


void MovementComponent::update(const float & dt)
{
	/*Decelerates the sprite and controls maximum velocity.
	Moves the sprite*/

	if (this->velocity.x > 0.f) //check for positive x
	{
		//Max velocity check positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//deceleration 
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}

	else if(this->velocity.x < 0.f) //check for negative x
	{
		//Max velocity check 
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//deceleration 
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	//Deceleration y
	if (this->velocity.y > 0.f) //check for positive y
	{
		//Max velocity check positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//deceleration 
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}

	else if (this->velocity.y < 0.f) //check for negative y
	{
		//Max velocity check 
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//deceleration 
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final Move
	this->sprite.move(this->velocity * dt); //uses velocity
}
