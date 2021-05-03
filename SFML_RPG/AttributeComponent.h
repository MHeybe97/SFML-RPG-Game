/**\file AttributeComponent.h*/
#pragma once
class AttributeComponent
{
private:

public:
	//Leveling 
	int level;
	int exp;
	int expNext;
	int attributePoints;
	
	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	//Con & Dest
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	const bool isDead() const;
	const bool isAlive() const;

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

