#include "rapetisser.hpp"


Rapetisser::Rapetisser() : Collectable()
{
	if (!txt.loadFromFile("images/rapetisser.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}
