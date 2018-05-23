#include "crane.hpp"

CCrane::CCrane(const unsigned width, const unsigned height, const std::string title)
: IMGPATH_CRANE("assets/crane.png"), IMGPATH_HOOKCONTROL("assets/hookcontrol.png"), IMGPATH_HOOK("assets/hook.png")
{
	m_width = width;
	m_height = height;
	
	m_window.create(sf::VideoMode(m_width, m_height), title, sf::Style::Close);
	m_window.setFramerateLimit(120);
	
	if (!loadSprites())
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
		update();
		refresh();
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
	m_window.clear(sf::Color(255, 255, 255));
	m_window.draw(m_craneSprite);
	m_window.draw(m_hookControlSprite);
	m_window.draw(m_hookSprite);
	m_window.draw(m_hookRope);
	m_window.display();
}

void CCrane::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_hookControlSprite.getPosition().x > m_craneSprite.getPosition().x + 10)
	{
		m_hookControlSprite.move(-1, 0);
		m_hookSprite.move(-1, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_hookControlSprite.getPosition().x < m_craneSprite.getPosition().x + 350)
	{
		m_hookControlSprite.move(1, 0);
		m_hookSprite.move(1, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_hookSprite.getPosition().y > m_hookControlSprite.getPosition().y + m_hookControlTexture.getSize().y)
	{
		m_hookSprite.move(0, -1);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_hookSprite.getPosition().y < m_height - 60)
	{
		m_hookSprite.move(0, 1);
	}
	
	m_hookRope.setPosition(sf::Vector2f(m_hookSprite.getPosition().x + 3, m_hookControlSprite.getPosition().y + m_hookControlTexture.getSize().y));
	m_hookRope.setSize(sf::Vector2f(2.0, m_hookSprite.getPosition().y - m_hookControlSprite.getPosition().y - m_hookControlTexture.getSize().y));
}

bool CCrane::loadSprites()
{
	if (!m_craneTexture.loadFromFile(IMGPATH_CRANE) || !m_hookControlTexture.loadFromFile(IMGPATH_HOOKCONTROL) || !m_hookTexture.loadFromFile(IMGPATH_HOOK))
	{
		return false;
	}
	
	m_craneSprite.setPosition(m_width - m_craneTexture.getSize().x - 50, 50);
	m_craneSprite.setTexture(m_craneTexture);
	
	m_hookControlSprite.setPosition(m_craneSprite.getPosition().x + 10, m_craneSprite.getPosition().y + 147);
	m_hookControlSprite.setTexture(m_hookControlTexture);
	
	m_hookSprite.setPosition(m_hookControlSprite.getPosition().x + 10, m_craneSprite.getPosition().y + 177);
	m_hookSprite.setTexture(m_hookTexture);
	
	m_hookRope.setFillColor(sf::Color::Black);
	
	return true;
}
