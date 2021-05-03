/**\file Weapon.h*/
#include "stdafx.h"
#include "Weapon.h"


void Weapon::initVariables()
{
	this->range = 10;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer 
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

Weapon::Weapon(unsigned value, std::string texture_file)
	: Item(value)
{
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE." << texture_file << "\n";
	this->weapon_sprite.setTexture(weapon_texture);
}


Weapon::~Weapon()
{
}

const unsigned & Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned & Weapon::getDamageMax() const
{
	return this->damageMax;
}

const unsigned & Weapon::getRange() const
{
	return this->range;
}

const bool Weapon::getAttackTimer()
{
	std::cout << this->attackTimer.getElapsedTime().asMicroseconds() << "\n";
	if (this->attackTimer.getElapsedTime().asMicroseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}
