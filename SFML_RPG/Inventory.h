/**\file Inventory.h*/
#pragma once
#include "Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned nrOfItem;
	unsigned capacity;

	void initialize();
	void expand();
	void nullify(const unsigned from = 0);
	void freeMmemory();
public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	//Accessors
	const unsigned& size() const;
	const unsigned& maxSize() const;
	//Modifiers

	//Functions
	void clear();
	const bool empty() const;

	const bool add(Item* item);
	const bool remove(const unsigned index);

	const bool saveToFile(const std::string fileName);
	const bool loadFromFile(const std::string fileName);
};

