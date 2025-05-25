#pragma once
#include "Object.h"
#include "Tile.h"

class Enemy;
class Player;

class MobileObject : public Object
{
public:
	MobileObject(sf::Vector2f location, sf::Sprite sprite);
	virtual ~MobileObject() = default;
	virtual void move(std::vector<std::vector<std::unique_ptr<Tile>>>&, float) = 0;
	virtual void move(float) = 0;

	// --- Double Dispatch ---
	virtual void handleCollision(MobileObject&) =0;
	virtual void handleCollision(Enemy&) =0;
	virtual void handleCollision(Player&) =0;

	virtual bool checkCollision(const sf::Sprite&);
protected:
  sf::Vector2f m_direction{ -1.f,-1.f };
};