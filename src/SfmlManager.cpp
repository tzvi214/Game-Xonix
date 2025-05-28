#include "SfmlManager.h"

SfmlManager::SfmlManager()
{
	// Load textures and font

	if (!m_tilesTex.loadFromFile("tiles.png"))
	{
		throw std::runtime_error("Failed to load tiles texture");
	}
	if (!m_enemyTex.loadFromFile("enemy.png"))
	{
		throw std::runtime_error("Failed to load enemy texture");
	}
	if (!m_gameOverTex.loadFromFile("gameover.png"))
	{
		throw std::runtime_error("Failed to load game over texture");
	}
	if (!m_font.loadFromFile("CENSCBK.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}
}