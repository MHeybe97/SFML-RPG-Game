/**\file HitBoxComponent*/
#include "stdafx.h"
#include "HitBoxComponent.h"

//Constructor
//! HitboxComponent class constructor
	/*!
	\param sprite a sf::Sprite object - the sprite 
	\param offset_x a float - to be added to the sprite position in the x-axis
	\param offset_y a float - to be added to the sprite position in the y-axis
	\param width a float - the width of the hitbox
	\param height a float - the height of the hitbox
	*/
HitBoxComponent::HitBoxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

//Destructor
//! HitboxComponent class destructor
	/*!
	\
	*/
HitBoxComponent::~HitBoxComponent()
{
}

//! Function to get hitbox position
	/*!
	\
	*/
const sf::Vector2f & HitBoxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

//! Function to get hitbox gloablbounds
	/*!
	\
	*/
const sf::FloatRect HitBoxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

//! Function to calculate hitbox next position
	/*!
	\param velocity a Vector2f - velocity of the hitbox
	*/
const sf::FloatRect & HitBoxComponent::getNextPosition(const sf::Vector2f & velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

//! Function to set hitbox position
	/*!
	\param position a Vector2f - set the hitbox position by subtracting the offset in both axis
	*/
void HitBoxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

//! Function to set hitbox position
	/*!
	\param position a Vector2f - set the hitbox position by subtracting the offset in both axis
	*/
void HitBoxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

//! Function to see where the hitbox intersects 
	/*!
	\param frect a FloatRect - where the the hitbox intersects with something
	*/
bool HitBoxComponent::Intersects(const sf::FloatRect frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

//! Function update the hitbox position
	/*!
	\brief set the hitbox position by adding the sprite positions with the offset
	*/
void HitBoxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

//! Function to render the hitbox position
	/*!
	\param target a RenderTarget - the target to be renderd 
	*/
void HitBoxComponent::render(sf::RenderTarget & target)
{
	target.draw(this->hitbox);
}
