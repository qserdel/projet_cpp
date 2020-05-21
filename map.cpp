#include "map.hpp"

Map::Map()
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




Sprite Map::getSpriteSol() const {return spriteSol;};
Sprite Map::getSpriteFond() const {return spriteFond;};
vector<Sprite> Map::getListObjets() const {return objets;};

IntRect Map::getRectObj(int indice) const
{
    IntRect rectObj;
    rectObj.left = objets[indice].getPosition().x;
    rectObj.width = objets[indice].getPosition().x + objets[indice].getLocalBounds().width * objets[indice].getScale().x;
    rectObj.top = objets[indice].getPosition().y;
    rectObj.height = objets[indice].getPosition().y + objets[indice].getLocalBounds().height * objets[indice].getScale().y;
    return rectObj;
}
