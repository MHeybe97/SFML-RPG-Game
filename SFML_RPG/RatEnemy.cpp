/**\file RatEnemy*/
#include "stdafx.h"
#include "RatEnemy.h"


void RatEnemy::initVariables()
{
}

void RatEnemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 0.4f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 5.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 5.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 5.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 0.4f, 0, 2, 1, 2, 60, 64);
}

RatEnemy::RatEnemy(float x, float y, sf::Texture& texture_sheet)
	: Enemy(x, y, texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 45.f, 55.f);
	this->createMovementComponent(300, 1500.f, 900.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimations();
}


RatEnemy::~RatEnemy()
{

}

void RatEnemy::updateAnimation(const float & dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void RatEnemy::update(const float & dt, sf::Vector2f & mouse_pos_view)
{
	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}

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

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
