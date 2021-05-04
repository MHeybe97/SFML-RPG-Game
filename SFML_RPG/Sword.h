/**\file Sword.h*/
#pragma once
#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword : public MeleeWeapon
{
private:

public:
	Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file);
	virtual ~Sword();

	virtual Sword* clone();
	//Functions
	void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

