#include "reparer.hpp"


Reparer::Reparer() : Collectable(REPARER)
{
	if (!txt.loadFromFile("images/reparer.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

void Reparer::activation(Robot &r)
{
	r.setPv(r.getPv() + 3);
	if(r.getPv() > PV_MAX)
		r.setPv(PV_MAX);
}
