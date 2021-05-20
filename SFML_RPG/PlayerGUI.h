/**\file PlayerGUI.h*/
#pragma once

#include "Player.h"
#include "Gui.h"

/*!\class PlayerGUI
\brief a class for the player gui
*/
class PlayerGUI
{
private:
	Player* player; //!< the player
	sf::Font font; //!< gui font
	sf::VideoMode vm; //!< the get the windows width and height

	//Level Bar
	std::string levelBarString; //!< characters for the level bar
	sf::Text levelBarText; //!< the text for the level bar
	sf::RectangleShape levelBarBack; //!< level bar back

	//HP BAR
	std::string hpBarString; //!< player hp bar text
	sf::Text hpBarText; //!< player hp bar text
	sf::RectangleShape hpBarBack; //!< hp bar background
	sf::RectangleShape hpBarInner; //!< red hp bar for when player is attacked
	float hpBarMaxWidth; //!< max width for the hp bar

	gui::ProgressBar* hpBar;

	//EXP BAR
	std::string expBarString; //!< exp bar text
	sf::Text expBarText; //!<exp bar text
	sf::RectangleShape expBarBack; //!< exp bar background
	sf::RectangleShape expBarInner; //!< blue exp bar 
	float expBarMaxWidth; //!< max exp bar width
	
	void initFonts(); //!< initialise fonts 
	void initLevelBar(); //!< initialise level bar
	void initEXPBar(); //!< initialise EXP bar
	void initHPBar(); //!<  initialise  HP bar

public:
	PlayerGUI(Player* player, sf::VideoMode& vm); //!< player gui constructor
	virtual ~PlayerGUI(); //!< player gui destructor

	//Accessors

	//Functions
	void updateLevelBar(); //!< update the level bar
	void updateEXPBar(); //!< update exp bar
	void updateHPBar(); //!< update hp bar
	void update(const float& dt); //!< update player gui

	void renderLevelBar(sf::RenderTarget& target); //!< render level bar
	void renderEXPBAR(sf::RenderTarget& target); //!< render exp bar
	void renderHPBar(sf::RenderTarget& target); //!< render hp bar

	void render(sf::RenderTarget& target); //!< render player gui
};

