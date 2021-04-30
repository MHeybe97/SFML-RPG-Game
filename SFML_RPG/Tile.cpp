/**\Tile.cpp*/
#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(int grid_x, int grid_y,float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type)
{
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->shape.setTexture(texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}


Tile::~Tile()
{
}

const bool & Tile::getCollision() const
{
	return this->collision;
}

const sf::Vector2f & Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}


//Functions

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
	return ss.str();
}

const short & Tile::getType() const
{
	return this->type;
}


void Tile::update()
{
	
}

void Tile::render(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f player_Position )
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("light", player_Position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}



