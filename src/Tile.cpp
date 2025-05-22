#include "Tile.h"

Tile::Tile(sf::Vector2f location, sf::Sprite sprite) : 
	     Object(location, sprite), m_visited(false) {}