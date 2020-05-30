#include "bouclier.hpp"


Bouclier::Bouclier() : Collectable(BOUCLIER)
{
	if (!txt.loadFromFile("images/bouclier.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

void Bouclier::activation(Robot &r)
{
	r.activerBouclier();
}
