/**\file AIOption.h*/
#pragma once
#include "Entity.h"

/*!\class AIOption
\brief a base class for the ai entities
*/

class AIOption
{
private:

protected:
	Entity& self; //!< the entity with the ai behaviour
	Entity& entity; //!< the entity to be followed or chased 

public:
	AIOption(Entity& self, Entity& entity)
		: self(self), entity(entity)
	{

	}

	virtual void update(const float& dt) = 0; //!< virtual update function for the ai child class

	
};

