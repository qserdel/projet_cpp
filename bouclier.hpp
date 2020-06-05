#ifndef BOUCLIER_HPP
#define BOUCLIER_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include "collectable.hpp"


class Bouclier : public Collectable {

	public :

		Bouclier();
		virtual void activation(Robot &r);
		static sf::CircleShape formationBouclier(Robot &rob);

		virtual ~Bouclier();

};
#endif
