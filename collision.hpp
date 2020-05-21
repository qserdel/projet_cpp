#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "balle.hpp"
#include "map.hpp"

using namespace sf;

class Collision
{
    private :

        Balle &balle;
        Robot &robot;
        float altitude_atterrissage;

    
    public :

        Collision(Balle &b, Robot &r);
        
        void gestionCollision(Robot *r, Balle *b, Map *map, float elapsed);
        bool detectCollision(const IntRect &b, const IntRect &r);
        bool detectAtterrissage(const IntRect &r,  const Map &map);
        void atterrissage(float altitude, Robot *r);
        

};

#endif
