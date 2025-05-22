#include "Enemy.h"

Enemy::Enemy(sf::Vector2f location, SfmlManager& SfmlMan) : MobileObject(location, sf::Sprite{ SfmlMan.getEnemyTex() })
{
}

void Enemy::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	//m_sprite.setTextureRect(sf::IntRect(0, 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));
	window.draw(m_sprite);
}
