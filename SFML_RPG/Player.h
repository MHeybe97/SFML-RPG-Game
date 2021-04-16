/**\file Player.h*/
#pragma once
#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	//variables
	bool attacking;
	//Initializer functions
	void initVariables();
	void initComponents();
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
	virtual void update(const float& dt);

	void render(sf::RenderTarget& target);
};

