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
#define GRAVITE -10
#define NORMAL 0
#define WALK_RIGHT 1
#define WALK_LEFT 2
#define JUMP 3
#define DOWN 4

class Robot {

	private :
		string _name;
		Texture texture[14];
		Forme *_forme;
		int pv;
		Arme arme;
		Equipement equipement;
		int x, y; // Coordonnées du coin supérieur gauche du sprite du robot
		float vitesse;
		int taille;
		int hauteurSaut;
		int state = NORMAL;
		int nbFrame;
		bool enPleinJump = false;
		bool aGenoux = false;
		
		Sprite sprite;

	public :
	
		Robot();

		Robot(string name);
		
		void detect_KeyPressed();
		void message();
		void move(Robot *rob, Texture *robotActuel, Sprite *sprite, float elapsed);
		void tirer();
		void ramasser(Collectable* c);
		void accelerer();
		void ralentir();
		void grandir();
		void rapetisser();
		void chargement_image();
		void sauter(Robot *rob, Sprite* sprite, float elapsed, Texture *robotActuel);
		
		int getStatus() const;
		int getNbFrame() const;
		int getHauteurSaut() const;
		bool getEnPleinJump() const;
		Texture getTexture(int indice) const;


};
#endif
