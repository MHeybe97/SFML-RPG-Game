/**\file Tile.h*/
#pragma once
#include "Gui.h"

enum TileType {DEFAULT = 0, DAMAGING};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;
public:
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileType::DEFAULT);
	virtual ~Tile();

	//Functions
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};

