/**\file Entity.h*/
#pragma once

#include "HitBoxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

class HitBoxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;

class Entity
{
private:
	void initVariables();
protected:
	
	sf::Sprite sprite;

	HitBoxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	
public:
	Entity(); //constructor
	virtual ~Entity(); //destructor

	//component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);

	//Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(const float x, const float y);

	//functions
	virtual void move(const float x, const float y, const float& dt); //move the entity
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0; //update entity
	virtual void render(sf::RenderTarget& target, const bool show_hitbox) = 0; //render entity
};

