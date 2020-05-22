#include "collision.hpp"

Collision::Collision(Balle &b, Robot &r) : balle(b), robot(r)
{}

void Collision::gestionCollision(Robot *r, Balle *b, Map *map, float elapsed)
{
    if (detectCollision(b->getRectBalle(), r->getRectRobot()) == true)
    {
        r->setStatus(BLESSE);
        r->setRobotActuel(r->getTexture(14));
        r->setPv(r->getPv()-1);
    }

	if ((detectAtterrissage(r->getRectRobot(), *map)) && (r->getHauteurSaut() < 0))
		atterrissage(altitude_atterrissage, r);

    if ((!detectAtterrissage(r->getRectRobot(), *map)) && (!r->getEnPleinJump()))  // Si le robot n'est sur aucun support
    	r->setPosSprite(r->getSprite().getPosition().x, r->getSprite().getPosition().y + 400*elapsed); // Le robot est en chute libre

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
    	if (abs(obj.top - r.height) <= 10)
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
        r->setRobotActuel(r->getTexture(10));
    }
    else if (r->getStatus() == DOWN)
		r->setPosSprite(r->getSprite().getPosition().x, altitude-r->getSprite().getScale().y*HAUTEUR_ROBOT+20.f*r->getSprite().getScale().y);
}

// Problème : Lorsque le robot est gand ou petit et qu'on le fait aller à droite.

