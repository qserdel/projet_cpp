#ifndef RAPETISSER_HPP
#define RAPETISSER_HPP
#include <SFML/Graphics.hpp>
#include "collectable.hpp"


class Rapetisser : public Collectable {

	public :

		Rapetisser();
		virtual void activation(Robot &r);

		virtual ~Rapetisser();

};
#endif
