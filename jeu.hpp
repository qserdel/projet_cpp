#ifndef JEU_HPP
#define JEU_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "robot.hpp"
#include "map.hpp"
#include <cstdlib>
#include "balle.hpp"
#include "collision.hpp"
#include "collectable.hpp"
#include "bouclier.hpp"

#define NB_BALLES 5 // Nombre de balles par personnage sur une frame


class Jeu {

	private :
			Map map;
			RenderWindow window;
			Robot rob;
			Robot rob2;
			Collision collision;
			Balle tabBalles[10];
			sf::Clock clock;
    		float elapsed = 0;
    		Bouclier bouclier;
    		//Music music;

	public :

		Jeu();
		int play();
		void updatePerso(Robot &rob);
		void update();
		void draw();
		//void playMusic();


};
#endif


	
