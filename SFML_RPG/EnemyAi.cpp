/**\file Enemy.cpp*/
#include "stdafx.h"
#include "EnemyAi.h"

EnemyAi::EnemyAi(Entity& self, Entity& entity)
	: AIOption(self, entity)
{

}


EnemyAi::~EnemyAi()
{
}

void EnemyAi::update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec.x = entity.getPosition().x - self.getPosition().x;
	moveVec.y = entity.getPosition().y - self.getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
	moveVec /= vecLength;

	if ((self.getPosition().x != entity.getPosition().x) && std::abs(vecLength) < 500.f)
		self.move(moveVec.x, moveVec.y, dt);
}
