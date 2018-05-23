#include "crane.hpp"

CCrane::CCrane(const unsigned width, const unsigned height, const std::string title) : IMGPATH_CRANE("assets/crane.png"), IMGPATH_HOOK("assets/hook.png")
{
	m_width = width;
	m_height = height;
	
	m_window.create(sf::VideoMode(m_width, m_height), title, sf::Style::Close);
	
	if (!getSprites())
	{
		std::cout << "Nie mozna wczytac obrazow\n";
		m_window.close();
	}
}

void CCrane::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		m_window.clear(sf::Color(255, 255, 255));
		refresh();
		m_window.display();
	}
}

void CCrane::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;
		}
	}
}

void CCrane::refresh()
{
	m_window.draw(m_craneSprite);
	m_window.draw(m_hookSprite);
}

bool CCrane::getSprites()
{
	if (!m_craneTexture.loadFromFile(IMGPATH_CRANE))
	{
		return false;
	}
	
	m_craneSprite.setPosition(m_width - m_craneTexture.getSize().x - 50, 50);
	m_craneSprite.setTexture(m_craneTexture);
	
	if (!m_hookTexture.loadFromFile(IMGPATH_HOOK))
	{
		return false;
	}
	
	m_hookSprite.setPosition(m_craneSprite.getPosition().x + 10, m_craneSprite.getPosition().y + 145);
	m_hookSprite.setTexture(m_hookTexture);
	
	return true;
}
