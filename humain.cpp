#include "humain.hpp"

using namespace sf;
using namespace std;

Humain::Humain() : Joueur()
{}


Humain::Humain(int id) : Joueur(id)
{}

Humain::~Humain()
{}

vector<Touche> Humain::detect_Choix()
{
	vector<Touche> touches;
	if (ID == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Right))
		    touches.push_back(RIGHT);
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		    touches.push_back(LEFT);
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		    touches.push_back(DOWN1);
		
		if (Keyboard::isKeyPressed(Keyboard::Up))
		    touches.push_back(UP);
		
		if (Keyboard::isKeyPressed(Keyboard::Space))
			touches.push_back(SHOOT);
	}
	else if (ID == 1)
    {
		if (Keyboard::isKeyPressed(Keyboard::D))
			touches.push_back(RIGHT1);
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		    touches.push_back(LEFT1);
		else if (Keyboard::isKeyPressed(Keyboard::S))
		    touches.push_back(DOWN2);
		
		if (Keyboard::isKeyPressed(Keyboard::Z))
		    touches.push_back(UP1);
		
		if (Keyboard::isKeyPressed(Keyboard::E))
			touches.push_back(SHOOT1);
	}
	touches.push_back(RIEN);
	return touches;
}
