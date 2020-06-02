#include "collision.hpp"

Collision::Collision() : altitude_atterrissage(0)
{}


void Collision::gestionCollisionBalle(Robot *r, vector<Balle> &tBalles, int i)
{
	if (detectCollision(tBalles[i].getRectBalle(), r->getRectRobot()) && tBalles[i].getID() != r->getID())
    {
    	if (r->getBouclier() == false)
    	{
		    r->setStatus(BLESSE);
		    r->setRobotActuel(r->getTexture(14+r->getIncrementLeft()));
		    r->setPv(r->getPv()-1);
	    }
		tBalles.erase(tBalles.begin() + i);
    }
}

void Collision::gestionAtterrissage(Robot *r, Map *map, float elapsed)
{
	if (detectAtterrissage(r->getRectRobot(), *map) && (r->getHauteurSaut() < 0))
		atterrissage(altitude_atterrissage, r);

    if (!r->getEnPleinJump() && !detectAtterrissage(r->getRectRobot(), *map)) // Si le robot n'est sur aucun support
    {
		r->setPosSprite(r->getSprite().getPosition().x, r->getSprite().getPosition().y + 400*elapsed);  // Le robot est en chute libre
		if (detectAtterrissage(r->getRectRobot(), *map))
			atterrissage(altitude_atterrissage, r);
	}
}

void Collision::collisionCollec(Robot *r, Map *map)
{
	for (size_t i = 0; i < map->getListCollec().size(); i++)
    {
    	if (detectCollision(map->getRectColl(i), r->getRectRobot()))
    	{
    		map->gestionCollectable(map->getListCollec()[i], r);
    		map->supprimerCollec(i);
		}
    }
}

void Collision::gestionAtterrissageCollec(Map *map, float elapsed)
{
	IntRect obj, obj1;

	for (size_t i = 0; i < map->getListCollec().size(); i++)
    {
    	if (!map->getSpriteStable(i))
    	{
			obj1 = map->getRectColl(i);
			for (size_t j = 0; j < map->getListObjets().size(); j++)
			{
				obj = map->getRectObj(j);
				if (detectCollision(obj, obj1))
				{
					map->setPosCollec(obj1.left, obj.top - (obj1.height - obj1.top), i);
					map->setSpriteStable(true, i);
					break;
				}
			}

			if (POS_SOL - obj1.height <= 0)
			{
				map->setPosCollec(obj1.left, POS_SOL - (obj1.height - obj1.top), i);
				map->setSpriteStable(true, i);
			}
			else if (!map->getSpriteStable(i))
				map->moveCollec(Vector2f(0.f, 200.f*elapsed), i);
		}
	}
}

bool Collision::detectCollision(const IntRect &b, const IntRect &r)
{
    if (b.height < r.top)
        return false;
    if (b.top > r.height)
        return false;
    if (b.left > r.width)
        return false;
    if (b.width < r.left)
        return false;
    else
        return true;
}


bool Collision::detectAtterrissage(const IntRect &r, const Map &map)
{
	IntRect obj;
	for (size_t i = 0; i < map.getListObjets().size(); i++)
    {
    	obj = map.getRectObj(i);
    	if (detectCollision(r, obj) && abs(obj.top - r.height) <= 20) // 20 car on autorise une petite marge d'erreur
		{
			altitude_atterrissage = obj.top;
			return true;
		}
    }
    if (POS_SOL - r.height <= 0)
    {
		altitude_atterrissage = POS_SOL;
		return true;
    }

    return false;
}


void Collision::atterrissage(float altitude, Robot *r)
{
	r->setHauteurSaut(500);
	r->setEnPleinJump(false);
    r->setTextRect(LARGEUR_ROBOT, HAUTEUR_ROBOT);

	if (r->getStatus() != DOWN) // Si le robot atterrit normalement
    {
		r->setPosSprite(r->getSprite().getPosition().x, altitude-r->getSprite().getScale().y*HAUTEUR_ROBOT);
        r->setRobotActuel(r->getTexture(10+r->getIncrementLeft()));
    }
    else if (r->getStatus() == DOWN)
		r->setPosSprite(r->getSprite().getPosition().x, altitude-r->getSprite().getScale().y*HAUTEUR_ROBOT+20.f*r->getSprite().getScale().y);
}

float Collision::getAltitude_atterrissage() const {return altitude_atterrissage;};

