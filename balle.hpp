#ifndef BALLE_HPP
#define BALLE_HPP
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "parametres.hpp"


class Balle
{
    private :

        sf::Texture textureBalle;

        sf::Sprite sp; // Un pour chaque instance

        bool direction;
        int ID_Joueur;

      public :
        Balle();
        Balle(float x, float y, bool dir, int ID);
        Balle(Balle const& copy);
        
        ~Balle();

        void action();

        sf::Sprite getSprite() const;
        sf::IntRect getRectBalle() const;
        float getX() const;
        int getID() const;
        bool getDir() const;
        float getLargeur() const;
        void setX(float newX);
        void setDir(bool a);
};
#endif
