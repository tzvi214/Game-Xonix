#include "TrailTile.h" // Fix circular include issue by using forward declaration
// Fix circular include issue by using forward declaration  


TrailTile::TrailTile(sf::Vector2f location, SfmlManager& SfmlMan) 
	: Tile(location, sf::Sprite{ SfmlMan.getTilesTex() })  
{ }  

void TrailTile::draw(sf::RenderWindow& window)  
{  
   m_sprite.setPosition(m_location);  
   m_sprite.setTextureRect(sf::IntRect(SIZE::TILE_SIZE * 3, 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));  
   window.draw(m_sprite);  
}