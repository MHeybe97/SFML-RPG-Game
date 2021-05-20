/**\file RatEnemy*/
#include "stdafx.h"
#include "RatEnemy.h"


void RatEnemy::initVariables()
{
}

//! Function to init enemy animation
	/*!
	*/
void RatEnemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 0.4f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 5.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 5.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 5.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 0.4f, 0, 2, 1, 2, 60, 64);
}

void RatEnemy::initAi()
{

}

//! Function to init enemy gui
	/*!
	*/
void RatEnemy::initGUI()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

//Constructor
//! RatEnemy class constructor
	/*!
	\param x a float - RatEnemy position in x-axis
	\param y a float - RatEnemy position in y-axis
	\param enemy_spawner an EnemySpawner obect - the position where the enemy spawns from
	*/
RatEnemy::RatEnemy(float x, float y, sf::Texture& texture_sheet, EnemySpawner& enemy_spawner, Entity& player)
	: Enemy(enemy_spawner)
{

	this->initVariables();
	this->initAi();
	this->initGUI();

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 45.f, 55.f);
	this->createMovementComponent(70.f, 800.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);
	this->initAnimations();

	this->enemyAI = new EnemyAi(*this, player);
}

//Destructor
//! RatEnemy class destructor
	/*!
	*/
RatEnemy::~RatEnemy()
{
	//delete enemy Ai
	delete this->enemyAI;
}

//! Function to update enemy animations
	/*!
	\param dt a float - to update using delta time
	*/
void RatEnemy::updateAnimation(const float & dt)
{
	//if enemy in idle state then play idle animation
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	//if enemy following player in the left direction the play walk left animation
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	//if enemy following player in the right direction then play walk right animation
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	//if enemy following player upwards then play walk up animation
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	//if enemy following player downwards then play walk down animation
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	//if enemy is being attacked/damaged then turn sprite else white
	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}

//! Function to update RatEnemy functions
	/*!
	\param dt a float - to update using delta time
	\param mouse_pos_view a sf::vector2f - mouse position in the view
	*/
void RatEnemy::update(const float & dt, sf::Vector2f & mouse_pos_view)
{
	//Update enemy movement with delta time
	this->movementComponent->update(dt);
	//update enemy hpbar after taking damage
	this->hpBar.setSize(sf::Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	//set the hpbar position above the enemy
	this->hpBar.setPosition(this->sprite.getPosition());
	//update animations
	this->updateAnimation(dt);
	//update hitbox
	this->hitboxComponent->update();
	//update enemy ai
	this->enemyAI->update(dt);
}

//! Function to render RatEnemy 
	/*!
	\param target a sf::RenderTarget - the RatEnemy target to be rendered
	\param shader a sf::shader - for the enemy to be affected by the lighting
	\param light_position a sf::Vector2F - where the light will be positioned
	\param show_hitbox a bool - returns false to not show hitbox or true to show it.
	*/
void RatEnemy::render(sf::RenderTarget & target, sf::Shader * shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", light_position);
		target.draw(this->sprite, shader);
		
	}
	else
	{
		target.draw(this->sprite);
		
	}
	target.draw(this->hpBar);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
