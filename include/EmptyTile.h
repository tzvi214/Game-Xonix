#pragma once 
#include "Tile.h"

class EmptyTile : public Tile
{
public:
	virtual bool isSave() override { return false; }
	EmptyTile(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~EmptyTile() = default;
	virtual void draw(sf::RenderWindow&) override;
	virtual bool isExists() override { return true; }
	virtual bool shouldRecurseInto() override {  return true;  }
	virtual void updateVisit() override { m_visited = true; };
	virtual bool iVisited() override { return m_visited; }

private:
};