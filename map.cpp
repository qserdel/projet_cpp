#include "map.hpp"

Map::Map() : timerMap(TIMER_MAP)
{
	if(!fond.loadFromFile("images/fond.jpg",IntRect(100, 300, 1000, 1000)))
      exit(EXIT_FAILURE);
    spriteFond.setTexture(fond);
    spriteFond.setPosition(Vector2f(0.f, 0.f));

    if(!mur.loadFromFile("images/mur.jpg"))
      exit(EXIT_FAILURE);
    spriteSol.setTexture(mur);
    spriteSol.setTextureRect(IntRect(0, 0, 1000, 50));
    spriteSol.setPosition(Vector2f(0.f, POS_SOL));
    creation_objets();
}


void Map::creation_objets()
{
	srand(time(NULL));
	Sprite obj(mur);
	for (int i = 0; i < 3; i++)
	{
		obj.setTextureRect(IntRect(0, 0, 50, 50));
		obj.setPosition(Vector2f(rand()%950, rand()%(POS_SOL-300)+135));
		objets.push_back(obj);
	}
	obj.setPosition(Vector2f(100, 550));
	objets.push_back(obj);
}

void Map::ajoutCollectable()
{
	srand(time(NULL));
	int alea = rand() % NB_COLLECTABLE;
	switch(alea)
	{
		case 0:
			{
				Bouclier b;
				c.push_back(b.getSprite());
			}
			break;
		case 1:
			{
				Grandir g;
				c.push_back(g.getSprite());
			}
			break;
		case 2:
			{
				Rapetisser r;
				c.push_back(r.getSprite());
			}
			break;
		default:
			break;
	}
}

void Map::updateMap()
{
	timerMap--;
	if(timerMap <= 0)
	{
		ajoutCollectable();
		timerMap = TIMER_MAP;
	}
}

void Map::ajouterSpriteListeCollec(Sprite sp)
{
	c.push_back(sp);
}


Sprite Map::getSpriteSol() const {return spriteSol;};
Sprite Map::getSpriteFond() const {return spriteFond;};
vector<Sprite> Map::getListObjets() const {return objets;};
vector<Sprite> Map::getListCollec() const {return c;};
void Map::setListCollec(Sprite sp, int i) { c[i] = sp;};


IntRect Map::getRectObj(int indice) const
{
    IntRect rectObj;
    rectObj.left = objets[indice].getPosition().x;
    rectObj.width = objets[indice].getPosition().x + objets[indice].getLocalBounds().width * objets[indice].getScale().x;
    rectObj.top = objets[indice].getPosition().y;
    rectObj.height = objets[indice].getPosition().y + objets[indice].getLocalBounds().height * objets[indice].getScale().y;
    return rectObj;
}

IntRect Map::getRectColl(int indice) const
{
    IntRect rectC;
    rectC.left = c[indice].getPosition().x;
    rectC.width = c[indice].getPosition().x + c[indice].getLocalBounds().width * c[indice].getScale().x;
    rectC.top = c[indice].getPosition().y;
    rectC.height = c[indice].getPosition().y + c[indice].getLocalBounds().height * c[indice].getScale().y;
    return rectC;
}


