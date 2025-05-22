#include "FilledTile.h"


FilledTile::FilledTile(sf::Vector2f location, SfmlManager& SfmlMan) : Tile(location, sf::Sprite{ SfmlMan.getTilesTex() }) {}

void FilledTile::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	m_sprite.setTextureRect(sf::IntRect(SIZE::TILE_SIZE * 4, 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));
	window.draw(m_sprite);
}