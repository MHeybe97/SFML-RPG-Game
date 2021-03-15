/**\file TileMap.h*/
#pragma once
#include "Tile.h"
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile> > > map;

public:
	TileMap();
	virtual ~TileMap();

	//Functions 
	void update();
	void render(sf::RenderTarget& target);
};
