#include "Player.h"
#include "Player.h"
#include "Player.h"
#include "Player.h"
#include <iostream>

MobileObject::MobileObject(sf::Vector2f loc, sf::Sprite sprite)
	: Object(loc), m_sprite{sprite}
{}

Player::Player(sf::Vector2f loc, sf::Sprite sprite)
	: MobileObject(loc, sprite)
{}

void Player::move(std::vector<std::vector<std::unique_ptr<Object>>>& board, float deltaTime)
{
	m_needToDoRecursion = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_direction != sf::Vector2f{ -1.f, 0.f })
		{
			int newX = static_cast<int>(m_location.x + 9) / 18;
			int newY = static_cast<int>(m_location.y + 9) / 18;
			newX *= 18;
			newY *= 18;
			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
		}
		m_direction = sf::Vector2f{ -1.f, 0.f };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_direction != sf::Vector2f{ 1.f, 0.f })
		{
			int newX = static_cast<int>(m_location.x + 9) / 18;
			int newY = static_cast<int>(m_location.y + 9) / 18;
			newX *= 18;
			newY *= 18;
			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
		}
		m_direction = sf::Vector2f{ 1.f, 0.f };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_direction != sf::Vector2f{ 0.f, -1.f })
		{
			int newX = static_cast<int>(m_location.x + 9) / 18;
			int newY = static_cast<int>(m_location.y + 9) / 18;
			newX *= 18;
			newY *= 18;
			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
		}
		m_direction = sf::Vector2f{ 0.f, -1.f };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_direction != sf::Vector2f{ 0.f, 1.f })
		{
			int newX = static_cast<int>(m_location.x + 9) / 18;
			int newY = static_cast<int>(m_location.y + 9) / 18;
			newX *= 18;
			newY *= 18;
			m_location = sf::Vector2f{ static_cast<float>(newX), static_cast<float>(newY) };
		}
		m_direction = sf::Vector2f{ 0.f, 1.f };
	}
	else
		m_direction = sf::Vector2f{ 0.f, 0.f };

	int titleSize = 18;
	sf::Vector2f nextLoc = sf::Vector2f(m_location.x + m_direction.x * deltaTime *50,
		m_location.y + m_direction.y * deltaTime*50);
	auto curRow = int(m_location.x) / titleSize;
	auto curCol = int(m_location.y) / titleSize;
	auto nextRow = int(nextLoc.x) / titleSize;
	auto nextCol = int(nextLoc.y) / titleSize;
	if (!board[curRow][curCol]->SavePlace()
		&& board[nextRow][nextCol]->SavePlace())
		m_needToDoRecursion = true;

	m_sprite.move(m_location.x + m_direction.x * deltaTime*50, m_location.y + m_direction.y * deltaTime*50);
	m_location = nextLoc;
}

void Player::draw(sf::RenderWindow& window)
{
	m_sprite.setTextureRect(sf::IntRect(4*18, 0, 18, 18));
	m_sprite.setPosition(m_location);
	window.draw(m_sprite);
}

Enemy::Enemy(sf::Vector2f loc, sf::Sprite sprite)
	: MobileObject(loc, sprite)
{}
//-------------------------------------------------------------------------
void Enemy::move(std::vector<std::vector<std::unique_ptr<Object>>>& board, float deltaTime)
{
	int titleSize = 18;
	sf::Vector2f nextLoc = sf::Vector2f(m_location.x + m_direction.x * deltaTime*50,
		m_location.y + m_direction.y * deltaTime*50);
	auto curRow = int(m_location.x) / titleSize;
	auto curCol = int(m_location.y) / titleSize;
	auto nextRow = int(nextLoc.x) / titleSize;
	auto nextCol = int(nextLoc.y) / titleSize;
	if ( (!board[nextRow][nextCol]->SavePlace()))
	{
		m_location = nextLoc;
	}
	else
	{
		m_direction.x *= -1;
		m_direction.y *= -1;
	}
	m_sprite.move(m_location.x + m_direction.x * deltaTime*50, m_location.y + m_direction.y * deltaTime*50);
	m_location = nextLoc;
}

void Enemy::draw(sf::RenderWindow& window)
{
	m_sprite.setTextureRect(sf::IntRect(6*18, 0, 18, 18));
	m_sprite.setPosition(m_location);
	window.draw(m_sprite);
}

void Enemy::conquer(std::vector<std::vector<std::unique_ptr<Object>>>& board, int row, int col)
{
	if (row >= 24 || col >= 24 || row <= 1 || col <= 1)
		return;
	board[row][col]->conquerable();
	
	/*if (board[row -1][col]->conquerable())
	{
		conquer(board, row - 1, col);
	}*/
	
	if (board[row][col -1]->conquerable())
	{
		conquer(board, row , col -1);
	}
	if (board[row + 1][col]->conquerable())
	{
		conquer(board, row + 1, col);

	}
	if (board[row][col +1]->conquerable())
	{
		conquer(board, row, col + 1);
	}

	//if (grid[y][x] == 0)
		//        grid[y][x] = -1;
		//
		//    if (grid[y - 1][x] == 0) 
		//        drop(y - 1, x);
		//
		//    if (grid[y + 1][x] == 0)
		//        drop(y + 1, x);
		//
		//    if (grid[y][x - 1] == 0) 
		//        drop(y, x - 1);
		//
		//    if (grid[y][x + 1] == 0)
		//        drop(y, x + 1);

}
