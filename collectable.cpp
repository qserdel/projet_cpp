#include "collectable.hpp"


Collectable::Collectable() : action_imediate(false)
{
	srand(time(NULL));
	sp.setPosition(Vector2f(rand()%950, 0));
}

Collectable::Collectable(int n) : action_imediate(false)
{
	number = n;
	srand(time(NULL));
	sp.setPosition(Vector2f(rand()%950, 0));
}		


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

