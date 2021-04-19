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

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 45.f, 55.f);
	this->createMovementComponent(300, 1500.f, 900.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 0.4f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 5.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 5.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 5.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 0.4f, 0, 2, 13, 2, 64, 64);

	
	if (!this->weapon_texture.loadFromFile("Resources/Images/Sprites/Player/sword.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE." << "\n";
	this->weapon_sprite.setTexture(weapon_texture);

	this->weapon_sprite.setOrigin
	(
		this->weapon_sprite.getGlobalBounds().width / 2.f,
		this->weapon_sprite.getGlobalBounds().height
	);
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
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
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
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainEXP(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//this->attacking = true;

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

void Player::update(const float & dt, sf::Vector2f& mouse_Pos_View)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainEXP(20);
	
	/*system("cls");
	std::cout << this->attributeComponent->debugPrint() << "\n";*/

	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimations(dt);
	
	this->hitboxComponent->update();

	this->weapon_sprite.setPosition(this->getCenter());

	float dX = mouse_Pos_View.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_Pos_View.y - this->weapon_sprite.getPosition().y;

	const  float PI = 3.14159265;
	float deg = atan2(dY, dX) * 180 / PI;

	this->weapon_sprite.setRotation(deg + 90.f);
}

void Player::render(sf::RenderTarget & target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", this->getCenter());
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("light", this->getCenter());
		target.draw(this->weapon_sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
		target.draw(this->weapon_sprite);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
