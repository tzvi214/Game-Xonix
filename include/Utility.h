#pragma once
#include <SFML/Graphics.hpp>

enum class TileType
{
	EMPTY,     // ���� ������ �� ����
	FILLED,    // ���� ���� ���� (���� �����)
	BORDER,    // ���� ���� �� ����
	TRAIL,  // ���� ����� ���� �����
};

namespace SIZE
{
	// tile = 20pixel * 20pixel
	constexpr int TILE_SIZE = 18; // size of each tile in pixels
	constexpr int HalfPixelSize = 9;
} // namespace Size


namespace Directions
{
	const sf::Vector2f Center{ 0.0f,  0.0f };
	const sf::Vector2f Right{ 1.0f,  0.0f };
	const sf::Vector2f Left{ -1.0f,  0.0f };
	const sf::Vector2f Up{ 0.0f, -1.0f };
	const sf::Vector2f Down{ 0.0f,  1.0f };

}

//sf::Vector2f ArrangeLocation(const sf::Vector2f& position);