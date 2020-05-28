#include "grandir.hpp"


Reparer::Reparer() : Collectable()
{
	if (!txt.loadFromFile("images/reparer.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}
