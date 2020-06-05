#include "collectable.hpp"

using namespace sf;
using namespace std;

// Constructeurs

Collectable::Collectable() : action_imediate(true)
{
	srand(time(NULL));
	sp.setPosition(Vector2f(rand()%950, 0));
}
		

Collectable::Collectable(Collectable const& copy) : txt(copy.txt), action_imediate(copy.action_imediate), sp(copy.sp), spriteStable(copy.spriteStable)
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
bool Collectable::getSpriteStable() const { return spriteStable; };
void Collectable::setSprite(Sprite s) { sp = s; };
void Collectable::setSpriteStable(bool a) { spriteStable = a; };

