/**\file TileMap.h*/
#pragma once
#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	int layers;
	std::vector<std::vector<std::vector<Tile*> > > map;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	//Accessors 
	const sf::Texture* getTileSheet() const;

	//Functions 
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void updateCollision(Entity* entity, const float& dt);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL); 
};

