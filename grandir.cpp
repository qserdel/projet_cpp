#include "grandir.hpp"


Grandir::Grandir() : Collectable()
{
	if (!txt.loadFromFile("images/grandir.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}


void Grandir::activation(Robot &r)
{
	if (r.getEnPleinRapetissement() == true)
    	r.setEnPleinRapetissement(false);
	if (r.getTaille() == PETIT)
	 	r.setTimerPetit(TIMER_PETIT);
	r.setEnPleinGrandissement(true);
	r.setMaxScale(2);
}


Grandir::~Grandir()
{}
