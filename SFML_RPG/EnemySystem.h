/**\file EnemySystem.h*/
#pragma once
#include "EnemySpawner.h"
#include "RatEnemy.h"
#include "Enemy.h"

enum EnemyTypes {RAT = 0};

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	Entity& player;

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies, 
		std::map<std::string, sf::Texture>& textures, Entity& player);
	virtual ~EnemySystem();

	//Accessors

	//Modifiers

	//Functions
	void createEnemy(const short type, const float xPos, const float yPos, EnemySpawner& enemy_spawner);
	void removeEnemy(const int index);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

