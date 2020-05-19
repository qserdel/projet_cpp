#include "collision.hpp"

Collision::Collision(Balle &b, Robot &r)
: balle(b), robot(r)
{}

void Collision::gestionCollision(Robot *r, Balle *b)
{
    if ((detectCollision(b->getRectBalle(), r->getRectRobot()) == true) || (r->getStatus() == BLESSE))
    {
        if (r->getStatus() != BLESSE)
        {
            r->setStatus(BLESSE);
            r->setNbFrame(14);
            r->setPv(r->getPv()-1);
        }
        /*else if ((this->nbFrame != 19) && (this->pv > 0))
        {
            this->sprite.setTextureRect(IntRect(0,0,130,100));
            this->nbFrame++;
        }*/
        
        r->setRobotActuel(r->getTexture(r->getNbFrame()));
        r->setTimerBlesse(r->getTimerBlesse()+1);

        if (r->getTimerBlesse() > 50)
        {
            r->setStatus(NORMAL);
            r->setTimerBlesse(0);
            r->setNbFrame(0);
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
