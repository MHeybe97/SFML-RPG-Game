/**\file Player.h*/
#pragma once
#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Entity;

class Player : public Entity
{
private:
	//variables
	Inventory* inventory;

	bool initAttack;
	bool attacking;
	Sword* sword;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;
	
	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();
	void initInventory();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Accessors
	AttributeComponent* getAttributeComponent();
	Weapon* getWeapon();

	const bool& getInitAttack() const;
	const bool getDamageTimer();

	//Modifiers
	void setInitAttack(const bool initAttack);

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	const bool isAlive() const;
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void updateAnimations(const float dt);
	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

