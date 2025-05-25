//#include "Player.h"
//#include <iostream>
//
//MobileObject::MobileObject(sf::Vector2f loc, sf::Sprite sprite)
//	: Object(loc), m_sprite{sprite}
//{}
//
//Player::Player(sf::Vector2f loc, sf::Sprite sprite)
//	: MobileObject(loc, sprite)
//{}
//
//void Player::move(std::vector<std::vector<std::unique_ptr<Object>>>& board, float deltaTime)
//{
//	m_needToDoRecursion = false;
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//	{
//		if (m_direction != sf::Vector2f{ -1.f, 0.f })
//		{
//			int newX = static_cast<int>(m_location.x + 9) / 18;
//			int newY = static_cast<int>(m_location.y + 9) / 18;
//			newX *= 18;
//			newY *= 18;
//			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
//		}
//		m_direction = sf::Vector2f{ -1.f, 0.f };
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//	{
//		if (m_direction != sf::Vector2f{ 1.f, 0.f })
//		{
//			int newX = static_cast<int>(m_location.x + 9) / 18;
//			int newY = static_cast<int>(m_location.y + 9) / 18;
//			newX *= 18;
//			newY *= 18;
//			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
//		}
//		m_direction = sf::Vector2f{ 1.f, 0.f };
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//	{
//		if (m_direction != sf::Vector2f{ 0.f, -1.f })
//		{
//			int newX = static_cast<int>(m_location.x + 9) / 18;
//			int newY = static_cast<int>(m_location.y + 9) / 18;
//			newX *= 18;
//			newY *= 18;
//			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
//		}
//		m_direction = sf::Vector2f{ 0.f, -1.f };
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//	{
//		if (m_direction != sf::Vector2f{ 0.f, 1.f })
//		{
//			int newX = static_cast<int>(m_location.x + 9) / 18;
//			int newY = static_cast<int>(m_location.y + 9) / 18;
//			newX *= 18;
//			newY *= 18;
//			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
//		}
//		m_direction = sf::Vector2f{ 0.f, 1.f };
//	}
//	else
//		m_direction = sf::Vector2f{ 0.f, 0.f };
//
//	int titleSize = 18;
//	sf::Vector2f nextLoc = sf::Vector2f(m_location.x + m_direction.x * deltaTime *50,
//		m_location.y + m_direction.y * deltaTime*50);
//	auto curRow = int(m_location.x) / titleSize;
//	auto curCol = int(m_location.y) / titleSize;
//	auto nextRow = int(nextLoc.x) / titleSize;
//	auto nextCol = int(nextLoc.y) / titleSize;
//	if (!board[curRow][curCol]->SavePlace()
//		&& board[nextRow][nextCol]->SavePlace())
//		m_needToDoRecursion = true;
//
//	m_sprite.move(m_location.x + m_direction.x * deltaTime*50, m_location.y + m_direction.y * deltaTime*50);
//	m_location = nextLoc;
//}
//
//void Player::draw(sf::RenderWindow& window)
//{
//	m_sprite.setTextureRect(sf::IntRect(4*18, 0, 18, 18));
//	m_sprite.setPosition(m_location);
//	window.draw(m_sprite);
//}
//
//Enemy::Enemy(sf::Vector2f loc, sf::Sprite sprite)
//	: MobileObject(loc, sprite)
//{}
////-------------------------------------------------------------------------
//void Enemy::move(std::vector<std::vector<std::unique_ptr<Object>>>& board, float deltaTime)
//{
//	int titleSize = 18;
//	sf::Vector2f nextLoc = sf::Vector2f(m_location.x + m_direction.x * deltaTime*50,
//		m_location.y + m_direction.y * deltaTime*50);
//	auto curRow = int(m_location.x) / titleSize;
//	auto curCol = int(m_location.y) / titleSize;
//	auto nextRow = int(nextLoc.x) / titleSize;
//	auto nextCol = int(nextLoc.y) / titleSize;
//	if ( (!board[nextRow][nextCol]->SavePlace()))
//	{
//		m_location = nextLoc;
//	}
//	else
//	{
//		m_direction.x *= -1;
//		m_direction.y *= -1;
//	}
//	m_sprite.move(m_location.x + m_direction.x * deltaTime*50, m_location.y + m_direction.y * deltaTime*50);
//	m_location = nextLoc;
//}
//
//void Enemy::draw(sf::RenderWindow& window)
//{
//	m_sprite.setTextureRect(sf::IntRect(6*18, 0, 18, 18));
//	m_sprite.setPosition(m_location);
//	window.draw(m_sprite);
//}
//
//void Enemy::conquer(std::vector<std::vector<std::unique_ptr<Object>>>& board, int row, int col)
//{
//	if (row >= 24 || col >= 24 || row <= 1 || col <= 1)
//		return;
//	board[row][col]->conquerable();
//	
//	/*if (board[row -1][col]->conquerable())
//	{
//		conquer(board, row - 1, col);
//	}*/
//	
//	if (board[row][col -1]->conquerable())
//	{
//		conquer(board, row , col -1);
//	}
//	if (board[row + 1][col]->conquerable())
//	{
//		conquer(board, row + 1, col);
//
//	}
//	if (board[row][col +1]->conquerable())
//	{
//		conquer(board, row, col + 1);
//	}
//
//	//if (grid[y][x] == 0)
//		//        grid[y][x] = -1;
//		//
//		//    if (grid[y - 1][x] == 0) 
//		//        drop(y - 1, x);
//		//
//		//    if (grid[y + 1][x] == 0)
//		//        drop(y + 1, x);
//		//
//		//    if (grid[y][x - 1] == 0) 
//		//        drop(y, x - 1);
//		//
//		//    if (grid[y][x + 1] == 0)
//		//        drop(y, x + 1);
//
//}


