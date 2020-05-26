#ifndef JEU_HPP
#define JEU_HPP
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "map.hpp"

class Jeu {

	private :
			Map map;
			sf::Window window;
			Robot rob1=Robot("Joueur1");
			Robot rob2=Robot("Joueur2");

	public :

		Jeu();
		int play();


};
#endif
