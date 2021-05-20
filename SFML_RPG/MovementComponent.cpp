/**\file MovementComponent.cpp*/
#include "stdafx.h"
#include "MovementComponent.h"

//Constructor
//! HitboxComponent class constructor
	/*!
	\param sprite a sf::Sprite - the sprite to be moved
	\param maxVelocity a float - the maximum speed when moving
	\param acceleration a float - the acceleration when moving
	\param deceleration a float - the deceleration when moving
	*/
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

//Destructor
//! HitboxComponent class destructor
	/*!
	\
	*/
MovementComponent::~MovementComponent()
{
}

//! Function to get the max velocity
	/*!
	\ returns max velocity
	*/
const float & MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

//! Function to get the velocity
	/*!
	\ returns velocity
	*/
const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

//! Function to get the movement states
	/*!
	\param state a short unsigned - the states of the different movements
	*/
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}

//! Function to stop all velocity
	/*!
	\brief stops velocity in both directions by setting it to 0
	*/
void MovementComponent::stopVelocity()
{
	//reset the vel to 0
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

//! Function to stop all  x-axis velocity
	/*!
	\brief stops velocity in the x-axis by setting it to 0
	*/
void MovementComponent::stopVelocityX()
{
	//reset the x vel to 0
	this->velocity.x = 0.f;
}

//! Function to stop all  y-axis velocity
	/*!
	\brief stops velocity in the y-axis by setting it to 0
	*/
void MovementComponent::stopVelocityY()
{
	//reset the y vel to 0
	this->velocity.y = 0.f;
}


//functions
//! Function to move entities 
	/*!
	\param dir_x a float - movement in the x-axis
	\param dir_y a float - movement in the y-axis
	\param dt a float - to update using delta time
	*/
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*accelerating a sprite until max velocity is reached*/

	//Acceleration

	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
}

//! Function to decelerate sprite
	/*!
	\param dt a float - update using delta time
	*/
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
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}

	else if(this->velocity.x < 0.f) //check for negative x
	{
		//Max velocity check 
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//deceleration 
		this->velocity.x += deceleration * dt;
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
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}

	else if (this->velocity.y < 0.f) //check for negative y
	{
		//Max velocity check 
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//deceleration 
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final Move
	this->sprite.move(this->velocity * dt); //uses velocity
}
