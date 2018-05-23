#ifndef CRANE_HPP
#define CRANE_HPP

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>

class CCrane
{
	public:
		CCrane(const unsigned width, const unsigned height, const std::string title);
		void run();
		
	private:
		unsigned m_width;
		unsigned m_height;
		const std::string IMGPATH_CRANE;
		const std::string IMGPATH_HOOK;
				
		sf::RenderWindow m_window;
		sf::Texture m_craneTexture;
		sf::Texture m_hookTexture;
		sf::Sprite m_craneSprite;
		sf::Sprite m_hookSprite;
		
		void processEvents();
		void refresh();	
		bool getSprites();
};

#endif // CRANE_HPP
