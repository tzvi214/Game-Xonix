#pragma once
#include "Object.h"
#include "SfmlManager.h"


class Tile : public Object
{
public:
	Tile(sf::Vector2f location, sf::Sprite sprite);
	virtual ~Tile() = default;
	virtual bool isSafe() = 0;
	virtual void draw(sf::RenderWindow&) =0;
	virtual bool isExists() = 0;
	virtual bool shouldRecurseInto() = 0;
	virtual bool iVisited() = 0;
	virtual void updateVisit() {};
	virtual bool checkCollision(const sf::Sprite&);

protected:

	bool m_visited;


};
