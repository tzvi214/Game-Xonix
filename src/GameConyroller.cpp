#include "GameController.h"
#include "Enemy.h"
#include "Player.h"
#include "EmptyTile.h"
#include "FilledTile.h"
#include "TrailTile.h"
#include "Utility.h"
#include <fstream>
#include <iostream>
#include <string>

GameController::GameController()
{}

void GameController::run()
{
	updateInfoFromFile();
	initBoard();
	initWindow();

	// width . height

	while (m_window.isOpen())
	{

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		moveObj();
		drawBoard();
	}
}

void GameController::moveObj()
{
	float deltaTime = m_clock.restart().asSeconds();

	
	/*for (int i = 0; i < m_MobileVec.size(); ++i)
	{
		m_MobileVec[i]->move(deltaTime);
	}*/
	handleCollisionControler();
	for (int i = 0; i < m_MobileVec.size(); ++i)
	{
		m_MobileVec[i]->move(m_TileVec,deltaTime);
	}

}
void GameController::updateInfoFromFile()
{
	std::fstream file("def.txt");
	if (!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	int rows, cols, numEnemy;
	file >> rows >> cols >> numEnemy;
	m_information.setTilesPerRow(rows);
	m_information.setTilesPerCol(cols);
	m_information.setNumEnemy(numEnemy);
}

void GameController::initBoard()
{
	// I want to line the board with empty tiles and the frame with solid tiles.
	int col = m_information.getTilesPerCol();
	int row = m_information.getTilesPerRow();

	//m_MobileVec.resize(1 + m_information.getnumEnemy()); // 1 for player + num enemy.
	m_TileVec.resize(col);
	for (int i = 0; i < col; ++i)
	{
		m_TileVec[i].resize(row);
		for (int j = 0; j < row; ++j)
		{
			if (i == 0 || i == col - 1 || j == 0 || j == row - 1)
			{
				m_TileVec[i][j] = std::make_unique<FilledTile>(sf::Vector2f(i * SIZE::TILE_SIZE, j * SIZE::TILE_SIZE), m_sfmlManager);
			}
			else
			{
				m_TileVec[i][j] = std::make_unique<EmptyTile>(sf::Vector2f(i * SIZE::TILE_SIZE, j * SIZE::TILE_SIZE), m_sfmlManager);
			}
		}
	}



	//m_MobileVec.resize(1 /*+ m_information.getnumEnemy()*/); // 1 for player + num enemy.
	m_MobileVec.push_back(std::make_unique<Player>(sf::Vector2f(0 * SIZE::TILE_SIZE, 0 * SIZE::TILE_SIZE), m_sfmlManager));
	m_MobileVec.push_back(std::make_unique<Enemy>(sf::Vector2f(11 * SIZE::TILE_SIZE, 12 * SIZE::TILE_SIZE), m_sfmlManager));

}

void GameController::initWindow()
{
	int WidthWindow = SIZE::TILE_SIZE * m_information.getTilesPerCol();
	int HeightWindow = SIZE::TILE_SIZE * m_information.getTilesPerRow();
	m_window.create(sf::VideoMode(WidthWindow, HeightWindow), "Game Xonix!");
	m_window.setFramerateLimit(60);
}

void GameController::drawBoard()
{
	m_window.clear();

	for (int i = 0; i < m_information.getTilesPerCol(); ++i)
	{
		for (int j = 0; j < m_information.getTilesPerRow(); ++j)
		{
			m_TileVec[i][j]->draw(m_window);
		}
	}

	for (int i = 0; i < m_MobileVec.size(); i++)
	{
		m_MobileVec[i]->draw(m_window);
	}

	m_window.display();
}
void GameController::handleCollisionControler()
{
	for(int i =0; i < m_MobileVec.size(); i++)
		for (int j = 0; j < m_MobileVec.size(); j++)
		{
			if (i != j)
			{
				m_MobileVec[i]->handleCollision(*m_MobileVec[j]);
			}
		}
}