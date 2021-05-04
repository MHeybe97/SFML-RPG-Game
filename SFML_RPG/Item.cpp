/**\file Item.cpp*/
#include "stdafx.h"
#include "Item.h"


void Item::initVariables()
{
}

Item::Item(unsigned level, unsigned value)
{
	this->initVariables();

	this->value = 0;
	this->type = ItemTypes::ITEM_DEFAULT;
}


Item::~Item()
{
}
