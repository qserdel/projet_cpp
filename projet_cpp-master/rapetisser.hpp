#ifndef RAPETISSER_HPP
#define RAPETISSER_HPP
#include "collectable.hpp"


class Rapetisser : public Collectable {

	protected :


	public :

		Rapetisser();
		
		virtual void activation(Robot &r);
		
		virtual ~Rapetisser();

};
#endif
