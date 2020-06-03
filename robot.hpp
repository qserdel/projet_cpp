#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include "parametres.hpp"

enum {NORMAL, WALK_LEFT, WALK_RIGHT, DOWN, PETIT, STANDARD, GRAND, BLESSE, TIRER};


class Robot {

	private :
		std::string _name;
		int ID;
		sf::Texture texture[36];
		sf::Texture robotActuel;
		int pv = PV_MAX;
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
		bool direction; // true vers la droite, false vers la gauche
		bool bouclier = false;
		int nbMunitions;

		sf::Sprite sprite;

	public :

		Robot(std::string name);

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
		sf::Texture getTexture(int indice) const;
		sf::Sprite getSprite() const;
		sf::IntRect getRectRobot() const;
		int getTimerBlesse() const;
		int getPv() const;
		std::string getName() const;
		bool getDirection() const;
		float getX() const;
		float getY() const;
		int getID() const;
		int getTimerTir() const;
		bool getBouclier() const;
		int getMunitions() const;
		int getTimerBouclier() const;
		int getTimerPetit() const;
		int getTimerGrand() const;

		void setPv(int nbVie);
		void setNbFrame(int nbreF);
		void setRobotActuel(sf::Texture robAct);
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
		void setTimerTir(int a);
		void setBouclier(bool a);
		void effacerMunition();
		void setMunitions(int nbM);
		void setTaille(int t);


};
#endif
