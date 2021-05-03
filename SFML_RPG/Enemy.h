/**\file Enemy.h*/
#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy : public Entity
{
private:
	//Variables
	unsigned gainExp;

	//Initializer Functions
	virtual void initVariables() = 0;
	virtual void initAnimations() = 0;
public:
	Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();

	//Accessors
	const unsigned& getGainExp() const;

	//Functions
	virtual void loseHP(const int hp);
	virtual const bool isDead() const;

	virtual const AttributeComponent* getAttributeComponent() const;

	virtual void updateAnimation(const float& dt) = 0;

	virtual void update(const float & dt, sf::Vector2f& mouse_pos_view) = 0;
	virtual void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};
