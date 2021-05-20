/**\file EnemySpawner.cpp*/
#include "stdafx.h"
#include "EnemySystem.h"

//Constructor
//! EnemySystem class constructor
	/*!
	\param activeEnemies  a vector - enemies that are active
	\param textures a std::map - the enemy textures
	\param player and Entity object
	*/
EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, 
	std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player)
{
	
}

//Destructor
//! EnemySystem class destructor
	/*!
	*/
EnemySystem::~EnemySystem()
{
}

//! Function to create a new enemies
	/*!
	\param type a short - the type of enemy
	\param xpos a float - enemy position in x-axis
	\param ypos a float - enemy position in y-axis
	\param enemy_spawner an EnemySpawner objecct
	*/
void EnemySystem::createEnemy(const short type, const float xPos, const float yPos, EnemySpawner& enemy_spawner)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		//create new RatEnemy
		this->activeEnemies.push_back(new RatEnemy(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner, this->player));
		//then increase the number of enemies
		enemy_spawner.increaseEnemyCounter();
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

//! Function to remove enemies
	/*!
	\param index an int - the amount of enemies active
	*/
void EnemySystem::removeEnemy(const int index)
{
	//decrese the amoun of enemies
	this->activeEnemies[index]->getEnemySpawner().decreaseEnemyCounter();
	//then delete active enemies
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float & dt)
{
}

void EnemySystem::render(sf::RenderTarget * target)
{
}
