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
        int ID_Joueur;

      public :
        Balle();
        Balle(float x, float y, bool dir, int ID);
        Balle(Balle const& copy);

        void action();

        Sprite getSprite() const;
        IntRect getRectBalle() const;
        float getX() const;
        int getID() const;
        void setX(float newX);
};
#endif
