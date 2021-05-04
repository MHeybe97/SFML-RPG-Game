/**\file Item.h*/
#pragma once

enum ItemTypes {ITEM_DEFAULT = 0, ITEM_MELEEWEAPON, ITEM_RANGEDWEAPON};

class Item
{
private:
	void initVariables();
protected:
	//Variables
	short unsigned type;
	unsigned level;
	unsigned value;

public:
	//Variables


	Item(unsigned level, unsigned value);
	virtual ~Item();

	//Functions 
	virtual Item* clone() = 0;
};

