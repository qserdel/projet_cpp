#ifndef GRANDIR_HPP
#define GRANDIR_HPP
#include <SFML/Graphics.hpp>
#include "collectable.hpp"


class Grandir : public Collectable {

	protected :


	public :

		Grandir();
		virtual void activation(Robot &r);
		
		virtual ~Grandir();

};
#endif
