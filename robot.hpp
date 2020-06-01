#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "equipement.hpp"
#include "arme.hpp"
#include "balle.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

#define NI 18 // Nombre d'images dans un sens (robot profil droit par exemple)

#define HAUTEUR_ROBOT 135
#define LARGEUR_ROBOT 100
#define TAILLE_WINDOW 1000 // Taille de la fenêtre de jeu

#define GRAVITE -10
#define POS_SOL 700

#define TIMER_BLESSE 30
#define TIMER_PETIT 300
#define TIMER_GRAND 300
#define TIMER_TIR 30
#define TIMER_BOUCLIER 400

#define PV_MAX 25

enum {NORMAL, WALK_LEFT, WALK_RIGHT, DOWN, PETIT, STANDARD, GRAND, BLESSE, TIRER};


class Robot {

	private :
		string _name;
		int ID;
		Texture texture[36];
		Texture robotActuel;
		int pv = PV_MAX;
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
		int timerGrand = TIMER_GRAND;
		int timerPetit = TIMER_PETIT;
		int timerBlesse = TIMER_BLESSE;
	  	int timerTir = 0;
	  	int timerBouclier = TIMER_BOUCLIER;
		float min_scale = 0.5;
		float max_scale = 2;
		int increment_left = 0;
		float taillePrec = 0;
		bool direction; //true vers la droite, false vers la gauche
		bool bouclier = false;
		int nbMunitions;

		Sprite sprite;

	public :

		Robot(string name);

		void detect_KeyPressed();
		void move(float elapsed);
		void grandir();
		void rapetisser();
		void chargement_image();
		void sauter(float elapsed);
		void blessure();
		void actionBouclier();
		void gestionMunitions();


		// Accesseurs
		int getStatus() const;
		int getNbFrame() const;
		int getHauteurSaut() const;
		bool getEnPleinJump() const;
		bool getEnPleinGrandissement() const;
		bool getEnPleinRapetissement() const;
		float getMinScale() const;
		float getMaxScale() const;
		int getTaille() const;
		int getIncrementLeft() const;
		Texture getTexture(int indice) const;
		Sprite getSprite() const;
		IntRect getRectRobot() const;
		int getTimerBlesse() const;
		int getPv() const;
		string getName() const;
		bool getDirection() const;
		float getX() const;
		float getY() const;
		int getID() const;
		int getTimerTir() const;
		bool getBouclier() const;
		int getMunitions() const;

		void setPv(int nbVie);
		void setNbFrame(int nbreF);
		void setRobotActuel(Texture robAct);
		void setStatus(int etat);
		void setTimerBlesse(int t);
		void setPosSprite(float x, float y);
		void setEnPleinJump(bool a);
		void setHauteurSaut(int h);
		void setTextRect(float w, float h);
		void setEnPleinGrandissement(bool r);
		void setEnPleinRapetissement(bool r);
		void setMinScale(float min);
		void setMaxScale(float max);
		void resetTimerTir();
		void setBouclier(bool a);
		void effacerMunition();
		void setMunitions(int nbM);


};
#endif
