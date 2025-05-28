#include "Player.h"
#include "Utility.h"
#include "memory"
#include "TrailTile.h"
#include "EmptyTile.h"
#include <FilledTile.h>
#include "Enemy.h"
#include <iostream>

Player::Player(sf::Vector2f location, SfmlManager& SfmlMan)
	: MobileObject(location, sf::Sprite{ SfmlMan.getTilesTex() }), m_sfmlManager{ SfmlMan }
	, m_firstLocation{ location }
{
}



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
	if (nextLoc.x < 0 || (nextLoc.x / SIZE::TILE_SIZE) > row -1)
	{	
		if (((nextLoc.x / SIZE::TILE_SIZE) >= row - 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || nextLoc.x < 0)
			return;
	}

	if (nextLoc.y < 0 || (nextLoc.y / SIZE::TILE_SIZE) > col -1 )
	{
		if (((nextLoc.y / SIZE::TILE_SIZE) >= col - 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || nextLoc.y < 0)
		   return;
	}
	if (touchTrail(board, nextLoc) || m_touchTrail)
	{
		updateTrail(board);
		return;
	}
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
		setDirection(Directions::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		setDirection(Directions::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		setDirection(Directions::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		setDirection(Directions::Down);
	}
	else if (!m_inTrailMode)// dont stop in trail
	{
		setDirection(Directions::Center);
	}
}

void Player::handleCollision(MobileObject& other)
{
	other.handleCollision(*this);
}

void Player::handleCollision(Enemy& enemy)
{

	if (enemy.checkCollision(m_sprite)) {
		m_playerDisqualified = true;
		m_needToDoRecursion = false;
		m_location = m_firstLocation;
		m_needToCleanTrail = false;
		m_touchTrail = true;

	}
}

void Player::checkLocation(std::vector<std::vector<std::unique_ptr<Tile>>>& board, sf::Vector2f nextLoc)
{
	if (m_touchTrail) updateTrail(board);
	if (m_needToCleanTrail) cleanTrail(board);
	m_needToDoRecursion = false;

	if (board[m_location.x / SIZE::TILE_SIZE][m_location.y / SIZE::TILE_SIZE]->isSave() &&
		(!board[nextLoc.x / SIZE::TILE_SIZE][nextLoc.y / SIZE::TILE_SIZE]->isSave()))
	{
		m_inTrailMode = true;// if i went from safety place to not savty place
		
	}

	if (m_inTrailMode)
	{
		if(!board[nextLoc.x / SIZE::TILE_SIZE][nextLoc.y / SIZE::TILE_SIZE]->isSave())// i am still nat in savty place
		{ 
			int newTileX = static_cast<int>(nextLoc.x);
			int newTileY = static_cast<int>(nextLoc.y);
				
			newTileX -= (newTileX % SIZE::TILE_SIZE);
			newTileY -= (newTileY % SIZE::TILE_SIZE);
			sf::Vector2f newTileLoc = sf::Vector2f{ static_cast<float>(newTileX), static_cast<float>(newTileY) };
			board[nextLoc.x / SIZE::TILE_SIZE][nextLoc.y / SIZE::TILE_SIZE] = std::move(std::make_unique<TrailTile>
				(newTileLoc, m_sfmlManager));
		//std::cout << "\nnew i am nat in savty place i am chinging it to trail\n";

		}
		else 
		{
			m_inTrailMode = false;
			m_needToDoRecursion = true;
			m_needToCleanTrail = true;
			//cleanTrail(board);
			//std::cout << "\nnew i am save agin i am doing rec and cleaning the trail\n";

		}
	}
	
}
//------------------------------------------------------------------------
void Player::cleanTrail(std::vector<std::vector<std::unique_ptr<Tile>>>& board)
{
	//if (!m_needToCleanTrail) return;//double check
	int row = board.size();
	int col = board.at(0).size();
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if ((!board[i][j]->isExists()))
				board[i][j] = std::move(std::make_unique<FilledTile>(sf::Vector2f
					{ static_cast<float>(i * SIZE::TILE_SIZE),  static_cast<float>(j * SIZE::TILE_SIZE) }, m_sfmlManager));
		}
	m_needToCleanTrail = false;
}

void Player::updateTrail(std::vector<std::vector<std::unique_ptr<Tile>>>& board)
{
	int row = board.size();
	int col = board.at(0).size();
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if ((!board[i][j]->isExists()))
				board[i][j] = std::move(std::make_unique<EmptyTile>(sf::Vector2f
					{ static_cast<float>(i * SIZE::TILE_SIZE),  static_cast<float>(j * SIZE::TILE_SIZE) }, m_sfmlManager));
		}
	
	m_touchTrail = false;
	m_inTrailMode = false;
	m_needToDoRecursion = false;
	m_playerDisqualified = true;
	m_location = m_firstLocation;
}

bool Player::touchTrail(std::vector<std::vector<std::unique_ptr<Tile>>>& board, sf::Vector2f newLocation)
{ 
	if (!m_inTrailMode) return false;

		if (!board[(m_location.x / (SIZE::TILE_SIZE)) + m_direction.x][(m_location.y / (SIZE::TILE_SIZE)) + m_direction.y]->isExists())
			return true;

	return false;

}

void Player::setDirection(sf::Vector2f newDirection)
{
	if (m_direction.x == newDirection.x && m_direction.y == newDirection.y)
	{
		return;
	}
	else   // direction changed but didnt stopt
	{
		//to move to the place nicely
		// its nat will look like jumping  
		if (newDirection.x || newDirection.y) // didnt stoppt
		{
			if (m_direction.x + newDirection.x == 0 || m_direction.y + newDirection.y == 0)// Reverse direction change immediately
			{
				m_direction = newDirection;
				return;
			}
		}

		if ((static_cast<int>(m_location.x) % SIZE::TILE_SIZE) > Data::throwable ||
			(static_cast<int>(m_location.y) % SIZE::TILE_SIZE) > Data::throwable)
		{
			return;
		}

		m_location = ArrangeLocation(m_location);
		m_direction = newDirection;
		//std::cout << "jumping \n";
	}

}
//-----------------------------------------------
void Player::updateInformation(Information& info)
{
	if (m_playerDisqualified)
	{
		info.playerDisqualified();
		m_playerDisqualified = false;
	}
}