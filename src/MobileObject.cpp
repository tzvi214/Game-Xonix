#include "MobileObject.h"

MobileObject::MobileObject(sf::Vector2f location, sf::Sprite sprite) 
	: Object(location, sprite)
{}

bool MobileObject::checkCollision(const sf::Sprite& other)
{
	if (m_sprite.getGlobalBounds().intersects(other.getGlobalBounds()))
		return true;
	return false;
}
