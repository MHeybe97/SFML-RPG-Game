/**\file Player.h*/
#pragma once
#include "Entity.h"
#include "Sword.h"

class Entity;

class Player : public Entity
{
private:
	//variables
	bool attacking;
	Sword sword;
	
	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Accessors
	AttributeComponent* getAttributeComponent();

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	const bool isAlive() const;
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void updateAttack();
	void updateAnimations(const float dt);
	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
};

