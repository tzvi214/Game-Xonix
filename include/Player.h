#pragma once
#include "MobileObject.h"
#include "SfmlManager.h"
class Enemy;
class Player : public MobileObject
{
public:
	Player(sf::Vector2f location, SfmlManager& SfmlMan);
	virtual ~Player() = default;
	virtual void updateInformation(Information&) override;
	virtual void draw(sf::RenderWindow&) override;
	virtual void move(std::vector<std::vector<std::unique_ptr<Tile>>>&, float) override ;
	bool needToDoRecursion() const { return m_needToDoRecursion; }

	   // --- Double Dispatch ---
	virtual void handleCollision(MobileObject&) override ;
	virtual void handleCollision(Enemy&) override ;
	virtual void handleCollision(Player&) override {};
	void cleanTrail() { m_touchTrail = true; m_playerDisqualified = true; }
private:
	const sf::Vector2f m_firstLocation;
	SfmlManager& m_sfmlManager;
	sf::Vector2f ArrangeLocation(sf::Vector2f);
	void chooseDirection();
	void checkLocation(std::vector<std::vector<std::unique_ptr<Tile>>>&, sf::Vector2f);
	void cleanTrail(std::vector<std::vector<std::unique_ptr<Tile>>>&);
	void updateTrail(std::vector<std::vector<std::unique_ptr<Tile>>>&);
	bool touchTrail(std::vector<std::vector<std::unique_ptr<Tile>>>&, sf::Vector2f);
	void setDirection(sf::Vector2f);
	bool m_touchTrail = false;
	int m_speed = 200;
	bool m_inTrailMode = false;
	bool m_needToDoRecursion = false;
	bool m_needToCleanTrail = false;
	int m_life = 5;
	bool m_playerDisqualified = false;
};