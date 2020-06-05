#ifndef REPARER_HPP
#define REPARER_HPP
#include "collectable.hpp"


class Reparer : public Collectable {

	protected :


	public :

		Reparer();
		
		virtual void activation(Robot &r);
		
		virtual ~Reparer();

};
#endif
