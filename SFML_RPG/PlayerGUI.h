/**\file PlayerGUI.h*/
#pragma once

#include "Player.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;
	sf::Font font;

	//HP BAR
	std::string hpBarString;
	sf::Text hpBarText;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;
	float hpBarMaxWidth;

	//EXP BAR

	

	void initFonts();
	void initHPBar();

public:
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	//Accessors

	//Functions
	void updateHPBar();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

