/**\file EnemySpawner.cpp*/
#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, 
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileType::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false)
{
	this->Enemytype = enemy_type;
	this->Enemyamount = enemy_amount;
	this->EnemytimeToSpawn = enemy_time_to_spawn;
	this->EnemymaxDistance = enemy_max_distance;
	this->spawned = false;
}


EnemySpawner::~EnemySpawner()
{

}

const std::string EnemySpawner::getAsString() const
{
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->Enemytype << " " << this->Enemyamount << " " << this->EnemytimeToSpawn << " " << this->EnemymaxDistance;

	return ss.str();
}

const bool & EnemySpawner::getSpawned() const
{
	return this->spawned;
}

void EnemySpawner::setSpawned(const bool spawned)
{
	this->spawned = spawned;
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
