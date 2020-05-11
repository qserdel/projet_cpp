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
	chargement_image();
	robotActuel = texture[10];
    sprite.setTexture(robotActuel);
    sprite.setPosition(Vector2f(20.f, 525.f)); // Choix de la position du sprite
    sprite.setTextureRect(IntRect(0,0,100,135));
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
	else if (this->state != BLESSE)
	    state = NORMAL;
    if (Keyboard::isKeyPressed(Keyboard::Up))
        enPleinJump = true;
    if (Keyboard::isKeyPressed(Keyboard::G))
    {
        enPleinGrandissement = true;
        max_scale = 2.0;
    }
    if (Keyboard::isKeyPressed(Keyboard::R))
    {
        enPleinRapetissement = true;
        min_scale = 0.5;
    }
    if (Keyboard::isKeyPressed(Keyboard::T))
        tir = true;
}

void Robot::move(float elapsed)
{
    float monte = 0.f;
    if ((this->aGenoux == true) && (this->state != DOWN)) // Si le robot était baissé sur la frame précédente et qu'il se relève, alors on remonte le robot
    {
        monte = -20.f*this->sprite.getScale().y;
        this->aGenoux = false;
    }
    
	if (this->state == WALK_RIGHT)
    {
        this->sprite.move(Vector2f(this->vitesse*elapsed, monte)); // Déplacement par rapport à la position actuelle
        (this->nbFrame)++;
        if(this->nbFrame == 9)
	        this->nbFrame = 0;
        this->robotActuel = texture[this->nbFrame];
	}
    else if (this->state == WALK_LEFT)
    {
    	this->sprite.move(Vector2f(-this->vitesse*elapsed, monte)); // Déplacement vers la gauche
    	(this->nbFrame)--;
    	if(this->nbFrame == -1)
    		this->nbFrame = 8;
    	this->robotActuel = texture[this->nbFrame];
	}
	else if ((this->state == DOWN) && (this->aGenoux == false))
	{
	    this->robotActuel = texture[11];
	    this->sprite.move(Vector2f(0.f, 20.f*this->sprite.getScale().y));
        this->aGenoux = true;
	}
	else if (this->state == NORMAL)
	{
	    this->robotActuel = texture[10];
	    if(monte != 0.f) // Si le robot n'est pas au niveau du sol parce que le robot s'est baissé sur la frame précédente, je remonte
	        this->sprite.move(Vector2f(0.f, monte));
    }

    if (this->enPleinJump == true)
    	this->sauter(elapsed);
}


void Robot::sauter(float elapsed)
{
    this->hauteurSaut += GRAVITE;
    this->sprite.move(Vector2f(0.f, -(this->hauteurSaut)*elapsed));
    if ((this->hauteurSaut >= 0) && (this->state != DOWN))
    {
        this->robotActuel = texture[12];
        this->sprite.setTextureRect(IntRect(0,0,100,160));
    }
    else if ((this->hauteurSaut < 0) && (this->state != DOWN))
    {
        this->robotActuel = texture[13];
        this->sprite.setTextureRect(IntRect(0,0,100,160));
    }

    if ((this->sprite.getPosition().y >= 660-this->sprite.getScale().y*135) && (this->state != DOWN))
    {
        this->hauteurSaut = 500;
        this->sprite.setPosition(this->sprite.getPosition().x, 660-this->sprite.getScale().y*135);
        this->enPleinJump = false;
        this->robotActuel = texture[10];
        this->sprite.setTextureRect(IntRect(0,0,100,135));
    }
    else if ((this->sprite.getPosition().y >= 660-this->sprite.getScale().y*135+20.f*this->sprite.getScale().y) && (this->state == DOWN))
    {
        this->hauteurSaut = 500;
        this->sprite.setPosition(this->sprite.getPosition().x, 660-this->sprite.getScale().y*135+20.f*this->sprite.getScale().y);
        this->enPleinJump = false;
        this->sprite.setTextureRect(IntRect(0,0,100,135));
    }
}


