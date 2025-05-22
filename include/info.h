#pragma once

class Information
{
public:
	Information() = default;
	void setTilesPerRow(int tilesPerRow) { m_tilesPerRow = tilesPerRow; }
	void setTilesPerCol(int tilesPerCol) { m_tilesPerCol = tilesPerCol; }
	void setNumEnemy(int numEnemy) { m_numEnemy = numEnemy; }
	int getTilesPerRow() const { return m_tilesPerRow; }
	int getTilesPerCol() const { return m_tilesPerCol; }
	int getnumEnemy() const { return m_numEnemy; }

private:
	int m_tilesPerRow;
	int m_tilesPerCol;
	int m_numEnemy;
};