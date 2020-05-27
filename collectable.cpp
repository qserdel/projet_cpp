#include "collectable.hpp"


Collectable::Collectable() : action_imediate(false)
{
	srand(time(NULL));
	sp.setPosition(Vector2f(rand()%950, 0));
}
		
		
		
		
		
void Collectable::apparition()
{
	
}


Sprite Collectable::getSprite() {return sp;};
