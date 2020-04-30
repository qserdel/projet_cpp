#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "forme.hpp"
#include "equipement.hpp"
#include "arme.hpp"
#include <iostream>
#include "collectable.hpp"
#include <SFML/Graphics.hpp>

#define HAUTEUR_ROBOT 10
#define LARGEUR_ROBOT 5 //TODO à définir plus tard

#define VITESSE_MAX 3
#define TAILLE_MAX 3


class Robot {

	private :
		string _name;
		Forme *_forme;
		int pv;
		Arme arme;
		Equipement equipement;
		int x, y; // Coordonnées du coin supérieur gauche du sprite du robot
		float vitesse;
		int taille;
		
		Sprite sprite;

	public :
	
		Robot();

		Robot(string name);
		
		
		void message();
		void move(Event e, Texture *texture, Texture *robotActuel, int *compteur, Sprite *sprite);
		void tirer();
		void ramasser(Collectable* c);
		void gagner_pv();
		void perdre_pv();
		void accelerer();
		void ralentir();
		void grandir();
		void rapetisser();
		void chargement_image(Texture *t);


};
#endif
