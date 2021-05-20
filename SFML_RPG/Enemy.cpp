/**\file Enemy.cpp*/
#include "stdafx.h"
#include "Enemy.h"

//! Function to init private variables
	/*!
	*/
void Enemy::initVariables()
{
	this->gainExp = 10;
	this->damageTimerMax = 1200;
}

//! Function to init private variables
	/*!
	*/
void Enemy::initAnimations()
{
	
}

//Constructor
//! Enemy class constructor
	/*!
	\param enemy_spawner an EnemySpawner obect - the position where the enemy spawns from
	*/
Enemy::Enemy(EnemySpawner& enemy_spawner)
	: enemySpawner(enemy_spawner)
{
	this->initVariables();
	this->initAnimations();
	
}

//Destructor
//! Enemy class destructor
	/*!
	*/
Enemy::~Enemy()
{
}

const unsigned & Enemy::getGainExp() const
{
	return this->gainExp;
}

//! Function to return enemySpawner
	/*!
	*/
EnemySpawner & Enemy::getEnemySpawner()
{
	return this->enemySpawner;
}

//! Function to get damageTimer when it's done
	/*!
	*/
const bool Enemy::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

//! Function to restart damageTimer
	/*!
	*/
void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

//! Function to calculate exp gained at random
	/*!
	*/
void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 5 + 1);
}

//! Function for enemy to lose hp
	/*!
	\param hp an int - enemy hp
	*/
void Enemy::loseHP(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

//! Function to check if enemy is dead
	/*!
	\
	*/
const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}
	return false;
}

//! Function to get attribute comp for enemy
	/*!
	*/
const AttributeComponent * Enemy::getAttributeComponent() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
}

