#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include "parametres.hpp"

class Joueur {

	protected:
		int ID;
	
	public:
		Joueur();
		Joueur(int id);
		virtual ~Joueur();
		
		virtual Touche detect_Choix() = 0;
		
};
#endif
