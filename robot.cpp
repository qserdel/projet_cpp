#include "robot.hpp"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>


Robot::Robot(string name){
	_name=name;
	pv = 3;
	vitesse = 300;
	taille = 0;
	hauteurSaut = 500;
	nbFrame = 0;
	chargement_image();
	if(_name == "Joueur1")
	{
  		sprite.setPosition(Vector2f(20.f, POS_SOL-HAUTEUR_ROBOT)); // Choix de la position du sprite
  		robotActuel = texture[10];
	}
	else
	{
		sprite.setPosition(Vector2f(TAILLE_WINDOW - LARGEUR_ROBOT - 20.f, POS_SOL-HAUTEUR_ROBOT));
		increment_left = 15;
		robotActuel = texture[10+increment_left];
	}
	sprite.setTexture(robotActuel);
  	sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, HAUTEUR_ROBOT));
}

void Robot::detect_KeyPressed()
{
	if ((this->_name == "Joueur1") && (this->state != BLESSE))  // Le joueur ne peut rien faire s'il est blessé
	{
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (this->state != WALK_RIGHT)
				this->increment_left = 0;
		    state = WALK_RIGHT;
	    }
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (this->state != WALK_LEFT)
				this->increment_left = 15;
		    state = WALK_LEFT;
	    }
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		    state = DOWN;
		else
			state = NORMAL;
		
		if (Keyboard::isKeyPressed(Keyboard::Up))
		    enPleinJump = true;
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
		    enPleinGrandissement = true;
		    max_scale = 2.0;  // La taille maximale qu'il pourra atteindre
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
		    enPleinRapetissement = true;
		    min_scale = 0.5;  // La taille minimale qu'il pourra atteindre
		}
		if (Keyboard::isKeyPressed(Keyboard::T))
		    tir = true;
    }
    else if ((this->_name == "Joueur2") && (this->state != BLESSE))  // Le joueur ne peut rien faire s'il est blessé
    {
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (this->state != WALK_RIGHT)
				this->increment_left = 0;
		    state = WALK_RIGHT;
	    }
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			if (this->state != WALK_LEFT)
				this->increment_left = 15;
		    state = WALK_LEFT;
	    }
		else if (Keyboard::isKeyPressed(Keyboard::S))
		    state = DOWN;
		else
			state = NORMAL;
		
		if (Keyboard::isKeyPressed(Keyboard::Z))
		    enPleinJump = true;
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
		    enPleinGrandissement = true;
		    max_scale = 2.0;  // La taille maximale qu'il pourra atteindre
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
		    enPleinRapetissement = true;
		    min_scale = 0.5;  // La taille minimale qu'il pourra atteindre
		}
		if (Keyboard::isKeyPressed(Keyboard::T))
		    tir = true;
    }
}


void Robot::move(float elapsed)
{
    float monte = 0.f;
    int increment = 0;
    if (this->_name == "Joueur2")
    	increment = 20;
    if ((this->aGenoux == true) && (this->state != DOWN))  // Si le robot était baissé sur la frame précédente et qu'il se relève, alors on remonte le robot
    {
        monte = -20.f*this->sprite.getScale().y;
        this->aGenoux = false;
    }

	if (this->state == WALK_RIGHT && this->sprite.getPosition().x < TAILLE_WINDOW-LARGEUR_ROBOT)
    {
        this->sprite.move(Vector2f(this->vitesse*elapsed, monte));  // Déplacement par rapport à la position actuelle
        (this->nbFrame)++;
        if(this->nbFrame == 10)
	        this->nbFrame = 0;
        this->robotActuel = this->texture[this->nbFrame];
	}
    else if (this->state == WALK_LEFT && this->sprite.getPosition().x > 0)
    {
    	this->sprite.move(Vector2f(-this->vitesse*elapsed, monte));  // Déplacement vers la gauche
    	(this->nbFrame)++;
    	if(this->nbFrame == 10)
    		this->nbFrame = 0;
    	this->robotActuel = this->texture[this->nbFrame+this->increment_left];
	}
	else if ((this->state == DOWN) && (this->aGenoux == false))
	{
	    this->robotActuel = this->texture[11+this->increment_left];
	    this->sprite.move(Vector2f(0.f, 20.f*this->sprite.getScale().y));
        this->aGenoux = true;
	}
	else if (this->state == NORMAL)
	{
	    this->robotActuel = this->texture[10+this->increment_left];
	    if(monte != 0.f)  // Si le robot n'est pas au niveau du sol parce que le robot s'est baissé sur la frame précédente, je remonte
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
        this->robotActuel = this->texture[12+this->increment_left];
        this->sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, 160)); // Le Sprite du robot qui saute est plus grand que ceux du robot au sol
    }
    else if ((this->hauteurSaut < 0) && (this->state != DOWN))
    {
        this->robotActuel = this->texture[13+this->increment_left];
        this->sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, 160));
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
        this->timerGrand--;

    if ((this->timerGrand <= 0) && (this->taille == GRAND))
    {
        this->enPleinRapetissement = true;
        this->min_scale = 1.0;
        this->timerGrand = TIMER_GRAND;
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
        this->timerPetit--;

    if ((this->timerPetit <= 0) && (this->taille == PETIT))
    {
        this->enPleinGrandissement = true;
        this->max_scale = 1.0;
        this->timerPetit = TIMER_PETIT;
    }
}

