/**\file HitBoxComponent*/
#pragma once

//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//
//#include "SFML\System.hpp"
//#include "SFML\Window.hpp"
//#include "SFML\Graphics.hpp"
//#include "SFML\Audio.hpp"
//#include "SFML\Network.hpp"

class HitBoxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitBoxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height);
	virtual ~HitBoxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Functions
	bool Intersects(const sf::FloatRect frect);

	void update();
	void render(sf::RenderTarget& target);
};

