#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "parametres.hpp"

class Joueur {

	protected:
		int ID;
	
	public:
		Joueur();
		Joueur(int id);
		virtual ~Joueur();
		
		virtual std::vector<Touche> detect_Choix() = 0;
		
};
#endif
