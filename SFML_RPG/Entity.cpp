/**\file Entity.cpp*/
#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	//set components to null
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	this->skillComponent = NULL;
}

//Constructor
//! Entity class constructor
	/*!
	\brief initialise private functions 
	*/
Entity::Entity()
{
	//init private variables
	this->initVariables();
}

//Destructor
//! Entity class destructor
	/*!
	\brief delete dynamic component objects
	*/
Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillComponent;
}

//component functions
//! Function to set entity texture
	/*!
	\param texture a sf::Texture - the entities texture
	*/
void Entity::setTexture(sf::Texture& texture)
{
	//set entity texture
	this->sprite.setTexture(texture);
	
}

//! Function to create hitbox comp
	/*!
	\param sprite a sf::Sprite - the sprite the hitbox belongs to
	\param offset_x a float - the hitboxes offset in the x-axis
	\param offset_y a float - the hitboxes offset in the y-axis
	\param width a float - the hitbox width
	\param height a float the hitbox height
	*/
void Entity::createHitboxComponent(sf::Sprite & sprite, 
	float offset_x, float offset_y,
	float width, float height)
{
	//create a new hitbox
	this->hitboxComponent = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

//! Function to create movement comp
	/*!
	\param maxVelocity a float - the max vel when moving
	\param acceleration a float - the acceleration when moving 
	\param decelration a float - decelration after accelerating
	*/
void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	//create new movement comp
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

//! Function to create animation comp
	/*!
	\param texture_sheet a sf::Texture - the texture sheet for the animation
	*/
void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
	//create new animation comp
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//! Function to create attribute comp
	/*!
	\param level an unsigned - the level to start the entity on
	*/
void Entity::createAttributeComponent(const unsigned level)
{
	//create new attribute comp 
	this->attributeComponent = new AttributeComponent(level);
}

//! Function to create skill comp
	/*!
	*/
void Entity::createSkillComponent()
{
	//create new skill comp
	this->skillComponent = new SkillComponent();
}

//! Function to return entity position
	/*!
	*/
const sf::Vector2f & Entity::getPosition() const
{
	//if entity has hitbox then get its position
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	//return sprite position
	return this->sprite.getPosition();
}

//! Function to calculate entity centre
	/*!
	\brief add the hitbox position with half its width and height same with the sprite
	*/
const sf::Vector2f Entity::getCenter() const
{
	//if entity has hitbox
	if (this->hitboxComponent)
		//then add hitbox position with half its width and height
		return this->hitboxComponent->getPosition() +
		sf::Vector2f
		(
			this->hitboxComponent->getGlobalBounds().width / 2.f,
			this->hitboxComponent->getGlobalBounds().height / 2.f
		);

	return
		//add sprite position with half its width and height
		this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);
}

//! Function to calculate entities grid-position
	/*!
	\param gridSizeI an int - the grid-size to be divided by the hitbox position and sprite position get its gridposition
	*/
const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	//if entity has a hitbox then divid its position with the grid-size
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);
	//divide sprite position with grid-size
	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI
	);
}

//! Function to get entity global bounds
	/*!
	\brief get entitty global bounds for sprite and hitbox
	*/
const sf::FloatRect Entity::getGlobalBounds() const
{
	//if entity has hitbox then return global bounds
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	//return entity sprite global bounds
	return this->sprite.getGlobalBounds();
}

//! Function to calculate entity nextposition
	/*!
	\param dt a float - to update using delta time
	*/
const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	//if entity has a hitbox and movement comp then return the hitbox next pos as the movement comp multiplied by delta time
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//! Function to set entity position
	/*!
	\param x a float - set entity in the x-axis
	\param y a float - set entity in the y-axis
	*/
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

//! Function to move entity
	/*!
	\param dir_x a float - moving entity in the x-axis
	\param dir_y a float - moving the enity in
	*/
void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	//move entity in x & y directions multiplied by movementspeed and delta time
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt); //set velocity

	if (skillComponent)
	{
		this->skillComponent->gainExp(SKILLS::ENDURANCE, 1);
		std::cout << this->skillComponent->getSkill(SKILLS::ENDURANCE) << "\n";
	}
}

//! Function to stop all velocity by setting it to 0
	/*!
	*/
void Entity::stopVelocity()
{
	//if entity has movement comp then stop vel
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

//! Function to stop x velocity by setting it to 0
	/*!
	*/
void Entity::stopVelocityX()
{
	//if entity has movement comp then stop entity in x-axis
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

//! Function to stop y velocity by setting it to 0
	/*!
	*/
void Entity::stopVelocityY()
{
	//if entity has movement comp then stop entity in y-axis
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

//! Function to get distance between entities
	/*!
	*/
const float Entity::getDistance(const Entity& entity) const
{
	//calculation for distance between entities
	return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
	
}


