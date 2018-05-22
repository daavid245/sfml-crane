#include "crane.hpp"

CCrane::CCrane(const unsigned width, const unsigned height, const std::string title)
{
	m_width = width;
	m_height = height;
	
	m_window.create(sf::VideoMode(m_width, m_height), title, sf::Style::Close);
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
	// todo
}
