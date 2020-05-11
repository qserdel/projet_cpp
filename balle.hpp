#ifndef BALLE_HPP
#define BALLE_HPP
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Balle
{
    private :

        Texture balle; // partagée par toutes les instances

        Sprite sp; // un pour chaque instance
    
    public :

        Balle();
        
        bool action();
        
        Sprite getSprite() const;
        IntRect getRectBalle() const;
};
#endif
