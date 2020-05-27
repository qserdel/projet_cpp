#include "bouclier.hpp"


Bouclier::Bouclier() : Collectable()
{
	if (!txt.loadFromFile("images/bouclier.jpg"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

