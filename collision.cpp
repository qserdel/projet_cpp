#include "collision.hpp"

Collision::Collision() : altitude_atterrissage(0)
{}


void Collision::gestionCollisionBalle(Robot *r, Balle *b, Map *map, float elapsed)
{
	if (detectCollision(b->getRectBalle(), r->getRectRobot()))
    {
        r->setStatus(BLESSE);
        r->setRobotActuel(r->getTexture(14+r->getIncrementLeft()));
				r->setTextRect(LARGEUR_ROBOT+10, HAUTEUR_ROBOT);
        r->setPv(r->getPv()-1);
    }
}

void Collision::gestionAtterrissage(Robot *r, Map *map, float elapsed)
{
	if (detectAtterrissage(r->getRectRobot(), *map) && (r->getHauteurSaut() < 0)) // Détecte uniquement en cas de saut, à revoir !
		atterrissage(altitude_atterrissage, r);

    if (!r->getEnPleinJump() && !detectAtterrissage(r->getRectRobot(), *map)) // Si le robot n'est sur aucun support
    {
		r->setPosSprite(r->getSprite().getPosition().x, r->getSprite().getPosition().y + 400*elapsed);  // Le robot est en chute libre
		if (detectAtterrissage(r->getRectRobot(), *map))
			atterrissage(altitude_atterrissage, r);
	}
}

void Collision::gestionAtterrissageCollec(Map *map, float elapsed)
{
	IntRect obj, obj1;
	Sprite sp;
	cout<<"size = "<<map->getListCollec().size()<<endl;
	for (size_t i = 0; i < map->getListCollec().size(); i++)
    {
    	obj1 = map->getRectColl(i);
		for (size_t j = 0; j < map->getListObjets().size(); j++)
		{
			obj = map->getRectObj(j);
			if (detectCollision(obj, obj1))
			{
				sp = map->getListCollec()[i];
				sp.setPosition(obj1.left, obj.top - (obj1.height - obj1.top));
				map->setListCollec(sp, i);
				break;
			}
		}

		if (POS_SOL - obj1.height < 5) // Si on met 0 le sprite tremblotte, on met donc 5 pour autoriser une petite marge d'erreur
		{
			sp = map->getListCollec()[i];
			sp.setPosition(obj1.left, POS_SOL - (obj1.height - obj1.top));
			map->setListCollec(sp, i);
		}
		else
		{
			sp = map->getListCollec()[i];
			sp.move(Vector2f(0.f, 200.f*elapsed));
			map->setListCollec(sp, i);
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
    	if (abs(obj.top - r.height) <= 20)
		{
			if (((r.left < obj.width) && (r.left > obj.left)) || ((r.width > obj.left) && (r.width < obj.width)) || ((r.left < obj.left) && (r.width > obj.width)))
			{
				altitude_atterrissage = obj.top;
				return true;
			}
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
