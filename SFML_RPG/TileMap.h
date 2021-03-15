/**\file TileMap.h*/
#pragma once
#include "Tile.h"
class TileMap
{
private:
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile> > > map;

public:
	TileMap();
	virtual ~TileMap();
};

