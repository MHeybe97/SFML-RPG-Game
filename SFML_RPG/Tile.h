/**\file Tile.h*/
#pragma once
#include "Gui.h"

enum TileType {DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER};

class Tile
{
private:

protected:
	sf::Sprite shape;
	bool collision;
	short type;
public:
	Tile();
	Tile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		const bool collision = false);
	virtual ~Tile();

	//Accessors
	const bool& getCollision() const;
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const std::string getAsString() const = 0;
	virtual const short& getType() const;

	//Functions
	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_Position = sf::Vector2f()) = 0;
};

