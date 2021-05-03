/**\file EnemySpawner.h*/
#pragma once
#include "Tile.h"

class Tile;
class EnemySpawner : public Tile
{
private:
	
	int Enemytype;
	int Enemyamount;
	int EnemytimeToSpawn;
	float EnemymaxDistance;
	bool spawned;

public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		         int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawner();

	//Accessors
	const std::string getAsString() const;
	const bool& getSpawned() const;
	//Modifiers
	void setSpawned(const bool spawned);

	//Functions
	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_Position = sf::Vector2f());
};
