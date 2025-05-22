#pragma once
#include "Tile.h"
//#include "SfmlManager.h"
//שובל
class TrailTile : public Tile
{
public:
	virtual bool isSave() override { return false; }
	TrailTile(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~TrailTile() = default;
	virtual void draw(sf::RenderWindow&) override;

};