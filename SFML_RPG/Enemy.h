/**\file Enemy.h*/
#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy : public Entity
{
private:
	//EnemySpawner& enemySpawner;

	//Initializer Functions
	void initVariables();
	void initAnimations();
public:
	Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();

	//Functions
	void updateAnimation(const float& dt);

	void update(const float & dt, sf::Vector2f& mouse_pos_view);
	void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

