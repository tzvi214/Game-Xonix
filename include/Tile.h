#pragma once
#include "Object.h"
#include "SfmlManager.h"


class Tile : public Object
{
public:
	Tile(sf::Vector2f location, sf::Sprite sprite);
	virtual ~Tile() = default;
	virtual bool isSave() = 0;
	virtual void draw(sf::RenderWindow&) =0;
	virtual bool isExists() = 0;

protected:

	bool m_visited;


};
