#include "bouclier.hpp"


Bouclier::Bouclier() : Collectable()
{
	if (!txt.loadFromFile("images/bouclier.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}
