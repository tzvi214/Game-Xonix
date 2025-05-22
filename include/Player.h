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
	sf::Vector2f m_direction ={1.f, -1.f};
	sf::Sprite m_sprite;
};
class Player : public MobileObject
{
  public:
	  Player(sf::Vector2f, sf::Sprite);
	  virtual void move(std::vector<std::vector<std::unique_ptr<Object>>>&, float) override ;
	  virtual void draw(sf::RenderWindow&);
	  virtual bool SavePlace() override { return true; }
	  bool needToDoRecursion() const { return m_needToDoRecursion; }
	  virtual bool conquerable() override { return false; }
	  sf::Vector2f getLocation() const { return m_location; }

private:
	sf::Vector2f m_lastLocation = { 0, 0};
	int m_life = 3;
	bool m_needToDoRecursion = false;
};

class Enemy: public MobileObject
{
public:
	virtual bool SavePlace() override { return true; }

	Enemy(sf::Vector2f, sf::Sprite);
	virtual void move(std::vector<std::vector<std::unique_ptr<Object>>>&, float) override ;
	virtual void draw(sf::RenderWindow&);
	void conquer(std::vector<std::vector<std::unique_ptr<Object>>>&,int ,int);
	virtual bool conquerable() override { return false; }
	sf::Vector2f getLocation() const { return m_location; }


private:
	sf::Vector2f m_lastLocation = { 0, 0 };
};
//
//#pragma once
//#include "MobileObject.h"
//
//class Player : public MobileObject
//{
//public:
//	Player(sf::Vector2f location, SfmlManager& SfmlMan);
//	virtual ~Player() = default;
//	virtual void draw(sf::RenderWindow&) override;
//	// virtual void move(std::vector<std::unique_ptr<Tile>>&, float) override;
//	virtual void move(float) override;
//};