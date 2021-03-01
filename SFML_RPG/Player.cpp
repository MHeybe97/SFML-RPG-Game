/**\file Player.cpp*/
#include "Player.h"


//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	this->createMovementComponent(210.f);
}

//Constructors / Destrutors
Player::Player(float x, float y, sf::Texture* texture)
{
	this->initVariables();
	this->initComponents();

	this->createSprite(texture);
	this->setPosition(x, y);
}


Player::~Player()
{
}
