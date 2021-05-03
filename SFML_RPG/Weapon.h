/**\file Weapon.h*/
#pragma once
#include "Item.h"
class Weapon :
	public Item
{
private:
	void initVariables();
	

protected:
	sf::Texture weapon_texture;
	sf::Sprite weapon_sprite;

	int damageMin;
	int damageMax;
	unsigned range;

	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;

public:
	Weapon(unsigned value, std::string texture_file);
	virtual ~Weapon();

	//Accessors
	const unsigned& getDamageMin() const;
	const unsigned& getDamageMax() const;

	const unsigned& getRange() const;
	const bool getAttackTimer();

	//Functions
	virtual Item* clone() = 0;

	virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

