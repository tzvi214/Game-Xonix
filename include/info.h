#pragma once
#include <SFML/Graphics.hpp>
#include "SfmlManager.h"

class Information
{
public:
	Information(SfmlManager&);

	void setTilesPerRow(int tilesPerRow) { m_tilesPerRow = tilesPerRow; }
	void setTilesPerCol(int tilesPerCol) { m_tilesPerCol = tilesPerCol; }
	void setLife(int life) { m_life = life; }
	void setNumEnemy(int numEnemy) { m_numEnemy = numEnemy; }
	void setClosePrecent(int closePrecent) { m_closePrecent = closePrecent; }
	void setLevel() { m_level++; }

	int getTilesPerRow() const { return m_tilesPerRow; }
	int getTilesPerCol() const { return m_tilesPerCol; }
	
	void draw(sf::RenderWindow&);
	void playerDisqualified() { m_life--; }
	bool robotDied() const { return m_life <= 0; }
private:
	int m_tilesPerRow;
	int m_tilesPerCol;
	int m_life ;
	int m_numEnemy;
	int m_closePrecent;
	int m_level = 0;
	SfmlManager& m_SfmlManager;
};