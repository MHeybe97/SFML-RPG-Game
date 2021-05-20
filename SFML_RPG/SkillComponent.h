/**\file SkillComponent.h*/
#pragma once

enum SKILLS {CONSTITUTION = 0, MELEE_COMBAT, ENDURANCE }; //!<enum for different skills

/*!\class SkillComponent
\brief a class to handle entity skills
*/
class SkillComponent
{
private:
	/*!\class Skill
    \brief a class to handle entity skills
   */
	class Skill
	{
	private:
		int type; //!<type of skill
		int level; //!<skill level
		int levelCap; //!<skill level cap
		int exp; //!< exp gained from skill
		int expNext; //!< next exp to be gained

	public:
		//Constructor
        //! SkillComponent class constructor
	    /*!
	    \param type an int - the type of skill
	   */
		Skill(int type)
		{
			this->level = 1; 
			this->levelCap = 99;
			this->exp = 0;
			this->expNext = 100;
		}

		//Destructor
        //! HitboxComponent class destructor
	    /*!
	    \
	   */
		~Skill() {}

		//Accessors
		inline const int& getType() const { return this->type; } //!< return skill type
		inline const int& getLevel() const { return this->level; } //!< return level
		inline const int& getExp() const { return this->exp; } //!<return exp
		inline const int& getExpNext() const { return this->expNext;} //!<return expNext

		//Modifiers
		void setLevel(const int level) { this->level = level; } //!< set the skill level
		void setLevelCap(const int level_cap) {} //!< set the levlcap

		//Functions 
		//! Function to gain skill exp when the level is updated
	    /*!
	    \param exp an int - the exp gained from the skillComponent
	   */
		void gainExp(const int exp) 
		{ 
			this->exp += exp; 
			this->updateLevel(); 
		}

		//! Function to lose skill exp 
		/*!
		\param exp an int - the exp lost 
	   */
		void loseExp(const int exp)
		{
			this->exp -= exp;
		}

		//! Function to update skill level
		/*!
		\return a boolean for when leveling up
	   */
		void updateLevel(const bool up = true)
		{
			//if leveling up
			if (up)
			{
				//if level is less than levelcap
				if (this->level < this->levelCap)
				{
					//while exp is more than or equal to the next exp 
					while (this->exp >= this->expNext)
					{
						//level is less the levelcap
						if (this->level < this->levelCap)
						{
							//increment the the level
							this->level++;
							//calculate the next exp goal
							this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
			else 
				//if level is more than 0
				if (this->level > 0)
				{
					//while exp is less than 0
					while (this->exp < 0)
					{
						//if the level > 0 
						if (this->level > 0)
						{
							//decrement the level
							this->level--;
							//calclate the next exp
							this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2;
						}
					}
				}

		}

		void update()
		{

		}
	};

	std::vector<Skill> skills; //!< vector of skills

public:
	SkillComponent(); //!< skillcomp constructor
	virtual ~SkillComponent(); //!<skillcomp destructor

	//Accessors
	const int getSkill(const int index) const; //!< return skill

	//FUNCTIONS
	const void gainExp(const int skill, const int exp); //!< gain skill exp
};

