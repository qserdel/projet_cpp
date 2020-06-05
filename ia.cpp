#include "ia.hpp"

using namespace sf;

Ia::Ia() : Joueur()
{}

Ia::Ia(int id) : Joueur(id)
{}

Ia::~Ia()
{}

Touche Ia::detect_Choix() // Reste à remplir selon les envies
{
	return RIEN;
}
