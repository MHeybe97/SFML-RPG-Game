/**\file AttributeComponent.cpp*/
#include "stdafx.h"
#include "AttributeComponent.h"

//Constructor
//! AttributeComponent class constructor
	/*!
	\param level an int - the level to set the entity on 
	*/
AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

//Destructor
//! AttribbuteComponent class destructor
	/*!
	\
	*/
AttributeComponent::~AttributeComponent()
{
}

//Functions
//! Function to print debug text on the screen
	/*!
	\brief to check if stats are working
	*/
std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expNext << "\n"
		<< "Attp: " << this->attributePoints << "\n";

	return ss.str();
}

//! Function to lose health points when attacked
	/*!
	\param hp an int - the entities health point
	*/
void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

//! Function to gain health points 
	/*!
	\param hp an int - the entities health point
	*/
void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

//! Function to lose experiance points
	/*!
	\param exp an int - the entities experiance point
	*/
void AttributeComponent::loseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

//! Function to lose experiance points
	/*!
	\param exp an int - the entities experiance point
	*/
void AttributeComponent::gainEXP(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

//! Function to retuen hp when it's 0
	/*!
	\brief used to see if an entity hp is 0
	*/
const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}

//! Function to retuen hp when it's 0
	/*!
	\brief used to see if an entity hp is 0
	*/
const bool AttributeComponent::isAlive() const
{
	return this->hp <= 0;
}

//! Function to upate attribute stats
	/*!
	\return a boolean when the hp is reset
	*/
void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax       = this->vitality     * 19 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMin   = this->strength     * 2 + this->strength                  / 4 + this->intelligence / 5;
	this->damageMax   = this->strength     * 2 + this->strength                  / 2 + this->intelligence / 5;
	this->accuracy    = this->dexterity    * 5 + this->dexterity                 / 2 + this->intelligence / 5;
	this->defence     = this->agility      * 2 + this->agility                   / 4 + this->intelligence / 5;
	this->luck        = this->intelligence * 2 + this->intelligence / 5;
	

	if (reset)
	{
		this->hp = hpMax;
	}
}

//! Function to upate leveling
	/*!
	\brief how leveling entities is decided
	*/
void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		++this->attributePoints;
	}
}

//! Function to upate levels
	/*!
	\brief update the level
	*/
void AttributeComponent::update()
{
	this->updateLevel();

}
