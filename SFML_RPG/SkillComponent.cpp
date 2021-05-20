/**\file SkillComponent.cpp*/
#include "stdafx.h"
#include "SkillComponent.h"

//Constructor
//! SkillComponent class constructor
	/*!
	*/
SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(CONSTITUTION));
	this->skills.push_back(Skill(MELEE_COMBAT));
	this->skills.push_back(Skill(ENDURANCE));
}

//Destructor
//! HitboxComponent class destructor
	/*!
	*/
SkillComponent::~SkillComponent()
{
}

//! Function to get skill  
	/*!
	\param skill int - the number of skills in the the skills vector
	*/
const int SkillComponent::getSkill(const int skill) const
{
	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST: " + skill);
	else
		return this->skills[skill].getLevel();
}

//! Function to gain skill exp
	/*!
	\param skill int - the number of skills in the the skills vector
	\param exp an int - skill exp
	*/
const void SkillComponent::gainExp(const int skill, const int exp)
{
	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOES NOT EXIST: " + skill);
	else
	{
		this->skills[skill].gainExp(exp);
	}
}
