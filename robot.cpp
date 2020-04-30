#include "robot.hpp"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>


Robot::Robot(){
	_name="Joueur 1";
	pv = 3;
	vitesse = 10;
	taille = 0;
	x=50;
	y=80;
	_forme = new Forme(0,0,HAUTEUR_ROBOT,LARGEUR_ROBOT,sprite);
}


Robot::Robot(string name){
	_name=name;
	if(name!="Joueur1"){
		_forme = new Forme(0,1000,HAUTEUR_ROBOT,LARGEUR_ROBOT,sprite);
	}
	pv=20;
}
		
void Robot::move(Event e, Texture *texture, Texture *robotActuel, int *compteur, Sprite *sprite)
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
    {
    	(*sprite).move(Vector2f(vitesse, 0.f)); // Déplacement par rapport à la position actuelle
    	(*compteur)++;
    	if(*compteur == 9)
    		*compteur = 0;
    	*robotActuel = texture[*compteur];
	}
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
    	(*sprite).move(Vector2f(-vitesse, 0.f)); // Déplacement par rapport à la position actuelle
    	(*compteur)--;
    	if(*compteur == -1)
    		*compteur = 8;
    	*robotActuel = texture[*compteur];
	}
    if (Keyboard::isKeyPressed(Keyboard::Up))
    	(*sprite).move(Vector2f(0.f, -vitesse)); // Déplacement par rapport à la position actuelle
    if (Keyboard::isKeyPressed(Keyboard::Down))
    	(*sprite).move(Vector2f(0.f, vitesse)); // Déplacement par rapport à la position actuelle*/
}

void Robot::chargement_image(Texture* texture)
{
	if (!texture[0].loadFromFile("images/1Rapide.jpg", IntRect(0, 0, 120, 190)))
	    exit(EXIT_FAILURE);
	if (!texture[1].loadFromFile("images/2Rapide.jpg", IntRect(0, 0, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[2].loadFromFile("images/3Rapide.jpg", IntRect(5, 25, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[3].loadFromFile("images/4Rapide.jpg", IntRect(10, 30, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[4].loadFromFile("images/5Rapide.jpg", IntRect(0, 10, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[5].loadFromFile("images/6Rapide.jpg", IntRect(0, 20, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[6].loadFromFile("images/7Rapide.jpg", IntRect(0, 10, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[7].loadFromFile("images/8Rapide.jpg", IntRect(0, 10, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[8].loadFromFile("images/9Rapide.jpg", IntRect(10, 25, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[9].loadFromFile("images/10Rapide.jpg", IntRect(0, 10, 120, 190)))
		exit(EXIT_FAILURE);
}

void Robot::message()
{
	cout<<"Hello !"<<endl;
}
