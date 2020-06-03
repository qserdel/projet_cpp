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
#include "menu.hpp"
#include "parametres.hpp"


using namespace sf;

class Jeu {

	private :
			Map map;
			Menu menu;
			RenderWindow window;
			Robot rob;
			Robot rob2;
			sf::Texture pvBlue;
			sf::Texture pvRed;
			sf::Texture victoire1;
			sf::Texture victoire2;
			sf::Sprite spritesPv1[PV_MAX];
			sf::Sprite spritesPv2[PV_MAX];
			sf::Sprite spriteVictoire;
			Collision collision;
			std::vector<Balle*> tabBalles;
			sf::Clock clock;
			float elapsed = 0;
	    	//Music music;

	public :

		Jeu();
		int play();
		void updatePerso(Robot &rob);
		void update();
		void draw();
		void updateMap();
		void gestionTirs(Robot &rob);
		void updateActionRobot(Robot &rob);
		void gestionAttaques(Robot &rob);
		void clearBalles();
		//void playMusic();
		
		std::vector<Balle*> getTab() const {return tabBalles;};
		void setElapsed(float time) {elapsed = time;}; // Pour les tests unitaires uniquement


};
#endif
