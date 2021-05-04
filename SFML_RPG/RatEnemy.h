/**\file RatEnemy.h*/
#pragma once
#include "Enemy.h"
#include "EnemyAi.h"

class RatEnemy : public Enemy
{
private:
	void initVariables();
	void initAnimations();
	void initAi();
	void initGUI();

	EnemyAi* enemyAI;
	sf::RectangleShape hpBar;

public:
	RatEnemy(float x, float y, sf::Texture& texture_sheet, EnemySpawner& enemy_spawner, Entity& player);
	virtual ~RatEnemy();

	//Functions

	void updateAnimation(const float& dt);

	 void update(const float & dt, sf::Vector2f& mouse_pos_view);
	 void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

