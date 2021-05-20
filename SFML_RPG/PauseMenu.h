/**\PauseMenu.h*/
#pragma once

#include "Gui.h"

/*!\class PauseMenu
\brief a class for the pause menu
*/
class PauseMenu
{
private:
	sf::Font& font; //!< menu font
	sf::Text manuText; //!< menu text/title

	sf::RectangleShape background; //!< menu background
	sf::RectangleShape container; //!< menu container

	std::map<std::string, gui::Button*> buttons; //!< menu buttons

	
public:
	PauseMenu(sf::VideoMode& vm, sf::Font& font); //!< PausMenu class Constructor 
	virtual ~PauseMenu(); //!<PauseMenu Destructor

	//Accessors
	std::map<std::string, gui::Button*>& getButtons(); //!< returns menu buttons

	//Functions
	const bool isButtonPressed(const std::string key); //!< checks to see if a particular button is pressed

	void addButton(
		const std::string key, 
		const float y, 
		const float width,
		const float height, 
		const unsigned char_Size, 
		const std::string text); //!< add button on the menu

	void update(const  sf::Vector2i& mousePosWindow); //!< update menu
	void render(sf::RenderTarget& target); //!< render menu

};

