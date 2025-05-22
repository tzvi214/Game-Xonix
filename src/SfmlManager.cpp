#include "SfmlManager.h"

SfmlManager::SfmlManager()
{
	m_tilesTex.loadFromFile("tiles.png");
	m_enemyTex.loadFromFile("enemy.png");
	m_gameOverTex.loadFromFile("gameover.png");
}