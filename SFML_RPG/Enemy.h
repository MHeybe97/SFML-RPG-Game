/**\file Enemy.h*/
#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

class Enemy : public Entity
{
private:
	//Variables
	EnemySpawner& enemySpawner;
	unsigned gainExp;

	//Initializer Functions
	virtual void initVariables() = 0;
	virtual void initAnimations() = 0;
public:
	Enemy(EnemySpawner& enemy_spawner);
	virtual ~Enemy();

	//Accessors
	const unsigned& getGainExp() const;
	EnemySpawner& getEnemySpawner();
	//Functions
	virtual void generateAttributes(const unsigned level);
	virtual void loseHP(const int hp);
	virtual const bool isDead() const;

	virtual const AttributeComponent* getAttributeComponent() const;

	virtual void updateAnimation(const float& dt) = 0;

	virtual void update(const float & dt, sf::Vector2f& mouse_pos_view) = 0;
	virtual void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

