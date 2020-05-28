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
			c.push_back(*(new Bouclier));
			break;

		case 1:
			c.push_back(*(new Grandir));
			break;

		case 2:
			c.push_back(*(new Rapetisser));
			break;

		case 3:
			c.push_back(*(new Reparer));
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

void Map::ajouterSpriteListeCollec(Collectable cnew)
{
	c.push_back(cnew);
}

void Map::supprimerCollec(int indice)
{
	c.erase(c.begin() + indice);
}

void Map::setPosCollec(float x, float y, int indice)
{
	c[indice].setPos(x, y);
}

void Map::moveCollec(Vector2f v, int indice)
{
	c[indice].move(v);
}



Sprite Map::getSpriteSol() const { return spriteSol; };
Sprite Map::getSpriteFond() const { return spriteFond; };
Sprite Map::getSpriteCollec(int indice) const { return c[indice].getSprite(); };
bool Map::getSpriteStable(int i) const { return c[i].getSpriteStable(); };
vector<Sprite> Map::getListObjets() const { return objets; };
vector<Collectable> Map::getListCollec() const { return c; };
void Map::setListCollec(Collectable cnew, int i) { c[i] = cnew; };
void Map::setSpriteStable(bool a, int i) { c[i].setSpriteStable(a); };


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
    rectC.left = c[indice].getSprite().getPosition().x;
    rectC.width = c[indice].getSprite().getPosition().x + c[indice].getSprite().getLocalBounds().width * c[indice].getSprite().getScale().x;
    rectC.top = c[indice].getSprite().getPosition().y;
    rectC.height = c[indice].getSprite().getPosition().y + c[indice].getSprite().getLocalBounds().height * c[indice].getSprite().getScale().y;
    return rectC;
}


