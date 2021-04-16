/**\file Player.cpp*/
#include "stdafx.h"
#include "Player.h"


//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
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

	this->createHitboxComponent(this->sprite, 86.f, 67.f, 86.f, 111.f);
	this->createMovementComponent(350.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 0.4f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 3.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 0.4f, 0, 2, 13, 2, 192 * 2, 192);
}

//Destructors
Player::~Player()
{
}

//Accessors
AttributeComponent * Player::getAttributeComponent()
{
	return this->attributeComponent;
}


//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

const bool Player::isAlive() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isAlive();
	}
	return false;
}


void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainEXP(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;

	}
}

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
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{

			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(258.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainEXP(20);
	
	/*system("cls");
	std::cout << this->attributeComponent->debugPrint() << "\n";*/

	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimations(dt);
	
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget & target)
{
	target.draw(this->sprite); 

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
