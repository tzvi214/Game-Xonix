#pragma once
#include "Tile.h"

class TrailTile : public Tile
{
public:
	virtual bool isSafe() override { return false; }
	TrailTile(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~TrailTile() = default;
	virtual void draw(sf::RenderWindow&) override;
	virtual bool isExists() override { return m_exists; }
	virtual bool shouldRecurseInto() override { return false; }
	virtual bool iVisited() override { return true; }

private:
	bool m_exists = false;
};