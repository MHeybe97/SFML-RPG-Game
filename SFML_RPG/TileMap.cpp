/**\file TileMap.cpp*/
#include "stdafx.h"
#include "TileMap.h"



TileMap::TileMap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->gridSizeU = 50;
	this->maxSize.x = 1000;
	this->maxSize.y = 1000;
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < maxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile> >());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector<Tile>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile(x *this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
			}
		}
	}
}


TileMap::~TileMap()
{

}

//Functions
void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget & target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				z.render(target);
			}
		}
	}
}


