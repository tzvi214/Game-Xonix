#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.h"

class SfmlManager
{
public:
	SfmlManager();
	~SfmlManager() = default;

	sf::Texture& getTilesTex() { return m_tilesTex; }
	sf::Texture& getEnemyTex() { return m_enemyTex; }
	sf::Texture& getGameOverTex() { return m_gameOverTex; }
	sf::Font& getFont() { return m_font; }

private:
	sf::Texture m_tilesTex;
	sf::Texture m_enemyTex;
	sf::Texture m_gameOverTex;
	sf::Font m_font;
};