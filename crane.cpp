#include "crane.hpp"

CCrane::CCrane(const unsigned width, const unsigned height, const std::string title)
: IMGPATH_CRANE("assets/crane.png"), IMGPATH_HOOKCONTROL("assets/hookcontrol.png"), IMGPATH_HOOK("assets/hook.png"), 
  IMGPATH_KEYS("assets/arrows.png")
{
	m_width = width;
	m_height = height;
	m_groundLevel = m_height - 10;
	m_highlightAlpha = 150;
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	m_window.create(sf::VideoMode(m_width, m_height), title, sf::Style::Close, settings);
	m_window.setFramerateLimit(120);
	
	if (!loadSprites())
	{
		std::cout << "Nie mozna wczytac obrazow\n";
		m_window.close();
	}	
	
	setupSprites();
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
	m_window.clear(sf::Color::White);
	
	for (int i = 0; i < m_keySprites.size(); i++)
	{
		m_window.draw(m_keySprites[i]);
	}	
	
	m_window.draw(m_craneSprite);
	m_window.draw(m_hookControlSprite);
	m_window.draw(m_hookSprite);
	m_window.draw(m_hookRope);
	m_window.draw(m_block.shape);
	
	m_window.display();
}

void CCrane::update()
{
	for (int i = 0; i < m_keySprites.size(); i++)
	{
		if (m_keySprites[i].getColor().a == m_highlightAlpha)
		{
			m_keySprites[i].setColor(sf::Color::White);
		}
	}
	
	int deltaX = 0;
	int deltaY = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_hookControlSprite.getPosition().x > m_craneSprite.getPosition().x + 10)
		{			
			deltaX -= 1;
		}
		
		m_keySprites[Key::LEFT].setColor(sf::Color(255, 255, 255, m_highlightAlpha));		
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_hookControlSprite.getPosition().x < m_craneSprite.getPosition().x + 350)
		{			
			deltaX += 1;
		}
		
		m_keySprites[Key::RIGHT].setColor(sf::Color(255, 255, 255, m_highlightAlpha));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_hookSprite.getPosition().y > m_hookControlSprite.getPosition().y + m_hookControlTexture.getSize().y)
		{			
			deltaY -= 1;
		}
		
		m_keySprites[Key::UP].setColor(sf::Color(255, 255, 255, m_highlightAlpha));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if ((!m_block.isSuspended && m_hookSprite.getPosition().y < m_groundLevel) || (m_block.isSuspended && (m_block.shape.getPosition().y + m_block.shape.getSize().y) < m_groundLevel))
		{		
			deltaY += 1;
		}
		
		m_keySprites[Key::DOWN].setColor(sf::Color(255, 255, 255, m_highlightAlpha));
	}

	sf::FloatRect ropeRect = m_hookRope.getGlobalBounds();
	sf::FloatRect hookRect = m_hookSprite.getGlobalBounds();
	ropeRect.left += deltaX;
	ropeRect.top += deltaY;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{	
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
		
		if (m_block.isSuspended)
		{
			m_block.isSuspended = false;
		}
		else if (m_block.collidesWith(hookRect))
		{
			m_block.isSuspended = true;
		}
		
		m_keySprites[Key::SPACE].setColor(sf::Color(255, 255, 255, m_highlightAlpha));
	}
	
	hookRect.left += deltaX;
	hookRect.top += deltaY;
	
	if (deltaX != 0 && (!(m_block.collidesWith(hookRect) || m_block.collidesWith(ropeRect)) || m_block.isSuspended))
	{
		m_hookControlSprite.move(deltaX, 0);
		m_hookSprite.move(deltaX, 0);
		m_hookRope.move(deltaX, 0);
		
		if (m_block.isSuspended)
		{
			m_block.shape.move(deltaX, 0);
		}
	}
	
	if (deltaY != 0 && (!m_block.collidesWith(ropeRect) || m_block.isSuspended))
	{
		m_hookSprite.move(0, deltaY);
		m_hookRope.setSize(sf::Vector2f(2.0, m_hookSprite.getPosition().y - m_hookControlSprite.getPosition().y - m_hookControlTexture.getSize().y));
		
		if (m_block.isSuspended)
		{
			m_block.shape.move(0, deltaY);
		}
	}
	
	if(!m_block.isSuspended && (m_block.shape.getPosition().y + m_block.shape.getSize().y + m_block.velocity) < m_groundLevel)
	{
		m_block.velocity += m_block.acceleration/120.0;
		m_block.shape.move(0, m_block.velocity);		
	}
	else
	{
		m_block.velocity = 0;
	}
}

bool CCrane::loadSprites()
{
	return (m_craneTexture.loadFromFile(IMGPATH_CRANE) && m_hookControlTexture.loadFromFile(IMGPATH_HOOKCONTROL) && m_hookTexture.loadFromFile(IMGPATH_HOOK)
		&& m_keysTexture.loadFromFile(IMGPATH_KEYS));
}

void CCrane::setupSprites()
{
	m_craneSprite.setPosition(m_width - m_craneTexture.getSize().x - 50, m_groundLevel - m_craneTexture.getSize().y);
	m_craneSprite.setTexture(m_craneTexture);
	
	m_hookControlSprite.setPosition(m_craneSprite.getPosition().x + 10, m_craneSprite.getPosition().y + 147);
	m_hookControlSprite.setTexture(m_hookControlTexture);
	
	m_hookSprite.setPosition(m_hookControlSprite.getPosition().x + 10, m_craneSprite.getPosition().y + 177);
	m_hookSprite.setTexture(m_hookTexture);
	
	m_hookRope.setPosition(m_hookControlSprite.getPosition().x + m_hookControlTexture.getSize().x/2 - 1, m_hookControlSprite.getPosition().y + m_hookControlTexture.getSize().y);
	m_hookRope.setFillColor(sf::Color::Black);
	
	for (int i = 0; i < 5; i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_keysTexture);
		if(i == 4)
		{
			sprite.setTextureRect(sf::IntRect(248, 0, 332, 62));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(i*62, 0, 62, 62));
		}

		m_keySprites.push_back(sprite);
	}
	
	m_keySprites[Key::LEFT].setPosition(10, m_height - 72);
	m_keySprites[Key::UP].setPosition(77, m_height - 139);
	m_keySprites[Key::RIGHT].setPosition(144, m_height - 72);
	m_keySprites[Key::DOWN].setPosition(77, m_height - 72);
	m_keySprites[Key::SPACE].setPosition(221, m_height - 72);
	
	m_block.shape.setSize(sf::Vector2f(50,50));
	m_block.shape.setPosition(700, m_groundLevel - m_block.shape.getSize().y);
	m_block.shape.setFillColor(sf::Color::Black);
	m_block.mass = 50.0;
	m_block.acceleration = 9.81;
	m_block.velocity = 0;
	m_block.isSuspended = false;
}