#include "Player.h"
#include "Utility.h"
#include "memory"
#include "TrailTile.h"
#include <FilledTile.h>
#include "Enemy.h"


Player::Player(sf::Vector2f location, SfmlManager& SfmlMan) 
	: MobileObject(location, sf::Sprite{ SfmlMan.getTilesTex() }), m_sfmlManager{ SfmlMan }
	, m_firstLocation{ location }
{}

void Player::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	m_sprite.setTextureRect(sf::IntRect(SIZE::TILE_SIZE * 1, 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));
	window.draw(m_sprite);
}


void Player::move(float deltaTime)
{
	// Handle player movement here
	// Example: m_location += speed * deltaTime;

	sf::Vector2f direction{ 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x += 1;
	}

	float speed = 100;
	// m_sprite.move(direction * deltaTime * speed);
	m_location += direction * deltaTime * speed;


}



void Player::move(std::vector<std::vector<std::unique_ptr<Tile>>>& board, float deltaTime)
{
	chooseDirection();
		sf::Vector2f nextLoc = sf::Vector2f(m_location.x + (m_direction.x * deltaTime * m_speed),
			                                m_location.y + (m_direction.y * deltaTime * m_speed));
		int row = board.size();
		int col = board.at(0).size();
		if (nextLoc.x < 0 || (nextLoc.x / SIZE::TILE_SIZE) > row-1) return;
		if (nextLoc.y < 0 || (nextLoc.y / SIZE::TILE_SIZE) > col-1) return;

		checkLocation(board, nextLoc);
		
		
		m_sprite.move(m_location.x + (m_direction.x * deltaTime * m_speed), 
			          m_location.y + (m_direction.y * deltaTime * m_speed));
		m_location = nextLoc;
}
//-------------------------------------
sf::Vector2f Player::ArrangeLocation(sf::Vector2f loc)
{
	int newX = static_cast<int>(loc.x + SIZE::HalfPixelSize) / SIZE::TILE_SIZE;
	int newY = static_cast<int>(loc.y + SIZE::HalfPixelSize) / SIZE::TILE_SIZE;
	newX *= SIZE::TILE_SIZE;
	newY *= SIZE::TILE_SIZE;
	return sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
}
//-------------------------------------
void Player::chooseDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_direction != Directions::Left)
		{
			m_location = ArrangeLocation(m_location);
		}
		m_direction = Directions::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_direction != Directions::Right)
		{
			m_location = ArrangeLocation(m_location);
		}
		m_direction = Directions::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_direction != Directions::Up)
		{
			m_location = ArrangeLocation(m_location);
		}
		m_direction = Directions::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_direction != Directions::Down)
		{
			m_location = ArrangeLocation(m_location);
		}
		m_direction = Directions::Down;
	}
	else
		m_direction = Directions::Center;
}



void Player::handleCollision(MobileObject& other)
{
	other.handleCollision(*this);
}

void Player::handleCollision(Enemy& enemy)
{ 
	if (enemy.checkCollision(m_sprite)) {
		m_life--;
		m_needToDoRecursion = false;
		m_location = m_firstLocation;
		m_needToCleanTrail = true;
		
	}
}

void Player::checkLocation(std::vector<std::vector<std::unique_ptr<Tile>>>& board, sf::Vector2f nextLoc)
{
	if (m_needToCleanTrail) cleanTrail(board);
	if (board[m_location.x / SIZE::TILE_SIZE][m_location.y / SIZE::TILE_SIZE]->isSave() &&
		(!board[nextLoc.x / SIZE::TILE_SIZE][nextLoc.y / SIZE::TILE_SIZE]->isSave()))
	{
		m_inTrailMode = true;
		m_needToDoRecursion = false;
	}
	else if ((!board[m_location.x / SIZE::TILE_SIZE][m_location.y / SIZE::TILE_SIZE]->isSave()) &&
		board[nextLoc.x / SIZE::TILE_SIZE][nextLoc.y / SIZE::TILE_SIZE]->isSave())
	{
		m_inTrailMode = false;
		m_needToDoRecursion = true;
		cleanTrail(board);
	}
	if (m_inTrailMode)
	{
		int newX = static_cast<int>(nextLoc.x);
		int newY = static_cast<int>(nextLoc.y);
		newX -= (newX % SIZE::TILE_SIZE);
		newY -= (newY % SIZE::TILE_SIZE);

		sf::Vector2f lestLoc = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
		if (!board[lestLoc.x / SIZE::TILE_SIZE][lestLoc.y / SIZE::TILE_SIZE]->isSave())
		{
			board[lestLoc.x / SIZE::TILE_SIZE][lestLoc.y / SIZE::TILE_SIZE] = std::move(std::make_unique<TrailTile>
				(lestLoc, m_sfmlManager));

		}
	}
	else
	{
		m_needToDoRecursion = false;
	}


}
//------------------------------------------------------------------------
void Player::cleanTrail(std::vector<std::vector<std::unique_ptr<Tile>>>& board)
{
	//if (!m_needToCleanTrail) return;//double check
	int row = board.size();
	int col = board.at(0).size();
	for(int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if ((!board[i][j]->isExists()))
				board[i][j] = std::move(std::make_unique<FilledTile>(sf::Vector2f
				{ static_cast<float>(i * SIZE::TILE_SIZE),  static_cast<float>(j * SIZE::TILE_SIZE) }, m_sfmlManager));
		}
	m_needToCleanTrail = false;
}
