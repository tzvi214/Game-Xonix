#pragma once
#include "SFML/Graphics.hpp"
#include "Utility.h"
#include "SfmlManager.h"

class Object
{
public:
	Object(sf::Vector2f location, sf::Sprite sprite) : m_location(location), m_sprite(sprite) {
		m_sprite.setPosition(m_location);
	}
	virtual ~Object() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	
protected:

	sf::Vector2f m_location;
	sf::Sprite m_sprite;
};