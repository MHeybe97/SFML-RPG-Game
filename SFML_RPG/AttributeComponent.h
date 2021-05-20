/**\file AttributeComponent.h*/
#pragma once

/*! \class Animation
\brief a class to handle all stats and leveling of the games entities like the player and enemies
*/
class AttributeComponent
{
private:

public:
	//Leveling 
	int level; //!< level for all entities in the game i.e player and enemy
	int exp; //!< the players experiance points
	int expNext; //!< the experiance points needed to level up
	int attributePoints; //! entities attribute points
	
	//Attributes
	int vitality; //!< entities vitality
	int strength; //!< entities strength
	int dexterity; //!< entities dexterity
	int agility; //!< entities agility
	int intelligence; //!< entities intelligence

	//Stats
	int hp; //!< entities helth points
	int hpMax; //!< entities max health points
	int damageMin; //!< minimum damage to be dealt
	int damageMax; //!< maximum damage to be dealt
	int accuracy; //!< entities accuracy
	int defence; //!< entities defence
	int luck; //!< entities  luck

	//Con & Dest
	AttributeComponent(int level); //!< AttributeComponent constructor
	virtual ~AttributeComponent(); //!< AttributeComponent destructor

	//Functions
	std::string debugPrint() const; //!< debug text to be printed on the screen

	void loseHP(const int hp); //!< function to decrease hp
	void gainHP(const int hp); //!< function to increase hp
	void loseEXP(const int exp); //!< function to lose experiance points
	void gainEXP(const int exp); //!< function to gain experiance points

	const bool isDead() const; //!< function to check if hp is less than or equal to 0
	const bool isAlive() const; //!< function to check if hp is less than or equal to 0

	void updateStats(const bool reset); //1< function to update entity stats
	void updateLevel(); //!< function update the player level

	void update(); //!< update levels
};

