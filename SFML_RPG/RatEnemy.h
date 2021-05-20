/**\file RatEnemy.h*/
#pragma once
#include "Enemy.h"
#include "EnemyAi.h"

/*!\class Enemy
\brief a child class of Enemy
*/
class RatEnemy : public Enemy
{
private:
	void initVariables(); //!< init private variables
	void initAnimations(); //!< init animations
	void initAi(); //!< init enemy ai
	void initGUI(); //!< init enemy gui

	EnemyAi* enemyAI; //!< enemy ai behaiviour
	sf::RectangleShape hpBar; //!< enemy health bar

public:
	RatEnemy(float x, float y, sf::Texture& texture_sheet, EnemySpawner& enemy_spawner, Entity& player); //!<RatEnemy constructor
	virtual ~RatEnemy(); //!< RatEnemy destructor

	//Functions

	void updateAnimation(const float& dt); //!< update enemy animations

	 void update(const float & dt, sf::Vector2f& mouse_pos_view); //!< Update RatEnemy
	 void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false); //!< render RatEnemy
};

