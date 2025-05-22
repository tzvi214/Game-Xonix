#pragma once
#include "Tile.h"

class FilledTile : public Tile
{
public:
	FilledTile(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~FilledTile() = default;
	virtual void draw(sf::RenderWindow&) override;

};