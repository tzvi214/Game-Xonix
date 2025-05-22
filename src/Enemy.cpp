#include "Enemy.h"
Enemy::Enemy(sf::Vector2f location, SfmlManager& SfmlMan) 
	: MobileObject(location, sf::Sprite{SfmlMan.getTilesTex() /*SfmlMan.getEnemyTex()*/ })
{ }

void Enemy::move(std::vector<std::vector<std::unique_ptr<Tile>>>& board, float deltaTime)
{
	sf::Vector2f nextLoc = sf::Vector2f(m_location.x + (m_direction.x * deltaTime * m_speed),
		m_location.y + (m_direction.y * deltaTime * m_speed));
	//if (board[nextLoc.x / (SIZE::TILE_SIZE)][nextLoc.y / (SIZE::TILE_SIZE)]->isSave()) //if its save location changed direction
	//{
	//	
	//	if (m_direction == Diagonals::UpLeft)
	//		m_direction = Diagonals::UpRight;

	//	else if (m_direction == Diagonals::UpRight)
	//		m_direction = Diagonals::DownRight;

	//	else if (m_direction == Diagonals::DownRight)
	//		m_direction = Diagonals::DownLeft;

	//	else if (m_direction == Diagonals::DownLeft)
	//		m_direction = Diagonals::UpLeft;
	//	//else// unexcepted direction
	//	//	m_direction = Diagonals::UpLeft;
	//	nextLoc = sf::Vector2f(m_location.x + (m_direction.x * deltaTime * m_speed),
	//		m_location.y + (m_direction.y * deltaTime * m_speed));
	//}

	//else
	//{
	//	m_sprite.move(m_direction.x * deltaTime * m_speed, m_direction.y * deltaTime * m_speed);
	//}


	if (m_direction == Diagonals::UpLeft ) {
		if (board[nextLoc.x / (SIZE::TILE_SIZE)][nextLoc.y / (SIZE::TILE_SIZE)]->isSave()) {
			m_direction = Diagonals::UpRight;
		}
	}
	else if (m_direction == Diagonals::UpRight) {
		if (board[nextLoc.x / (SIZE::TILE_SIZE)][nextLoc.y / (SIZE::TILE_SIZE)]->isSave()) {
	     	m_direction = Diagonals::DownRight;
	     }
	}
	else if (m_direction == Diagonals::DownRight)
	{
		if (board[(nextLoc.x / (SIZE::TILE_SIZE)) + 1][(nextLoc.y / (SIZE::TILE_SIZE))+1]->isSave()) {
			m_direction = Diagonals::DownLeft;
		}
	}
	else if (m_direction == Diagonals::DownLeft) {

		if (board[(nextLoc.x / (SIZE::TILE_SIZE)) + 1][(nextLoc.y / (SIZE::TILE_SIZE)) + 1]->isSave()) {
			m_direction = Diagonals::UpLeft;
		}
	}
	sf::Vector2f nextLocation = sf::Vector2f(m_location.x + (m_direction.x * deltaTime * m_speed),
		m_location.y + (m_direction.y * deltaTime * m_speed));
	m_location = nextLocation;

	//if() if enemy toch the trail player liife --
}


void Enemy::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	m_sprite.setTextureRect(sf::IntRect(2 * SIZE::TILE_SIZE , 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));
	window.draw(m_sprite);
}
