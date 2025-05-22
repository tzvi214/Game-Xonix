#pragma once
#include "MobileObject.h"
#include "SfmlManager.h"


class Enemy : public MobileObject
{
public:
	virtual void move(std::vector<std::vector<std::unique_ptr<Tile>>>&, float) override {};
	Enemy(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~Enemy() = default;
	virtual void draw(sf::RenderWindow&) override;

};