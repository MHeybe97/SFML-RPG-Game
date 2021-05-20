/**\file Entity.h*/
#pragma once

#include "HitBoxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class HitBoxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;

/*!\class Entity
\brief base class for all entities in the game
*/
class Entity
{
private:
	void initVariables(); //!< initialise private variables
protected:
	
	sf::Sprite sprite; //!< entity sprite

	HitBoxComponent* hitboxComponent; //!<entity hitboxComponent object
	MovementComponent* movementComponent; //!<entity movementComponent object
	AnimationComponent* animationComponent; //!< entity animationComponent object
	AttributeComponent* attributeComponent; //!< entity attributeComponent
	SkillComponent* skillComponent; //!< entity skillComponent
	
public:
	Entity(); //constructor
	virtual ~Entity(); //destructor

	//component functions
	void setTexture(sf::Texture& texture); //!< entity texture
	void createHitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y,
		float width, float height); //!< create the hitbox
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration); //!< create the movement comp
	void createAnimationComponent(sf::Texture& texture_sheet); //!< create animation comp
	void createAttributeComponent(const unsigned level); //!< create attribute comp
	void createSkillComponent(); //!< create skill comp

	//Accessors
	virtual const sf::Vector2f& getPosition() const; //return entity position if it has a hitbox
	virtual const sf::Vector2f getCenter() const; //!<return the center of an entity
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const; //!<return the entities position in the grid
	virtual const sf::FloatRect getGlobalBounds() const; //!< return the entities global bounds
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const; //!< get the entities next position

	//Modifiers
	virtual void setPosition(const float x, const float y); //!< set the entities position

	//functions
	virtual void move(const float x, const float y, const float& dt); //move the entity
	virtual void stopVelocity(); //!<stop all velocity
	virtual void stopVelocityX(); //!<stop velocity in the x-axis
	virtual void stopVelocityY(); //!<stop velocity in the y-axis

	virtual void update(const float& dt, sf::Vector2f& mouse_Pos_View) = 0; //update entity
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f light_position, const bool show_hitbox) = 0; //render entity

	//Calculations
	virtual const  float getDistance(const Entity& entity) const; //!<get distance calculations 
};

