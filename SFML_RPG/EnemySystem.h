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
public:
	EnemySystem(std::vector<Enemy*>& activeEnemies, 
		std::map<std::string, sf::Texture>& textures);
	virtual ~EnemySystem();

	//Accessors

	//Modifiers

	//Functions
	void createEnemy(const short type, const float xPos, const float yPos);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

