#include "rapetisser.hpp"


Rapetisser::Rapetisser() : Collectable()
{
	if (!txt.loadFromFile("images/R.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

