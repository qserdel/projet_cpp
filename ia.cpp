#include "ia.hpp"

using namespace sf;

Ia::Ia() : Joueur()
{}

Ia::Ia(int id) : Joueur(id)
{}

Ia::~Ia()
{}

std::vector<Touche*> Ia::detect_Choix() // Reste à remplir selon les envies
{
	Touche t;
	while (!touches.empty())
	{
		delete touches.back();
		touches.pop_back();
	}
	t=RIEN;
	touches.push_back(&t);
	return touches;
}
