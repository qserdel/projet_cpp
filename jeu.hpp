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


using namespace sf;

class Jeu {

	private :
			Map map;
			Menu menu;
			RenderWindow window;
			Robot rob;
			Robot rob2;
			Texture pvBlue;
			Texture pvRed;
			Texture victoire1;
			Texture victoire2;
			Sprite spritesPv1[PV_MAX];
			Sprite spritesPv2[PV_MAX];
			Sprite spriteVictoire;
			Collision collision;
			vector<Balle> tabBalles;
			Clock clock;
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
		//void playMusic();


};
#endif
