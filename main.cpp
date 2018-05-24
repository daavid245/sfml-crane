#include <iostream>
#include "crane.hpp"

int main(int argc, char** argv)
{
	unsigned width = 1400;
	unsigned height = 870;
	std::string title = "Wizualizacja systemow automatyki - dzwig";
	
	CCrane simulation(width, height, title);
	simulation.run();
	
	return 0;
}
