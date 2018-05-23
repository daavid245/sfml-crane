#ifndef CRANE_HPP
#define CRANE_HPP

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum Direction
{
	LEFT,
	UP,
	RIGHT,
	DOWN	
};

class CCrane
{
	public:
		CCrane(const unsigned width, const unsigned height, const std::string title);
		void run();
		
	private:
		unsigned m_width;
		unsigned m_height;
		const std::string IMGPATH_CRANE;
		const std::string IMGPATH_HOOKCONTROL;
		const std::string IMGPATH_HOOK;
		const std::string IMGPATH_ARROWS;
				
		sf::RenderWindow m_window;
		
		// textures
		sf::Texture m_craneTexture;
		sf::Texture m_hookControlTexture;
		sf::Texture m_hookTexture;
		sf::Texture m_arrowsTexture;
		
		// sprites 
		sf::Sprite m_craneSprite;
		sf::Sprite m_hookControlSprite;
		sf::Sprite m_hookSprite;
		std::vector<sf::Sprite> m_arrowSprites;
		
		// other
		sf::RectangleShape m_hookRope;
		
		void processEvents();
		void refresh();	
		void update();
		bool loadSprites();
};

#endif // CRANE_HPP
