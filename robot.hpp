#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "equipement.hpp"
#include "arme.hpp"
#include <iostream>
#include "collectable.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

#define HAUTEUR_ROBOT 135
#define LARGEUR_ROBOT 100

#define VITESSE_MAX 3
#define TAILLE_MAX 3
#define GRAVITE -10

enum {NORMAL, WALK_LEFT, WALK_RIGHT, DOWN, PETIT, GRAND, BLESSE};


class Robot {

	private :
		string _name;
		Texture texture[20];
		Texture robotActuel;
		int pv;
		Arme arme;
		Equipement equipement;
		float vitesse;
		int taille;
		int hauteurSaut;
		int state = NORMAL;
		int nbFrame;
		bool enPleinJump = false;
		bool aGenoux = false;
		bool enPleinGrandissement = false;
		bool enPleinRapetissement = false;
		bool tir = false;
		int timerGrand = 0;
		int timerPetit = 0;
		int timerBlesse = 0;
		float min_scale;
		float max_scale;


		float taillePrec = 0;

		Sprite sprite;

	public :

		//Robot();

		Robot(string name);

		void detect_KeyPressed();
		void message();
		void move(float elapsed);
		void tirer();
		void ramasser(Collectable* c);
		void grandir();
		void rapetisser();
		void chargement_image();
		void sauter(float elapsed);

		// Accesseurs
		int getStatus() const;
		int getNbFrame() const;
		int getHauteurSaut() const;
		bool getEnPleinJump() const;
		bool getEnPleinGrandissement() const;
		bool getEnPleinRapetissement() const;
		bool getTir() const;
		void setTir(bool var);
		float getMinScale() const;
		float getMaxScale() const;
		int getTaille() const;
		Texture getTexture(int indice) const;
		Sprite getSprite() const;
		IntRect getRectRobot() const;
		int getTimerBlesse() const;
		int getPv() const;
		string getName() const;
		void setPv(int nbVie);
		void setNbFrame(int nbreF);
		void setRobotActuel(Texture robAct);
		void setStatus(int etat);
		void setTimerBlesse(int t);


};
#endif
