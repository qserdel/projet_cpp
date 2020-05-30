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

using namespace sf;

#define NB_BALLES 5 // Nombre de balles par personnage sur une frame


class Jeu {

	private :
			Map map;
			RenderWindow window;
			Robot rob;
			Robot rob2;
			Texture pvBlue;
			Texture pvRed;
			Sprite spritesPv1[PV_MAX];
			Sprite spritesPv2[PV_MAX];
			Collision collision;
			Balle tabBalles[10];
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
		//void playMusic();


};
#endif
