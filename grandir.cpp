#include "grandir.hpp"


Grandir::Grandir() : Collectable(GRANDIR)
{
	if (!txt.loadFromFile("images/grandir.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

