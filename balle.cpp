#include "balle.hpp"


Balle::Balle()
{
    if (!balle.loadFromFile("images/Tir.png"))
        exit(EXIT_FAILURE);
    sp.setTexture(balle);
    sp.setPosition(Vector2f(600.f, 530.f));
    sp.setScale(Vector2f(1.3f, 1.3f));
}

bool Balle::action()
{
    sp.move(Vector2f(-10.f, 0.f));
    if (sp.getPosition().x < 0)
        return false;
    return true;
}

Sprite Balle::getSprite() const {return sp;};

IntRect Balle::getRectBalle() const
{
    IntRect rectBalle;
    rectBalle.left = sp.getPosition().x;
    rectBalle.width = sp.getPosition().x + sp.getLocalBounds().width;
    rectBalle.top = sp.getPosition().y;
    rectBalle.height = sp.getPosition().y + sp.getLocalBounds().height;
    return rectBalle;
}
