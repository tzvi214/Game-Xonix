#pragma once
#include "Object.h"
#include "SfmlManager.h"


class Tile : public Object
{
public:
	Tile(sf::Vector2f location, sf::Sprite sprite);
	virtual ~Tile() = default;

protected:

	bool m_visited;

};
