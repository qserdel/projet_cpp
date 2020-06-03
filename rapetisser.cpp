#include "rapetisser.hpp"


Rapetisser::Rapetisser() : Collectable()
{
	if (!txt.loadFromFile("images/rapetisser.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

void Rapetisser::activation(Robot &r)
{
	r.setEnPleinRapetissement(true);
	r.setMinScale(0.5);
}

Rapetisser::~Rapetisser()
{}
