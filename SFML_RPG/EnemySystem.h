/**\file EnemySystem.h*/
#pragma once
#include "EnemySpawner.h"
#include "RatEnemy.h"
#include "Enemy.h"

enum EnemyTypes {RAT = 0}; //!< enum for enemy types

/*!\class EnemySystem
\brief a class for creating enemies 
*/
class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures; //!< a map of textures
	std::vector<Enemy*>& activeEnemies; //!< a dynamic vector of enemies
	Entity& player; //!< the player

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies, 
		std::map<std::string, sf::Texture>& textures, Entity& player); //!< EnemySystem class constructor 
	virtual ~EnemySystem(); //!< EnemySystem class destructor

	//Accessors

	//Modifiers

	//Functions
	void createEnemy(const short type, const float xPos, const float yPos, EnemySpawner& enemy_spawner); //!< create an enemy
	void removeEnemy(const int index); //!< remove an enemy
	void update(const float& dt); //!< update enemy system
	void render(sf::RenderTarget* target);
};

