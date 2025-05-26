#pragma once
#include "MobileObject.h"
#include "SfmlManager.h"
#include "Utility.h"
class Player;

class Enemy : public MobileObject
{
public:
	Enemy(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~Enemy() = default;
	virtual void draw(sf::RenderWindow&) override;
	virtual void move(std::vector<std::vector<std::unique_ptr<Tile>>>&, float) override;
	virtual void move(float) override {};

	  // --- Double Dispatch ---
	virtual void handleCollision(MobileObject&) override ;
	virtual void handleCollision(Enemy&) override {};
	virtual void handleCollision(Player&) override ;
	
private:
	bool m_killedPlayer = false;
	int m_speed = 50;
	bool m_needRec = false;
	SfmlManager& m_sfmlManager;
	void cleanRec(std::vector<std::vector<std::unique_ptr<Tile>>>&);
	void rec(std::vector<std::vector<std::unique_ptr<Tile>>>&, int, int);
	void choiseLocation(std::vector<std::vector<std::unique_ptr<Tile>>>&, sf::Vector2f);
};