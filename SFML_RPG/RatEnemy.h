/**\file RatEnemy.h*/
#pragma once
#include "Enemy.h"
class RatEnemy : public Enemy
{
private:
	void initVariables();
	void initAnimations();
public:
	RatEnemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~RatEnemy();

	//Functions

	void updateAnimation(const float& dt);

	 void update(const float & dt, sf::Vector2f& mouse_pos_view);
	 void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

