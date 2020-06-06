#include "rapetisser.hpp"


Rapetisser::Rapetisser() : Collectable()
{
	if (!txt.loadFromFile("images/rapetisser.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

void Rapetisser::activation(Robot &r)
{
	if (r.getEnPleinGrandissement() == true)
    	r.setEnPleinGrandissement(false);
	if (r.getTaille() == GRAND)
	 	r.setTimerGrand(TIMER_GRAND);
	r.setEnPleinRapetissement(true);
	r.setMinScale(0.5);
}

Rapetisser::~Rapetisser()
{}
