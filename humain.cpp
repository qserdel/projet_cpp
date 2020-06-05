#include "humain.hpp"

using namespace sf;
using namespace std;

Humain::Humain() : Joueur()
{}


Humain::Humain(int id) : Joueur(id)
{}

Humain::~Humain()
{}

std::vector<Touche*> Humain::detect_Choix()
{
	Touche t;
	while (!touches.empty())
	{
		delete touches.back();
		touches.pop_back();
	}
	if (ID == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Right))
			t=RIGHT;
		  touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			t=LEFT;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			t=DOWN1;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::Up))
			t=UP;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::Space))
			t=SHOOT;
			touches.push_back(&t);
	}
	else if (ID == 1)
    {
		if (Keyboard::isKeyPressed(Keyboard::D))
			t=RIGHT1;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::Q))
			t=LEFT1;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::S))
			t=DOWN2;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::Z))
			t=UP1;
			touches.push_back(&t);
		if (Keyboard::isKeyPressed(Keyboard::E))
			t=SHOOT1;
			touches.push_back(&t);
	}
	return touches;
}
