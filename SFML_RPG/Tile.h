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
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileType::DEFAULT);
	virtual ~Tile();

	//Accessors
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;
	const short& getType() const;

	//Functions
	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_Position = sf::Vector2f());
};

