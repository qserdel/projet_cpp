#include "balle.hpp"


Balle::Balle(){}

Balle::Balle(Balle const& copy) : sp(copy.sp), textureBalle(copy.textureBalle), direction(copy.direction), ID_Joueur(copy.ID_Joueur)
{}

Balle::Balle(float x, float y, bool dir, int ID)
{
    direction = dir;
    if (dir)
    {
      if (!textureBalle.loadFromFile("images/Tir.png"))
        exit(EXIT_FAILURE);
    } else {
      if (!textureBalle.loadFromFile("images/TirL.png"))
        exit(EXIT_FAILURE);
    }
    sp.setTexture(textureBalle);
    sp.setPosition(Vector2f(x, y));
    sp.setScale(Vector2f(1.2, 1.2));
    ID_Joueur = ID;
}

void Balle::action()
{
    if(direction){
      if (sp.getPosition().x < 1000)
      {
          sp.move(Vector2f(10.f, 0.f));
      }
    } else {
        if (sp.getPosition().x > 0)
        {
            sp.move(Vector2f(-10.f, 0.f));
        }
    }
}

Sprite Balle::getSprite() const {return sp;};
float Balle::getX() const {return sp.getPosition().x;};
int Balle::getID() const {return ID_Joueur;};
bool Balle::getDir() const {return direction;};
void Balle::setX(float newX) {sp.setPosition(newX,sp.getPosition().y);};
void Balle::setDir(bool a) {direction = a;};

IntRect Balle::getRectBalle() const
{
    IntRect rectBalle;
    rectBalle.left = sp.getPosition().x;
    rectBalle.width = sp.getPosition().x + sp.getLocalBounds().width;
    rectBalle.top = sp.getPosition().y;
    rectBalle.height = sp.getPosition().y + sp.getLocalBounds().height;
    return rectBalle;
}
