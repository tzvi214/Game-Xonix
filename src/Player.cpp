#include "Player.h"

MobileObject::MobileObject(sf::Vector2f loc, sf::Sprite sprite)
	: Object(loc), m_sprite{sprite}
{}

Player::Player(sf::Vector2f loc, sf::Sprite sprite)
	: MobileObject(loc, sprite)
{}

Enemy::Enemy(sf::Vector2f loc, sf::Sprite sprite)
	: MobileObject(loc, sprite)
{}
