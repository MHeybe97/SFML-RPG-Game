/**\file EnemySpawner.cpp*/
#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, 
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileType::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false)
{
	this->Enemytype = enemy_type;
	this->Enemyamount = enemy_amount;
	this->EnemyCounter = 0;
	this->EnemySpawnTimer.restart();
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

const int & EnemySpawner::getEnemyAmount() const
{
	return this->Enemyamount;
}

const int & EnemySpawner::getEnemyCounter() const
{
	return this->EnemyCounter;
}

void EnemySpawner::setSpawned(const bool spawned)
{
	this->spawned = spawned;
	this->EnemySpawnTimer.restart();
}

const bool EnemySpawner::canSpawn() const
{
	if (this->EnemySpawnTimer.getElapsedTime().asSeconds() >= this->EnemytimeToSpawn)
	{
		return true;
	}
	return false;
}

void EnemySpawner::increaseEnemyCounter()
{
	if (this->EnemyCounter > this->Enemyamount)
		this->EnemyCounter = this->Enemyamount;
	else
		++this->EnemyCounter;
}

void EnemySpawner::decreaseEnemyCounter()
{
	if (this->EnemyCounter < 0)
		this->EnemyCounter = 0;
	else
		--this->EnemyCounter;
}

void EnemySpawner::update()
{
	if (this->canSpawn())
		this->spawned = false;
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
