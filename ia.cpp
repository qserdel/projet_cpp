#include "ia.hpp"

using namespace sf;
using namespace std;

Ia::Ia() : Joueur()
{}

Ia::Ia(int id) : Joueur(id)
{}

Ia::~Ia()
{}

vector<Touche> Ia::detect_Choix() // Reste à remplir selon les envies
{
	vector<Touche> touches;
	touches.push_back(RIEN);
	return touches;
}
