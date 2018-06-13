#ifndef CRANE_HPP
#define CRANE_HPP

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum Key
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	SPACE
};

struct Block
{
	sf::RectangleShape shape;
	double mass;
	double acceleration;
	double velocity;
	bool isSuspended;
	
	
	bool collidesWith(const sf::FloatRect& entity)
	{
		sf::FloatRect rect = shape.getGlobalBounds();
		return rect.intersects(entity);
	}
};

class CCrane
{
	public:
		CCrane(const unsigned width, const unsigned height, const std::string title);
		void run();
		
	private:
		unsigned m_width;
		unsigned m_height;
		unsigned m_groundLevel;
		const std::string IMGPATH_CRANE;
		const std::string IMGPATH_HOOKCONTROL;
		const std::string IMGPATH_HOOK;
		const std::string IMGPATH_KEYS;
		unsigned m_highlightAlpha;

		sf::RenderWindow m_window;
		
		// textures
		sf::Texture m_craneTexture;
		sf::Texture m_hookControlTexture;
		sf::Texture m_hookTexture;
		sf::Texture m_keysTexture;
		
		// sprites 
		sf::Sprite m_craneSprite;
		sf::Sprite m_hookControlSprite;
		sf::Sprite m_hookSprite;
		std::vector<sf::Sprite> m_keySprites;
		
		// other
		sf::RectangleShape m_hookRope;
		Block m_block;
		
		void processEvents();
		void refresh();	
		void update();
		bool loadSprites();
		void setupSprites();
};

#endif // CRANE_HPP
