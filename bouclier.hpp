#ifndef BOUCLIER_HPP
#define BOUCLIER_HPP
#include <cmath>
#include "collectable.hpp"


class Bouclier : public Collectable {

	protected :


	public :

		Bouclier();
		virtual void activation(Robot &r);
		static sf::CircleShape formationBouclier(Robot &rob);
		
		virtual ~Bouclier();

};
#endif
