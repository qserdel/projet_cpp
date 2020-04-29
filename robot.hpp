#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "forme.hpp"
#include "equipement.hpp"
#include "arme.hpp"
#include <iostream>
#include "collectable.hpp"

#define HAUTEUR_ROBOT 10
#define LARGEUR_ROBOT 5 //TODO à définir plus tard

class Robot {

	private :
		string _name;
		Forme _forme;
		int pv;
		Arme arme;
		Equipement equipement;

	public :

		Robot(string name){
			_name=name;
			if(name=="Joueur1"){
				_forme=Forme(0,0,HAUTEUR_ROBOT,LARGEUR_ROBOT);
			}
			else{
				_forme=Forme(0,1000,HAUTEUR_ROBOT,LARGEUR_ROBOT);
			}
			pv=20;
		}
		void move(const float x, const float y);
		void tirer();
		void ramasser(Collectable* c);
		void gagner_pv();
		void perdre_pv();


};
#endif
