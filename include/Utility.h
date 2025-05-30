﻿#pragma once
#include <SFML/Graphics.hpp>

enum class TileType
{
	EMPTY,     
	FILLED,    
	BORDER,    
	TRAIL,  
};

namespace SIZE
{
	constexpr int TILE_SIZE = 18; // size of each tile in pixels
	constexpr int HALF_TILE_SIZE = 9;
	constexpr int TOOLBAR_SIZE = 50; // size of the toolbar in pixels
} // namespace Size


namespace Directions
{
	const sf::Vector2f Center{ 0.0f,  0.0f };
	const sf::Vector2f Right{ 1.0f,  0.0f };
	const sf::Vector2f Left{ -1.0f,  0.0f };
	const sf::Vector2f Up{ 0.0f, -1.0f };
	const sf::Vector2f Down{ 0.0f,  1.0f };

}

namespace Diagonals
{
	const sf::Vector2f UpRight{ 1.0f, -1.0f };
	const sf::Vector2f UpLeft{ -1.0f, -1.0f };
	const sf::Vector2f DownRight{ 1.0f, 1.0f };
	const sf::Vector2f DownLeft{ -1.0f, 1.0f };
	const sf::Vector2f Center{ 0.0f, 0.0f };

}
namespace Data {
	const int throwable = 5;
}
