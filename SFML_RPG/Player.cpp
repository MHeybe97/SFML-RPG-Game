/**\file Player.cpp*/
#include "Player.h"


//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

//Constructors 
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents();

	
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 0.4f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK_LEFT", 0.4f, 0, 1, 11, 1, 192, 192);
}

//Destructors
Player::~Player()
{
}

//Functions
void Player::update(const float & dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE_LEFT", dt);
	else if(this->movementComponent->getState(MOVING_LEFT))
		this->animationComponent->play("WALK_LEFT", dt);

}
