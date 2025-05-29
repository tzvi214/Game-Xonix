#pragma once
#include "Tile.h"

class FilledTile : public Tile
{
public:
	virtual bool isSafe() override { return true; }
	FilledTile(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~FilledTile() = default;
	virtual void draw(sf::RenderWindow&) override;
	virtual bool isExists() override { return true; }
	virtual bool shouldRecurseInto() override { return false; }
	virtual bool iVisited() override { return true; }

};