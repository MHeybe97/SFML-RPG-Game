/**\file Enemy.h*/
#pragma once
#include "AIOption.h"

class EnemyAi : public AIOption
{
public:
	EnemyAi(Entity& self, Entity& entity);
	virtual ~EnemyAi();

	//Functions
	void update(const float& dt);
};

