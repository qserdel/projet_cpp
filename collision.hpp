#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "balle.hpp"

using namespace sf;

class Collision
{
    private :

        Balle &balle;
        Robot &robot;

    
    public :

        Collision(Balle &b, Robot &r);
        
        bool gestionCollision(Robot *r, Balle *b);
        
        bool detectCollision(const IntRect &b, const IntRect &r);
        

};

#endif
