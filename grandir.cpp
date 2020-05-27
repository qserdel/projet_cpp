#include "grandir.hpp"


Grandir::Grandir() : Collectable()
{
	if (!txt.loadFromFile("images/R.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

