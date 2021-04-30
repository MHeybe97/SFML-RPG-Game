/**\file EnemySpawner.cpp*/
#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	: Tile(grid_x, grid_y, gridSizeF, texture, texture_rect, false, TileType::ENEMYSPAWNER)
{
	this->Enemytype = enemy_type;
	this->Enemyamount = enemy_amount;
	this->EnemytimeToSpawn = enemy_time_to_spawn;
	this->EnemymaxDistance = enemy_max_distance;
}


EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::spawn()
{
}

void EnemySpawner::clear()
{
}

void EnemySpawner::update()
{

}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_Position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", player_Position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
