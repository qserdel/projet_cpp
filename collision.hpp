#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "collectable.hpp"
#include "robot.hpp"
#include "balle.hpp"
#include "map.hpp"

using namespace sf;

class Collision
{
    private :
        float altitude_atterrissage;

    
    public :

        Collision();
        
        void gestionCollisionBalle(Robot *r, Balle *b, Map *map, float elapsed);
        void gestionAtterrissage(Robot *r, Map *map, float elapsed);
        bool detectCollision(const IntRect &b, const IntRect &r);
        bool detectAtterrissage(const IntRect &r,  const Map &map);
        void atterrissage(float altitude, Robot *r);
        void gestionAtterrissageCollec(Map *map, float elapsed);
        void collisionCollec(Robot *r, Map *map);
        

};

#endif
