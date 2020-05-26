#include "balle.hpp"


Balle::Balle(){}

Balle::Balle(float x, float y, bool dir)
{
    direction = dir;
    if(dir)
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
}

void Balle::action()
{
    sp.setTexture(textureBalle);
    if(direction){
      if (sp.getPosition().x < 1000)
      {
          sp.move(Vector2f(10.f, 0.f));
      } else {
        //delete this;
      }
    } else {
        if (sp.getPosition().x > -100)
        {
            sp.move(Vector2f(-10.f, 0.f));
        } else {
          //delete this;
        }
    }
}

Sprite Balle::getSprite() const {return sp;};
float Balle::getX() const {return sp.getPosition().x;};

IntRect Balle::getRectBalle() const
{
    IntRect rectBalle;
    rectBalle.left = sp.getPosition().x;
    rectBalle.width = sp.getPosition().x + sp.getLocalBounds().width;
    rectBalle.top = sp.getPosition().y;
    rectBalle.height = sp.getPosition().y + sp.getLocalBounds().height;
    return rectBalle;
}
