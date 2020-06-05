#include "humain.hpp"

using namespace sf;
using namespace std;

Humain::Humain() : Joueur()
{}


Humain::Humain(int id) : Joueur(id)
{}

Humain::~Humain()
{}

Touche Humain::detect_Choix()
{
	if (ID == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Right))
		    return RIGHT;
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		    return LEFT;
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		    return DOWN1;
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		    return UP;
		else if (Keyboard::isKeyPressed(Keyboard::Space))
			return SHOOT;
	}
	else if (ID == 1)
    {
		if (Keyboard::isKeyPressed(Keyboard::D))
			return RIGHT1;
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		    return LEFT1;
		else if (Keyboard::isKeyPressed(Keyboard::S))
		    return DOWN2;
		else if (Keyboard::isKeyPressed(Keyboard::Z))
		    return UP1;
		else if (Keyboard::isKeyPressed(Keyboard::E))
			return SHOOT1;
	}
	return RIEN;
}
