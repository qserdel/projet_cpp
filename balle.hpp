#ifndef BALLE_HPP
#define BALLE_HPP
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Balle
{
    private :

        Texture textureBalle;

        Sprite sp; // un pour chaque instance

        bool direction;

      public :
        Balle();
        Balle(float x, float y, bool direction);

        void action();

        Sprite getSprite() const;
        IntRect getRectBalle() const;
        float getX() const;
        void setX(float newX);
};
#endif
