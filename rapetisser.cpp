#include "rapetisser.hpp"


Rapetisser::Rapetisser() : Collectable(RAPETISSER)
{
	if (!txt.loadFromFile("images/rapetisser.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

