#ifndef GRANDIR_HPP
#define GRANDIR_HPP
#include "collectable.hpp"


class Grandir : public Collectable {

	protected :


	public :

		Grandir();
		
		virtual void activation(Robot &r);
		
		virtual ~Grandir();

};
#endif
