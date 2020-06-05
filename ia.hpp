#ifndef IA_HPP
#define IA_HPP
#include "joueur.hpp"

class Ia : public Joueur {

	protected:
	
	
	public:
		Ia();
		Ia(int id);
		virtual ~Ia();
		
		virtual Touche detect_Choix();
		
};
#endif
