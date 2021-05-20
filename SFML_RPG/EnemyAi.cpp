/**\file Enemy.cpp*/
#include "stdafx.h"
#include "EnemyAi.h"

//Constructor
//! HitboxComponent class constructor
	/*!
	\param self an Entity obj - the ai entity
	\param entity an entity obj - the player entity
	*/
EnemyAi::EnemyAi(Entity& self, Entity& entity)
	: AIOption(self, entity)
{

}

//Destructor
//! HitboxComponent class destructor
	/*!
	\
	*/
EnemyAi::~EnemyAi()
{
}

//! Function to calculate the enemy ai behaviour
	/*!
	\param dt  a float - update the ai using delta time
	*/
void EnemyAi::update(const float& dt)
{
	// a vector2f moveVec veriable for the distance between the two entities
	sf::Vector2f moveVec; 
	// decreae the distance between them by taking away the values of their positions
	moveVec.x = entity.getPosition().x - self.getPosition().x;
	moveVec.y = entity.getPosition().y - self.getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
	moveVec /= vecLength;

	if ((self.getPosition().x != entity.getPosition().x) && std::abs(vecLength) < 500.f)
		self.move(moveVec.x, moveVec.y, dt);
}
