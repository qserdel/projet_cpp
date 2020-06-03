#include "collectable.hpp"

using namespace sf;
using namespace std;

// Constructeurs

Collectable::Collectable() : action_imediate(false)
{
	srand(time(NULL));
	sp.setPosition(Vector2f(rand()%950, 0));
}
		

Collectable::Collectable(Collectable const& copy) : txt(copy.txt), sp(copy.sp), number(copy.number), spriteStable(copy.spriteStable)
{}

Collectable::~Collectable()
{}

// Méthodes

void Collectable::move(Vector2f v)
{
	sp.move(v);
}

void Collectable::setPos(float x, float y)
{
	sp.setPosition(x, y);
}


Sprite Collectable::getSprite() const { return sp; };
int Collectable::getNumber() const { return number; };
bool Collectable::getSpriteStable() const { return spriteStable; };
void Collectable::setSprite(Sprite s) { sp = s; };
void Collectable::setSpriteStable(bool a) { spriteStable = a; };

