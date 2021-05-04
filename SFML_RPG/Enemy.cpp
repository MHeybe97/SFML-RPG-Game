/**\file Enemy.cpp*/
#include "stdafx.h"
#include "Enemy.h"


void Enemy::initVariables()
{
	this->gainExp = 10;
}

void Enemy::initAnimations()
{
	
}

Enemy::Enemy(EnemySpawner& enemy_spawner)
	: enemySpawner(enemy_spawner)
{
	this->initAnimations();
	this->initVariables();
}


Enemy::~Enemy()
{
}

const unsigned & Enemy::getGainExp() const
{
	return this->gainExp;
}

EnemySpawner & Enemy::getEnemySpawner()
{
	return this->enemySpawner;
}

void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 5 + 1);
}

void Enemy::loseHP(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}
	return false;
}

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

