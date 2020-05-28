#include "grandir.hpp"


Grandir::Grandir() : Collectable()
{
	if (!txt.loadFromFile("images/grandir.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}
