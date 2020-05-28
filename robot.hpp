#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "equipement.hpp"
#include "arme.hpp"
#include <iostream>
#include "collectable.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

#define NI 18 // Nombre d'images dans un sens (robot profil droit par exemple)

#define HAUTEUR_ROBOT 135
#define LARGEUR_ROBOT 100
#define TAILLE_WINDOW 1000

#define GRAVITE -10
#define POS_SOL 700

#define TIMER_BLESSE 50
#define TIMER_PETIT 200
#define TIMER_GRAND 200

enum {NORMAL, WALK_LEFT, WALK_RIGHT, DOWN, PETIT, STANDARD, GRAND, BLESSE, TIRER};


class Robot {

	private :
		string _name;
		int ID;
		Texture texture[34];
		Texture robotActuel;
		int pv=10;
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
		float min_scale = 0.5;
		float max_scale = 2;
		int increment_left = 0;
		float taillePrec = 0;
		bool direction; //true vers la droite, false vers la gauche

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

		void setPv(int nbVie);
		void setNbFrame(int nbreF);
		void setRobotActuel(Texture robAct);
		void setStatus(int etat);
		void setTimerBlesse(int t);
		void setPosSprite(float x, float y);
		void setEnPleinJump(bool a);
		void setHauteurSaut(int h);
		void setTextRect(float w, float h);


};
#endif
