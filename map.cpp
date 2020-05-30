#include "map.hpp"

Map::Map(int i) : timerMap(TIMER_MAP)
{
	index=i;
	switch(index){
		case 1:
			if(!fond.loadFromFile("images/fond.jpg",IntRect(100, 300, 1000, 1000)))
      			exit(EXIT_FAILURE);
    		spriteFond.setTexture(fond);

			if(!mur.loadFromFile("images/mur.jpg"))
		  		exit(EXIT_FAILURE);
			spriteSol.setTexture(mur);
			spriteSol.setTextureRect(IntRect(0, 0, 1000, 50));
			spriteSol.setPosition(Vector2f(0.f, POS_SOL));
			creation_objets();
		break;
		case 2:
			if(!fond.loadFromFile("images/fond2.png",IntRect(0, 0, 1000, 1000)))
				exit(EXIT_FAILURE);
			spriteFond.setTexture(fond);

			if(!mur.loadFromFile("images/mur2.png"))
				exit(EXIT_FAILURE);
			spriteSol.setTexture(mur);
			spriteSol.setTextureRect(IntRect(0, 0, 1000, 50));
			spriteSol.setPosition(Vector2f(0.f, POS_SOL));
			creation_objets();
		break;
		case 3:
			if(!fond.loadFromFile("images/fond3.jpg",IntRect(0, 0, 1000, 1000)))
				exit(EXIT_FAILURE);
			spriteFond.setTexture(fond);

			if(!mur.loadFromFile("images/mur3.png"))
				exit(EXIT_FAILURE);
			spriteSol.setTexture(mur);
			spriteSol.setTextureRect(IntRect(0, 0, 1000, 50));
			spriteSol.setPosition(Vector2f(0.f, POS_SOL));
			creation_objets();
		break;
		default:
		break;
	}

}


void Map::creation_objets()
{
	Sprite obj(mur);
	//placement prédéfini des objets de la map
	switch(index){
		case 1:
			obj.setTextureRect(IntRect(0,0,600,30));
			obj.setPosition(Vector2f(200, 500));
			objets.push_back(obj);
			obj.setTextureRect(IntRect(0,0,200,30));
			obj.setPosition(Vector2f(50, 300));
			objets.push_back(obj);
			obj.setPosition(Vector2f(750,300));
			objets.push_back(obj);
			obj.setTextureRect(IntRect(0,0,100,30));
			obj.setPosition(Vector2f(450, 150));
			objets.push_back(obj);
		break;
		case 2:
			obj.setTextureRect(IntRect(0,0,250,30));
			obj.setPosition(Vector2f(100, 530));
			objets.push_back(obj);
			obj.setPosition(Vector2f(600, 530));
			objets.push_back(obj);
			obj.setPosition(Vector2f(100, 180));
			objets.push_back(obj);
			obj.setPosition(Vector2f(600, 180));
			objets.push_back(obj);
			obj.setTextureRect(IntRect(0,0,100,30));
			obj.setPosition(Vector2f(450, 360));
			objets.push_back(obj);
		break;
		case 3:
			obj.setTextureRect(IntRect(0,0,700,30));
			obj.setPosition(Vector2f(150, 360));
			objets.push_back(obj);
			obj.setTextureRect(IntRect(0,0,300,30));
			obj.setPosition(Vector2f(600, 530));
			objets.push_back(obj);
			obj.setPosition(Vector2f(100, 530));
			objets.push_back(obj);
			obj.setPosition(Vector2f(600, 530));
			objets.push_back(obj);
			obj.setTextureRect(IntRect(0,0,100,30));
			obj.setPosition(Vector2f(450, 180));
			objets.push_back(obj);
		break;
	}
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
	}
}

void Map::gestionCollectable(Collectable &co, Robot *rob)
{
	switch(co.getNumber())
	{
		case BOUCLIER:
		{
			//Bouclier& b = dynamic_cast<Bouclier&>(co);
			co.activation(*rob);
			break;
		}
		case GRANDIR:
		{
			//Grandir& gr = dynamic_cast<Grandir&>(co);
			co.activation(*rob);
			break;
		}
		case RAPETISSER:
		{
			//Rapetisser& rap = dynamic_cast<Rapetisser&>(co);
			co.activation(*rob);
			break;
		}
		case REPARER:
		{
			//Reparer& re = dynamic_cast<Reparer&>(co);
			co.activation(*rob);
			break;
		}
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