void Robot::blessure()
{
    this->timerBlesse--;

    if (this->timerBlesse <= 0)
    {
        this->state = NORMAL;
        this->timerBlesse = TIMER_BLESSE;
        this->nbFrame = 0;
    }
}

void Robot::chargement_image()
{
	string fin_nom;
	string dossier;
	for (int i = 0; i < 2; i++)
	{
		if (this->_name == "Joueur1")
		{
			if (i == 0)
				fin_nom = ".png";
			else if (i == 1)
				fin_nom = "L.png";
		}
		else
		{
			if (i == 0)
				fin_nom = "2.png";
			else if (i == 1)
				fin_nom = "2L.png";
		}

		dossier = "images/";
	    if (!this->texture[0+15*i].loadFromFile(dossier.append(to_string(1)).append("Rapide").append(fin_nom), IntRect(0, 0, 120, 190)))
	    	exit(EXIT_FAILURE);
    	dossier = "images/";
    	if (!this->texture[1+15*i].loadFromFile(dossier.append(to_string(2)).append("Rapide").append(fin_nom), IntRect(0, 0, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[2+15*i].loadFromFile(dossier.append(to_string(3)).append("Rapide").append(fin_nom), IntRect(5, 25, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[3+15*i].loadFromFile(dossier.append(to_string(4)).append("Rapide").append(fin_nom), IntRect(10, 30, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[4+15*i].loadFromFile(dossier.append(to_string(5)).append("Rapide").append(fin_nom), IntRect(0, 10, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[5+15*i].loadFromFile(dossier.append(to_string(6)).append("Rapide").append(fin_nom), IntRect(0, 20, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[6+15*i].loadFromFile(dossier.append(to_string(7)).append("Rapide").append(fin_nom), IntRect(0, 10, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[7+15*i].loadFromFile(dossier.append(to_string(8)).append("Rapide").append(fin_nom), IntRect(0, 10, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[8+15*i].loadFromFile(dossier.append(to_string(9)).append("Rapide").append(fin_nom), IntRect(10, 25, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[9+15*i].loadFromFile(dossier.append(to_string(10)).append("Rapide").append(fin_nom), IntRect(0, 10, 120, 190)))
			exit(EXIT_FAILURE);	
		dossier = "images/";
		if (!this->texture[10+15*i].loadFromFile(dossier.append("Face").append(fin_nom),IntRect(0, 10, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[11+15*i].loadFromFile(dossier.append("bas").append(fin_nom), IntRect(0, 0, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[12+15*i].loadFromFile(dossier.append("saut1").append(fin_nom), IntRect(0, 15, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[13+15*i].loadFromFile(dossier.append("saut2").append(fin_nom), IntRect(0, 5, 120, 190)))
			exit(EXIT_FAILURE);
		dossier = "images/";
		if (!this->texture[14+15*i].loadFromFile(dossier.append("blesse").append(fin_nom), IntRect(0, 0, 120, 190)))
			exit(EXIT_FAILURE);	
	}
}

void Robot::message()
{
	cout<<"La partie peut commencer !"<<endl;
}

int Robot::getStatus() const {return state;}
int Robot::getNbFrame() const {return nbFrame;}
int Robot::getHauteurSaut() const {return hauteurSaut;}
bool Robot::getEnPleinJump() const {return enPleinJump;}
bool Robot::getEnPleinGrandissement() const {return enPleinGrandissement;};
bool Robot::getEnPleinRapetissement() const {return enPleinRapetissement;};
bool Robot::getTir() const {return tir;};
int Robot::getTaille() const {return taille;};
float Robot::getMinScale() const {return min_scale;};
float Robot::getMaxScale() const {return max_scale;};
Sprite Robot::getSprite() const {return sprite;};
int Robot::getPv() const {return pv;};
int Robot::getTimerBlesse() const {return timerBlesse;};
string Robot::getName() const {return _name;};
int Robot::getIncrementLeft() const {return increment_left;};

void Robot::setPv(int nbVie) {this->pv = nbVie;};
void Robot::setNbFrame(int nbreF) {this->nbFrame = nbreF;};
void Robot::setRobotActuel(Texture robAct) {this->robotActuel = robAct;};
void Robot::setStatus(int etat) {this->state = etat;};
void Robot::setTimerBlesse(int t) {this->timerBlesse = t;};
void Robot::setTir(bool var) {this->tir = var;};
void Robot::setPosSprite(float x, float y) {this->sprite.setPosition(x, y);};
void Robot::setEnPleinJump(bool a) {this->enPleinJump = a;};
void Robot::setHauteurSaut(int h) {this->hauteurSaut = h;};
void Robot::setTextRect(float w, float h) {this->sprite.setTextureRect(IntRect(0, 0, w, h));};

IntRect Robot::getRectRobot() const
{
    IntRect rectRobot;
    rectRobot.left = sprite.getPosition().x;
    rectRobot.width = sprite.getPosition().x + sprite.getLocalBounds().width * sprite.getScale().x;
    rectRobot.top = sprite.getPosition().y;
    rectRobot.height = sprite.getPosition().y + sprite.getLocalBounds().height * sprite.getScale().y;
    return rectRobot;
}

Texture Robot::getTexture(int indice) const {return texture[indice];}



