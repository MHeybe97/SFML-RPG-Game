/**\file Player.h*/
#pragma once
#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	//variables
	bool attacking;
	sf::Texture weapon_texture;
	sf::Sprite weapon_sprite;

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
	virtual void update(const float& dt, sf::Vector2f& mouse_Pos_View);

	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
};