void Robot::grandir()
{
    if (this->taillePrec == 0)
        this->taillePrec = this->sprite.getLocalBounds().height*this->sprite.getScale().y; // Récupère la hauteur du sprite initial

    if ((this->sprite.getScale().x*1.1 <= this->max_scale) && (taille != GRAND))
    {
        this->sprite.scale(Vector2f(1.1f, 1.1f)); // Modifie l'échelle par rapport à l'échelle actuelle
        this->sprite.move(Vector2f(0.f, -this->taillePrec*0.1));
        this->taillePrec *= 1.1;
    }
    else
    {
        this->enPleinGrandissement = false;
        this->taillePrec = 0;
        if (this->max_scale == 1.0)
        {
            this->taille = NORMAL;
            this->sprite.move(Vector2f(0.f, this->sprite.getLocalBounds().height*(this->sprite.getScale().y-1)));
            this->sprite.setScale(Vector2f(1.f, 1.f));
        }
        else
            this->taille = GRAND;
    }

    if (this->taille == GRAND)
        this->timerGrand++;
    
    if ((this->timerGrand > 500) && (this->taille == GRAND))
    {
        this->enPleinRapetissement = true;
        this->min_scale = 1.0;
        this->timerGrand = 0;
    }
}


void Robot::rapetisser()
{
    if (this->taillePrec == 0)
        this->taillePrec = this->sprite.getLocalBounds().height*this->sprite.getScale().y;

    if ((this->sprite.getScale().x*0.9 >= this->min_scale) && (this->taille != PETIT))
    {
        this->sprite.scale(Vector2f(0.9f, 0.9f)); // Modifie l'échelle par rapport à l'échelle actuelle
        this->sprite.move(Vector2f(0.f, this->taillePrec*0.1));
        this->taillePrec *= 0.9;
    }
    else
    {
        this->enPleinRapetissement = false;
        this->taillePrec = 0;
        if (this->min_scale == 1.0)
        {
            this->taille = NORMAL;
            this->sprite.move(Vector2f(0.f, this->sprite.getLocalBounds().height*(this->sprite.getScale().y-1)));
            this->sprite.setScale(Vector2f(1.f, 1.f));
        }
        else
            this->taille = PETIT;
    }
    
    if (this->taille == PETIT)
        this->timerPetit++;

    if ((this->timerPetit > 500) && (this->taille == PETIT))
    {
        this->enPleinGrandissement = true;
        this->max_scale = 1.0;
        this->timerPetit = 0;
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
	if (!texture[14].loadFromFile("images/blesse.jpg", IntRect(0, 0, 120, 190)))
		exit(EXIT_FAILURE);
	if (!texture[15].loadFromFile("images/blesse1.jpg"))
		exit(EXIT_FAILURE);
	if (!texture[16].loadFromFile("images/blesse2.jpg"))
		exit(EXIT_FAILURE);
	if (!texture[17].loadFromFile("images/blesse3.jpg"))
		exit(EXIT_FAILURE);
	if (!texture[18].loadFromFile("images/blesse4.jpg"))
		exit(EXIT_FAILURE);
	if (!texture[19].loadFromFile("images/blesse5.jpg"))
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
bool Robot::getEnPleinGrandissement() const {return enPleinGrandissement;};
bool Robot::getEnPleinRapetissement() const {return enPleinRapetissement;};
bool Robot::getTir() const {return tir;};
void Robot::setTir(bool var) {this->tir = var;};
int Robot::getTaille() const {return taille;};
float Robot::getMinScale() const {return min_scale;};
float Robot::getMaxScale() const {return max_scale;};
Sprite Robot::getSprite() const {return sprite;};
int Robot::getPv() const {return pv;};
int Robot::getTimerBlesse() const {return timerBlesse;};

void Robot::setPv(int nbVie) {this->pv = nbVie;};
void Robot::setNbFrame(int nbreF) {this->nbFrame = nbreF;};
void Robot::setRobotActuel(Texture robAct) {this->robotActuel = robAct;};
void Robot::setStatus(int etat) {this->state = etat;};
void Robot::setTimerBlesse(int t) {this->timerBlesse = t;};

IntRect Robot::getRectRobot() const
{
    IntRect rectRobot;
    rectRobot.left = sprite.getPosition().x;
    rectRobot.width = sprite.getPosition().x + sprite.getLocalBounds().width;
    rectRobot.top = sprite.getPosition().y;
    rectRobot.height = sprite.getPosition().y + sprite.getLocalBounds().height;
    return rectRobot;
}

Texture Robot::getTexture(int indice) const {return texture[indice];}


