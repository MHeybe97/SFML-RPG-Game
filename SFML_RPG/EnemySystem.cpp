/**\file EnemySpawner.cpp*/
#include "stdafx.h"
#include "EnemySystem.h"


EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, 
	std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player)
{
	
}


EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos, EnemySpawner& enemy_spawner)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		this->activeEnemies.push_back(new RatEnemy(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner, this->player));
		enemy_spawner.increaseEnemyCounter();
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawner().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float & dt)
{
}

void EnemySystem::render(sf::RenderTarget * target)
{
}
