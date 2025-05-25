#include "Enemy.h"
#include "Player.h"
#include "FilledTile.h"
#include "TrailTile.h"
#include "memory"
#include <iostream>

Enemy::Enemy(sf::Vector2f location, SfmlManager& SfmlMan) 
	: MobileObject(location, sf::Sprite{SfmlMan.getTilesTex()}), m_sfmlManager{SfmlMan}
{ }

void Enemy::move(std::vector<std::vector<std::unique_ptr<Tile>>>& board, float deltaTime)
{

	sf::Vector2f nextLoc = sf::Vector2f(m_location.x + (m_direction.x * deltaTime * m_speed),
		m_location.y + (m_direction.y * deltaTime * m_speed));
	
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
	if (m_needRec) { // new i am doing the recursion if i need to 
		rec(board, (m_location.x / SIZE::TILE_SIZE), (m_location.y / SIZE::TILE_SIZE));
		cleanRec(board);
	}
}



void Enemy::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	m_sprite.setTextureRect(sf::IntRect(2 * SIZE::TILE_SIZE , 0, SIZE::TILE_SIZE, SIZE::TILE_SIZE));
	window.draw(m_sprite);
}

void Enemy::handleCollision(MobileObject& other)
{
	other.handleCollision(*this);
}

void Enemy::handleCollision(Player& player)
{
	player.handleCollision(*this);
	if (player.needToDoRecursion())
		m_needRec = true;
}

void Enemy::rec(std::vector<std::vector<std::unique_ptr<Tile>>>& board, int i , int j)
{
	int row = board.size();
	int col = board.at(0).size();
	if (i <= 0 || i >= row || j <= 0 || j >= col) return;//extra check ivean that i dont need it

	if (board[i][j]->shouldRecurseInto() && (!board[i][j]->iVisited())){
		board[i][j]->updateVisit();
	}

	 
	if (i+1 <= row  && board[i +1][j]->shouldRecurseInto() && (!board[i +1][j]->iVisited())) {
		rec(board, i+1, j);
	}
	if (i - 1 >= 0 && board[i - 1][j]->shouldRecurseInto() && (!board[i-1][j]->iVisited())) {
		rec(board, i -1, j);
	}
	if (j + 1 <= row && board[i][j +1]->shouldRecurseInto() && (!board[i][j+1]->iVisited())) {
		rec(board, i , j +1);
	}
	if (j - 1 >= 0 && board[i][j -1]->shouldRecurseInto() && (!board[i][j-1]->iVisited())) {
		rec(board, i, j -1);
	}

}

void Enemy::cleanRec(std::vector<std::vector<std::unique_ptr<Tile>>>& board)
{
	int row = board.size();
	int col = board.at(0).size();
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if  ( board[i][j]->shouldRecurseInto() && (!board[i][j]->iVisited()) ) {
				board[i][j] = std::move(std::make_unique<FilledTile>(sf::Vector2f
					{ static_cast<float>(i * SIZE::TILE_SIZE),  static_cast<float>(j * SIZE::TILE_SIZE) }, m_sfmlManager));
			}
		}
}
