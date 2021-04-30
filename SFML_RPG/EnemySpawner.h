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

public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawner();

	//Functions
	void spawn();
	void clear();

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_Position = sf::Vector2f());
};

