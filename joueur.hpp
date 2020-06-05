#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "parametres.hpp"

class Joueur {

	protected:
		int ID;
		std::vector<Touche*> touches;

	public:
		Joueur();
		Joueur(int id);
		virtual ~Joueur();

		virtual std::vector<Touche*> detect_Choix() = 0;

};
#endif
