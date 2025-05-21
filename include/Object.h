#pragma once
#include <SFML/Graphics.hpp>
#include "GameInfromation.h"

class Object {
public:
   Object(sf::Vector2f); // Fixed spelling and corrected type
   virtual ~Object() = default; // Added virtual destructor for proper cleanup
   virtual void draw(sf::RenderWindow&) = 0; // Added pure virtual function for drawing
   virtual bool SavePlace() = 0; 
   virtual bool exists() { return true; } 
   virtual bool conquerable() = 0;
protected:
	sf::Vector2f m_location; // Fixed spelling and corrected type
};
// tile -> father of the tiles
// emptyTile -> enemysPlace
// trailTile -> щебк
// filledTile -> savtyZone
// 
class Tile : public Object
{
public:
	Tile(sf::Sprite&, sf::Vector2f);	
protected:
	sf::Sprite m_sprite;
};

class EmptyTile :public Tile
{
public:
	EmptyTile(sf::Sprite&, sf::Vector2f);
	virtual void draw(sf::RenderWindow& window) override
	{
		m_sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
		m_sprite.setPosition(m_location);
		window.draw(m_sprite);

	}
	//void killTile() { m_exists = false; } // Added function to kill the tile
	virtual bool SavePlace() override { return false; }
	virtual bool exists() override { return m_exists; } // Added override for exists
	virtual bool conquerable() override 
	{ 
		if (m_exists) {
			m_exists = false;
			return true;
		}
	 return false; }
private:
	bool m_exists = true;
};

class TrailTile :public Tile
{
public:
	TrailTile(sf::Sprite&, sf::Vector2f);
	virtual void draw(sf::RenderWindow& window) override
	{
		m_sprite.setTextureRect(sf::IntRect(18, 0, 18, 18));
		m_sprite.setPosition(m_location);
		window.draw(m_sprite);
	}
	virtual bool SavePlace() override { return false; }
	virtual bool conquerable() override { return true; }
};

class FilledTile : public Tile  
{  
public:  
   FilledTile(sf::Sprite&, sf::Vector2f);  
   virtual bool SavePlace() override { return true; }
   virtual void draw(sf::RenderWindow& window) override
   {
	   m_sprite.setTextureRect(sf::IntRect(18 * 3, 0, 18, 18));
	   m_sprite.setPosition(m_location);
	   window.draw(m_sprite);
   }
   virtual bool conquerable() override { return false; } // Added override for conquerable
};