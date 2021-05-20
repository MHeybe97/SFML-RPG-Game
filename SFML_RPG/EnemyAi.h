/**\file Enemy.h*/
#pragma once
#include "AIOption.h"

/*!\class EnemyAi
\brief a class to handle all the games ai behaviour 
*/

class EnemyAi : public AIOption
{
public:
	EnemyAi(Entity& self, Entity& entity); //!< constructor
	virtual ~EnemyAi(); //!< destructor

	//Functions
	void update(const float& dt); //!< update the enemy behaviour
};

