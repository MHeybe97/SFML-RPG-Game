/**\file Player.cpp*/
#include "stdafx.h"
#include "Player.h"


//Initializer functions
//! Function to initialise private variables
	/*!
	*/
void Player::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->sword = new Sword(1, 2, 5, 200, 20, "Resources/Images/Sprites/Player/sword.png");
	this->sword->generate(1, 3);

	this->damageTimerMax = 1200;
}

//! Function to initialise comps
	/*!
	*/
void Player::initComponents()
{
	
}

//! Function to initialise animations
	/*!
	*/
void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 0.4f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 5.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 5.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 5.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 0.4f, 0, 2, 13, 2, 64, 64);
}

//! Function to create dynamic inventory
	/*!
	*/
void Player::initInventory()
{
	this->inventory = new Inventory(100);
}

//Constructors 
//! Player class constructor
	/*!
	\param x a float - players position on screen in the x-axis
	\param y a float - players position on screen in the y-axis
	\param texture_sheet a sf::Texture - the players texture sheet
	*/
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents();

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 45.f, 55.f);
	this->createMovementComponent(300, 1500.f, 900.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();


	this->setPosition(x, y);
	this->initAnimations();

	this->initInventory();
}

//Destructors
//! Player class destructor
	/*!
	*/
Player::~Player()
{
	delete this->inventory;
	delete this->sword;
}

//Accessors
//! Function to return attribute comp
	/*!
	*/
AttributeComponent * Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//! Function to get player sword
	/*!
	*/
Weapon * Player::getWeapon() 
{
	return this->sword;
}

//! Function to get initAttack boolean
	/*!
	*/
const bool & Player::getInitAttack() const
{
	return this->initAttack;
}

//! Function to get damageTimer
	/*!
	\brief restart damage timer if the elapsed time is more than or equal to the max damage timer
	*/
const bool Player::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}

//! Function to set initAtack
	/*!
	\param initAttack a bool - return true when player is attacking
	*/
void Player::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}


//! Function for player hp to decrease
	/*!
	\param hp an int - player hp
	*/
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

//! Function for player hp to increase
	/*!
	\param hp an int - player hp
	*/
void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

//! Function to see if player hp is less than or equal to 0
	/*!
	*/
const bool Player::isAlive() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isAlive();
	}
	return false;
}

//! Function for player exp to decrease
	/*!
	\param exp an int - player exp
	*/
void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

//! Function for player exp to increase
	/*!
	\param exp an int - player exp
	*/
void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainEXP(exp);
}


//! Function to update player animations
	/*!
	\param dt a float - update animations using delta time
	*/
void Player::updateAnimations(const float dt)
{
	if (this->attacking)
	{
		//set origin depending on direction
		if (this->sprite.getScale().x > 0.f) // facing left
		{
			this->sprite.setOrigin(96.f, 0.f);
		}
		else //facing right
		{
			this->sprite.setOrigin(258.f + 96.f, 0.f);
		}
		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) // facing left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else //facing right
			{
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
	}
	//if player not moving play idle animation
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	//if player moving left play walk left animation
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	//if the player moving right play walk right animation
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	//if the player moving up play walk up animation
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	//if the player moving down play walk down animation
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

//! Function to update player
	/*!
	\param dt a float - update using delta time
	\param mouse_pos_viewa sf::Vector2f - mouse position on the view
	*/
void Player::update(const float & dt, sf::Vector2f& mouse_pos_view)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainEXP(20);*/

	//update movement comp
	this->movementComponent->update(dt);

	//update animation comp
	this->updateAnimations(dt);
	
	//update hitbox comp
	this->hitboxComponent->update();

	//update sword
	this->sword->update(mouse_pos_view, this->getCenter());
}

//! Function to render player
	/*!
	\param target a sf::RenderTarget - the player target to be renderd
	\param shader a sf::Shader - light shader 
	\param light_position a sf::Vector2f - where the light is positioned in the game
	\return a boolean for when the hitbox is visible it will true else false
	*/
void Player::render(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		this->sword->render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->sword->render(target);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
