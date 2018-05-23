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
				
		sf::RenderWindow m_window;
		sf::Texture m_craneTexture;
		sf::Sprite m_craneSprite;
		
		void processEvents();
		void refresh();	
		bool getSprites();
};

#endif // CRANE_HPP
