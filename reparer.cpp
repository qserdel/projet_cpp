#include "reparer.hpp"


Reparer::Reparer() : Collectable(REPARER)
{
	if (!txt.loadFromFile("images/reparer.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}
