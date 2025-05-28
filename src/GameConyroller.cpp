#include "GameController.h"
#include "Enemy.h"
#include "Player.h"
#include "EmptyTile.h"
#include "FilledTile.h"
#include "TrailTile.h"
#include "Utility.h"

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

GameController::GameController() : m_information(m_sfmlManager)
{
	try
	{
		updateInfoFromFile();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown error occurred while reading the file." << std::endl;

	}
	
	initBoard();
	initWindow();
}

void GameController::run()
{
	while (readLevels()) // read the levels from the file
	{
		m_clock.restart();

		while (m_window.isOpen()) //  game Main loop
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
			}
			moveObj();
			drawBoard();
			
			if (m_information.robotDied())
			{
				drawGameOver();
				return;
			}
			else if (finishedThisLevel())
			{
				std::cout << "\n you finished The level\n";
				m_window.close();

				initBoard();
				initWindow();
				break;
			}
		}
	}

}

void GameController::moveObj()
{
	float deltaTime = m_clock.restart().asSeconds();

	for (int i = 0; i < m_MobileVec.size(); ++i)
	{
		m_MobileVec[i]->move(m_TileVec, deltaTime);
	}
	handleCollisionControler();

}

void GameController::handleCollisionControler()
{
	for (int i = 0; i < m_MobileVec.size(); i++)
		for (int j = 0; j < m_MobileVec.size(); j++)
		{
			if (i != j)
			{
				m_MobileVec[i]->handleCollision(*m_MobileVec[j]);
			}
		}

	for (int i = 0; i < m_MobileVec.size(); i++)
	{
		m_MobileVec[i]->updateInformation(m_information);
	}
}

void GameController::updateInfoFromFile()
{
	m_fileLevels.open("def.txt");
	if (!m_fileLevels.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	int rows, cols, life;

	// Read the first line
	std::string line;
	std::getline(m_fileLevels, line);
	std::stringstream ss(line);
	ss >> rows >> cols >> life;
	if (ss.fail())
	{
		std::string errorMsg = "this First line: " + line + "\n need to enter {row col life} \n";
		throw std::runtime_error(errorMsg);
	}

	m_information.setTilesPerRow(rows);
	m_information.setTilesPerCol(cols);
	m_information.setLife(life);
}

void GameController::initBoard()
{
	// I want to line the board with empty tiles and the frame with solid tiles.
	
	int col = m_information.getTilesPerCol();
	int row = m_information.getTilesPerRow();
	m_TileVec.clear();
	//m_MobileVec.resize(1 + m_information.getnumEnemy()); // 1 for player + num enemy.
	// i changhed the resize of row and col
	m_TileVec.resize(row);
	for (int i = 0; i < row; ++i)
	{
		m_TileVec[i].resize(col);

		for (int j = 0; j < col; ++j)
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


	m_MobileVec.clear();
	m_MobileVec.push_back(std::make_unique<Player>(sf::Vector2f(0 * SIZE::TILE_SIZE, 0 * SIZE::TILE_SIZE), m_sfmlManager));
	m_MobileVec.push_back(std::make_unique<Enemy>(sf::Vector2f(5 * SIZE::TILE_SIZE, 2 * SIZE::TILE_SIZE), m_sfmlManager));

}

void GameController::initWindow()
{
	int WidthWindow = SIZE::TILE_SIZE * m_information.getTilesPerCol();
	int HeightWindow = SIZE::TILE_SIZE * m_information.getTilesPerRow();
	m_window.create(sf::VideoMode(WidthWindow, HeightWindow + SIZE::TOOLBAR_SIZE), "Game Xonix!");
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

	m_information.draw(m_window); // draw the information on the screen

	m_window.display();
}

bool GameController::readLevels()
{
	std::cout << "\nreading from file \n";
	//The line will contain the percentage of closed area required to win and the number of enemies
	std::string line;
	if (!std::getline(m_fileLevels, line))
	{
		std::cerr << "Error reading line from file" << std::endl;
		return false;
	}

	std::stringstream ss(line);
	int closePrecent, numEnemy;
	ss >> closePrecent >> numEnemy;
	if (ss.fail())
	{
		std::string errorMsg = "this line: " + line + "\n need to enter {closePrecent numEnemy} \n";
		throw std::runtime_error(errorMsg);
	}
	m_information.setClosePrecent(closePrecent);
	m_information.setNumEnemy(numEnemy);
	m_information.setLevel(); // Increment the level

	return true;
}

bool GameController::finishedThisLevel()
{
	double boardSize = m_information.getTilesPerCol() * m_information.getTilesPerRow();
	double percent = 0.5;
	double  occupied = 0;
	for (int i = 0; i < m_information.getTilesPerRow(); i++)
		for (int j = 0; j < m_information.getTilesPerRow(); j++)
			if (m_TileVec[i][j]->isSave())
				occupied++;

	m_information.setClosePrecent((occupied / boardSize)*100);
	return occupied >= (boardSize * percent);
}

void GameController::drawGameOver()
{
	sf::Sprite gameOver(m_sfmlManager.getGameOverTex());
	m_window.draw(gameOver);
	m_window.display();
	std::this_thread::sleep_for(std::chrono::seconds(2));
}
