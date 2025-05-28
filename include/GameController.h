#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>

#include "Tile.h"
#include "SfmlManager.h"
#include "info.h"
#include "MobileObject.h"

class GameController
{
public:
	GameController();
	void run();

private:
	SfmlManager m_sfmlManager;
	Information m_information;
	sf::RenderWindow m_window;
	std::fstream m_fileLevels;

	using TileVec = std::vector<std::unique_ptr<Tile>>;
	using MobileVec = std::vector<std::unique_ptr<MobileObject>>;

	std::vector<std::vector<std::unique_ptr<Tile>>> m_TileVec;
	std::vector<std::unique_ptr<MobileObject>> m_MobileVec;
	sf::Clock m_clock;

	void moveObj();
	void handleCollisionControler();
	void updateInfoFromFile();
	void initBoard();
	void initWindow();
	void drawBoard();
	bool readLevels();
	bool finishedThisLevel();
	void drawGameOver();
};