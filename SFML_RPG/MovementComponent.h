/**\file MovementComponent.h*/
#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN}; //!< enum for different positions to move

/*!\class MovementComponent
\brief a class to handle all the games movement
*/
class MovementComponent
{
private:
	//Variables
	sf::Sprite& sprite; //!< the sprite to be moved

	float maxVelocity; //!< max velocity when moving
	float acceleration; //!< acceleratin when moving 
	float deceleration; //!< decelartion after accelerting

	sf::Vector2f velocity; //!< movement velocity


public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration); //!<MovementComponent Constructor
	virtual ~MovementComponent(); //!<MovmentComponent Destructor 

	//Accessors
	const float& getMaxVelocity() const; //!<return the max velocity
	const sf::Vector2f& getVelocity() const; //!<return velocity

	//Functions
	const bool getState(const short unsigned state) const; //!<the state the entity is moving in
	void stopVelocity(); //!<stop all velocity 
	void stopVelocityX(); //!<stop velocity in the x-axis
	void stopVelocityY(); //!<stop velocity in the y-axis
	

	void move(const float dir_x, const float dir_y, const float& dt); //!<move entity
	void update(const float& dt); //!<update movements
};
