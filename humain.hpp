#ifndef HUMAIN_HPP
#define HUMAIN_HPP
#include "joueur.hpp"

class Humain : public Joueur {

	protected:
	
	public:
		Humain();
		Humain(int id);
		virtual Touche detect_Choix();
		
		virtual ~Humain();

};
#endif
