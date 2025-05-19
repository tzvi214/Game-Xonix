#pragma once
#include "Object.h"
#include "vector"
#include "memory"
class MobileObject : public Object
{
public:
	MobileObject(sf::Vector2f, sf::Sprite);
	virtual void move(std::vector<std::vector<std::unique_ptr<Object>>>&, float) = 0;
protected:
	sf::Vector2f m_direction ={0, 0};
	sf::Sprite m_sprite;
};
class Player : public MobileObject
{
  public:
	  Player(sf::Vector2f, sf::Sprite);
	  virtual void move(std::vector<std::vector<std::unique_ptr<Object>>>&, float) override {};
private:
	sf::Vector2f m_lastLocation = { 0, 0};
	int m_life = 3;
};

class Enemy: public MobileObject
{
public:

	Enemy(sf::Vector2f, sf::Sprite);
	virtual void move(std::vector<std::vector<std::unique_ptr<Object>>>&, float) override {};
private:
	sf::Vector2f m_lastLocation = { 0, 0 };
};

