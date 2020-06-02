#include "bouclier.hpp"


Bouclier::Bouclier() : Collectable(BOUCLIER)
{
	if (!txt.loadFromFile("images/bouclier.png"))
			exit(EXIT_FAILURE);
	sp.setTexture(txt);
}

void Bouclier::activation(Robot &r)
{
	r.setBouclier(true);
	r.actionBouclier();
}

CircleShape Bouclier::formationBouclier(Robot &rob)
{
	float rayon(sqrt(pow(HAUTEUR_ROBOT*rob.getSprite().getScale().x, 2) + pow(LARGEUR_ROBOT*rob.getSprite().getScale().y, 2))/2);
	CircleShape bouclier(rayon);
	bouclier.setPosition(Vector2f(rob.getX()+LARGEUR_ROBOT*rob.getSprite().getScale().x/2-rayon, rob.getY()+HAUTEUR_ROBOT*rob.getSprite().getScale().y/2-rayon));
	if(rob.getID()){
		bouclier.setFillColor(Color(255,0,0,75));
	} else {
		bouclier.setFillColor(Color(0,0,255,75));
	}
	return bouclier;
}
