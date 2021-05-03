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
	unsigned value;

public:
	//Variables


	Item(unsigned value);
	virtual ~Item();

	//Functions 
	virtual Item* clone() = 0;
};

