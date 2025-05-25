#include "EmptyTile.h"

EmptyTile::EmptyTile(sf::Vector2f location, SfmlManager& SfmlMan) : Tile(location, sf::Sprite{ SfmlMan.getTilesTex() }) {}

void EmptyTile::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	m_sprite.setTextureRect(sf::IntRect(0, 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));
	window.draw(m_sprite);
	m_visited = false; //new loop
}