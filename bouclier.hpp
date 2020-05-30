#ifndef BOUCLIER_HPP
#define BOUCLIER_HPP
#include <SFML/Graphics.hpp>
#include "collectable.hpp"


class Bouclier : public Collectable {

	protected :


	public :

		Bouclier();
		virtual void activation(Robot &r);
		
		virtual ~Bouclier() {};

};
#endif
