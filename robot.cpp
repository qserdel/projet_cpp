#include "robot.hpp"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>


Robot::Robot(){
	_name="Joueur 1";
	pv = 3;
	vitesse = 300;
	taille = 0;
	x=50;
	y=80;
	hauteurSaut = 500;
	nbFrame = -1;
	_forme = new Forme(0,0,HAUTEUR_ROBOT,LARGEUR_ROBOT,sprite);
}


Robot::Robot(string name){
	_name=name;
	if(name!="Joueur1"){
		_forme = new Forme(0,1000,HAUTEUR_ROBOT,LARGEUR_ROBOT,sprite);
	}
	pv=20;
}

void Robot::detect_KeyPressed()
{
    if (Keyboard::isKeyPressed(Keyboard::Right))
        state = WALK_RIGHT;
    else if (Keyboard::isKeyPressed(Keyboard::Left))
        state = WALK_LEFT;
    else if (Keyboard::isKeyPressed(Keyboard::Down))
        state = DOWN;
	else
	    state = NORMAL;
    if (Keyboard::isKeyPressed(Keyboard::Up))
        enPleinJump = true;
    
}

void Robot::move(Robot *rob, Texture *robotActuel, Sprite *sprite, float elapsed)
{
    float monte = 0.f;
    if ((aGenoux == true) && (rob->state != DOWN)) // Si le robot était baissé sur la frame précédente et qu'il se relève, alors on remonte le robot
    {
        monte = -20.f;
        aGenoux = false;
    }
    
	if (rob->state == WALK_RIGHT)
    {
        sprite->move(Vector2f(vitesse*elapsed, monte)); // Déplacement par rapport à la position actuelle
        (rob->nbFrame)++;
        if(rob->nbFrame == 9)
	        rob->nbFrame = 0;
        *robotActuel = texture[nbFrame];
	}
    else if (rob->state == WALK_LEFT)
    {
    	sprite->move(Vector2f(-vitesse*elapsed, monte)); // Déplacement par rapport à la position actuelle
    	(rob->nbFrame)--;
    	if(rob->nbFrame == -1)
    		rob->nbFrame = 8;
    	*robotActuel = texture[nbFrame];
	}
	else if ((rob->state == DOWN) && (aGenoux == false))
	{
	    *robotActuel = texture[11];
	    sprite->move(Vector2f(0.f, 20.f));
        aGenoux = true;
	}
	else if (rob->state == NORMAL)
	{
	    *robotActuel = texture[10];
	    if(monte != 0.f) // Si le robot n'est pas au niveau du sol parce que le robot s'est baissé sur la frame précédente, je remonte
	        sprite->move(Vector2f(0.f, monte));
    }

    if (rob->enPleinJump == true)
    	sauter(rob, sprite, elapsed, robotActuel);
}


void Robot::sauter(Robot *rob, Sprite* sprite, float elapsed, Texture *robotActuel)
{
    rob->hauteurSaut += GRAVITE;
    sprite->move(Vector2f(0.f, -(rob->hauteurSaut)*elapsed));
    if ((rob->hauteurSaut >= 0) && (rob->getStatus() != DOWN))
        *robotActuel = texture[12];
    else if ((rob->hauteurSaut < 0) && (rob->getStatus() != DOWN))
        *robotActuel = texture[13];

    if ((sprite->getPosition().y >= 525.0) && (rob->getStatus() != DOWN))
    {
        rob->hauteurSaut = 500;
        sprite->setPosition(sprite->getPosition().x, 525.f);
        rob->enPleinJump = false;
        *robotActuel = texture[10];
    }
    else if ((sprite->getPosition().y >= 545.0) && (rob->getStatus() == DOWN))
    {
        rob->hauteurSaut = 500;
        sprite->setPosition(sprite->getPosition().x, 545.f);
        rob->enPleinJump = false;
    }
}


void Robot::chargement_image()
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
	if (!texture[10].loadFromFile("images/Face.jpg", IntRect(0, 10, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[11].loadFromFile("images/bas.jpg", IntRect(0, 0, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[12].loadFromFile("images/saut1.jpg", IntRect(0, 15, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[13].loadFromFile("images/saut2.jpg", IntRect(0, 5, 120, 190)))
		exit(EXIT_FAILURE);
}

void Robot::message()
{
	cout<<"Hello !"<<endl;
}

int Robot::getStatus() const {return state;}
int Robot::getNbFrame() const {return nbFrame;}
int Robot::getHauteurSaut() const {return hauteurSaut;}
bool Robot::getEnPleinJump() const {return enPleinJump;}

Texture Robot::getTexture(int indice) const {return texture[indice];}


