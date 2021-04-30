/**\file PlayerGUI.h*/
#pragma once

#include "Player.h"
#include "Gui.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;
	sf::Font font;
	sf::VideoMode vm;

	//Level Bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	//HP BAR
	std::string hpBarString;
	sf::Text hpBarText;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;
	float hpBarMaxWidth;

	gui::ProgressBar* hpBar;

	//EXP BAR
	std::string expBarString;
	sf::Text expBarText;
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInner;
	float expBarMaxWidth;

	//gui::ProgressBar* expBar;
	
	void initFonts();
	void initLevelBar();
	void initEXPBar();
	void initHPBar();

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	//Accessors

	//Functions
	void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();
	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderEXPBAR(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

