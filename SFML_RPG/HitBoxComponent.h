/**\file HitBoxComponent*/
#pragma once

/*!\class HitBoxComponent
\brief a class to handle all the games collision detection
*/
class HitBoxComponent
{
private:
	sf::Sprite& sprite; //!< the sprite the hitbox will be on
	sf::RectangleShape hitbox; //!< the hitbox
	sf::FloatRect nextPosition; //!< where the hitboxes next position will be 
	float offsetX; //!< offset x for posistioning the hitbox
	float offsetY; //!< offset y for positioning the hitbox

public:
	HitBoxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height); //!< Hitbox constructor
	virtual ~HitBoxComponent(); //!< Hitbox destructor

	//Accessors
	const sf::Vector2f& getPosition() const; //!< get the position of the hitbox
	const sf::FloatRect getGlobalBounds() const; //!< get the globalbounds of the hitbox
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity); //!< get the next position of the hitbox component

	//Modifiers
	void setPosition(const sf::Vector2f& position); //!< set the position of the hitbox
	void setPosition(const float x, const float y); //!< set the position of the hitbox

	//Functions
	bool Intersects(const sf::FloatRect frect); //!< get the hitboxes intersect

	void update(); //!< update the hitbox
	void render(sf::RenderTarget& target); //!< render the hitbox
};

