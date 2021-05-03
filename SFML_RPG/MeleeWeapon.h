/**\file MeleeWeapon.h */
#pragma once

#include "Weapon.h"

class Item;

class MeleeWeapon : public Weapon
{
private:

protected:
	

public:
	MeleeWeapon(unsigned value, std::string texture_file);
	virtual ~MeleeWeapon();

	virtual MeleeWeapon* clone() = 0;
	//Functions 
	virtual void update(const sf::Vector2f & mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

