/**\file AttributeComponent.h*/
#pragma once
class AttributeComponent
{
private:

public:
	//Leveling 
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;
	
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
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;
	void gainEXP(const unsigned exp);
	const bool isAlive() const;
	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

