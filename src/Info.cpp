#include "Info.h"

Information::Information(SfmlManager& SfmlMan) : m_SfmlManager(SfmlMan)
{
}

void Information::draw(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(m_SfmlManager.getFont());
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setString("Life: " + std::to_string(m_life) +
		"    Close Percent: " + std::to_string(m_closePrecent)
		+ "    Level: " + std::to_string(m_level)
		+ "\n               The gool is: " + std::to_string(m_gool) +" Percent");

	// set position of the text 
	auto windowSize = window.getSize();
	float yPos = static_cast<float>(windowSize.y - SIZE::TOOLBAR_SIZE + 10);
	text.setPosition(10.f, yPos);

	window.draw(text);
}