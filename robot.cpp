#include "robot.hpp"

using namespace std;
using namespace sf;

Robot::Robot(string name, int id, Type type){
	_name = name;
	ID = id;
	vitesse = 300;
	taille = STANDARD;
	hauteurSaut = 500;
	nbFrame = 0;
	chargement_image();
	gestionMunitions();
	if(ID == 0)
	{
		if (type == HUMAIN)
			joueur = new Humain(0);
		else
			joueur = new Ia(0);
  		sprite.setPosition(Vector2f(20.f, POS_SOL-HAUTEUR_ROBOT)); // Choix de la position du sprite
  		robotActuel = texture[10];
		direction = true;
	}
	else
	{
		if (type == HUMAIN)
			joueur = new Humain(1);
		else
			joueur = new Ia(1);
		sprite.setPosition(Vector2f(TAILLE_WINDOW_X - LARGEUR_ROBOT - 20.f, POS_SOL-HAUTEUR_ROBOT));
		increment_left = NI;
		robotActuel = texture[10+increment_left];
		direction = false;
	}
	sprite.setScale(1.f, 1.f);
	sprite.setTexture(robotActuel);
  	sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, HAUTEUR_ROBOT));
}

void Robot::resetRobot()
{
	taille = STANDARD;
	hauteurSaut = 500;
	nbFrame = 0;
	setMunitions(5);
	pv = PV_MAX;
	state = NORMAL;
	enPleinJump = false;
	aGenoux = false;
	enPleinGrandissement = false;
	enPleinRapetissement = false;
	timerGrand = TIMER_GRAND;
	timerPetit = TIMER_PETIT;
	timerBlesse = TIMER_BLESSE;
  	timerTir = 0;
  	timerBouclier = TIMER_BOUCLIER;
	taillePrec = 0;
	bouclier = false;
	if(ID == 0)
	{
		sprite.setPosition(Vector2f(20.f, POS_SOL-HAUTEUR_ROBOT)); // Choix de la position du sprite
  		robotActuel = texture[10];
		direction = true;
	}
	else
	{
		sprite.setPosition(Vector2f(TAILLE_WINDOW_X - LARGEUR_ROBOT - 20.f, POS_SOL-HAUTEUR_ROBOT));
		increment_left = NI;
		robotActuel = texture[10+increment_left];
		direction = false;
	}
	sprite.setScale(1.f, 1.f);
	sprite.setTexture(robotActuel);
  	sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, HAUTEUR_ROBOT));
}

bool Robot::choix_Present(vector<Touche> v, Touche to)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == to)
			return true;
	}
	return false;
}

void Robot::detect_KeyPressed()
{
	vector<Touche> choix = joueur->detect_Choix();
	if ((ID == 0) && (state != BLESSE))
	// Le joueur ne peut rien faire s'il est blessé ou juste après avoir tiré
	{
		if (choix_Present(choix, RIGHT))
		{
			if (state != WALK_RIGHT)
				increment_left = 0;
		    state = WALK_RIGHT;
			direction = true;
	    }
		else if (choix_Present(choix, LEFT))
		{
			if (state != WALK_LEFT)
				increment_left = NI;
		    state = WALK_LEFT;
			direction = false;
	    }
		else if (choix_Present(choix, DOWN1))
		    state = DOWN;
		else
			state = NORMAL;

		if (choix_Present(choix, UP))
		    enPleinJump = true;

		if (choix_Present(choix, SHOOT))
		{
		  	robotActuel = texture[15+increment_left];
			state = TIRER;
    	}
	}
  	else if ((ID == 1) && (state != BLESSE))  // Le joueur ne peut rien faire s'il est blessé
    {
		if (choix_Present(choix, RIGHT1))
		{
			if (state != WALK_RIGHT)
				increment_left = 0;
		    state = WALK_RIGHT;
			direction = true;
	    }
		else if (choix_Present(choix, LEFT1))
		{
			if (state != WALK_LEFT)
				increment_left = NI;
		    state = WALK_LEFT;
			direction = false;
	    }
		else if (choix_Present(choix, DOWN2))
		    state = DOWN;
		else
			state = NORMAL;

		if (choix_Present(choix, UP1))
		    enPleinJump = true;

		if (choix_Present(choix, SHOOT1))
		{
		  	robotActuel = texture[15+increment_left];
			state = TIRER;
    	}
	}
}


void Robot::move(float elapsed)
{
	if(timerTir > 0){
		timerTir--;
	}

    if ((aGenoux == true) && (state != DOWN))  // Si le robot était baissé sur la frame précédente et qu'il se relève, alors on remonte le robot
    {
    	sprite.move(Vector2f(0, -20.f*sprite.getScale().y));
        aGenoux = false;
    }

	if (state == WALK_RIGHT && sprite.getPosition().x < TAILLE_WINDOW_X-LARGEUR_ROBOT)  // Si le robot n'est pas hors de la fenêtre à droite
    {
        sprite.move(Vector2f(vitesse*elapsed, 0));  // Déplacement par rapport à la position actuelle
        (nbFrame)++;
        if(nbFrame == 10)
	        nbFrame = 0;
        robotActuel = texture[nbFrame];
	}
    else if (state == WALK_LEFT && sprite.getPosition().x > 0)  // Si le robot n'est pas hors de la fenêtre à gauche
    {
    	sprite.move(Vector2f(-vitesse*elapsed, 0));  // Déplacement vers la gauche
    	(nbFrame)++;
    	if(nbFrame == 10)
    		nbFrame = 0;
    	robotActuel = texture[nbFrame+increment_left];
	}
	else if ((state == DOWN) && (aGenoux == false))
	{
	    robotActuel = texture[11+increment_left];
	    sprite.move(Vector2f(0.f, 20.f*sprite.getScale().y)); // Le robot se baisse
        aGenoux = true;
	}
	else if (state == NORMAL)
	    robotActuel = texture[10+increment_left];

    if (enPleinJump == true)
    	sauter(elapsed);
}


void Robot::sauter(float elapsed)
{
    hauteurSaut += GRAVITE;
    sprite.move(Vector2f(0.f, -(hauteurSaut)*elapsed));
    if ((hauteurSaut >= 0) && (state != DOWN))
    {
    	if(state==TIRER){
			robotActuel = texture[16+increment_left];
		} else {
			robotActuel = texture[12+increment_left];
		}
        sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, 160)); // Le Sprite du robot qui saute est plus grand que ceux du robot au sol
    }
    else if ((hauteurSaut < 0) && (state != DOWN))
    {
    	if(state==TIRER){
			robotActuel = texture[17+increment_left];
		} else {
			robotActuel = texture[13+increment_left];
		}
        sprite.setTextureRect(IntRect(0, 0, LARGEUR_ROBOT, 160));
    }
}


void Robot::grandir()
{
    if (taillePrec == 0)
        taillePrec = sprite.getLocalBounds().height*sprite.getScale().y;  // Récupère la hauteur du sprite initial

    if ((sprite.getScale().x*1.1 <= max_scale) && (taille != GRAND))  // Si le robot est en plein changement de taille
    {
        sprite.scale(Vector2f(1.1f, 1.1f));  // Modifie l'échelle par rapport à l'échelle actuelle
        sprite.move(Vector2f(0.f, -taillePrec*0.1));
        taillePrec *= 1.1;
    }
    else
    {
        enPleinGrandissement = false;
        taillePrec = 0;
        if (max_scale == 1.0)
        {
            taille = STANDARD;
            sprite.move(Vector2f(0.f, sprite.getLocalBounds().height*(sprite.getScale().y-1)));
            sprite.setScale(Vector2f(1.f, 1.f));
        }
        else
            taille = GRAND;
    }

    if (taille == GRAND)
        timerGrand--;

    if ((timerGrand <= 0) && (taille == GRAND))
    {
        enPleinRapetissement = true;
        min_scale = 1.0;
        timerGrand = TIMER_GRAND;
    }
}

void Robot::rapetisser()
{
    if (taillePrec == 0)
        taillePrec = sprite.getLocalBounds().height*sprite.getScale().y;  // Récupère la hauteur du sprite initial

    if ((sprite.getScale().x*0.9 >= min_scale) && (taille != PETIT))  // Si le robot est en plein changement de taille
    {
        sprite.scale(Vector2f(0.9f, 0.9f));  // Modifie l'échelle par rapport à l'échelle actuelle
        sprite.move(Vector2f(0.f, taillePrec*0.1));
        taillePrec *= 0.9;
    }
    else
    {
        enPleinRapetissement = false;
        taillePrec = 0;
        if (min_scale == 1.0)  // Si le robot retourne à la taille standard
        {
            taille = STANDARD;
            sprite.move(Vector2f(0.f, sprite.getLocalBounds().height*(sprite.getScale().y-1)));
            sprite.setScale(Vector2f(1.f, 1.f));
        }
        else
            taille = PETIT;
    }

    if (taille == PETIT)  // Si le robot a atteint la petite taille alors on lance le timer
        timerPetit--;

    if ((timerPetit <= 0) && (taille == PETIT))
    {
        enPleinGrandissement = true;
        max_scale = 1.0;
        timerPetit = TIMER_PETIT;
    }
}

void Robot::blessure()  // Le robot est paralysé pendant un certain temps
{
    timerBlesse--;
    if (timerBlesse <= 0)
    {
        state = NORMAL;
        timerBlesse = TIMER_BLESSE;
        nbFrame = 0;
    }
}

void Robot::actionBouclier()
{
	timerBouclier--;
	if (timerBouclier <= 0)
	{
		timerBouclier = TIMER_BOUCLIER;
		bouclier = false;
	}
}

void Robot::gestionMunitions()
{
	if (nbMunitions == 0)
		nbMunitions = 5;
}

void Robot::effacerMunition()
{
	nbMunitions--;
}

void Robot::chargement_image()
{
	string fin_nom;
	string dossier("images/");
	for (int i = 0; i < 2; i++)
	{
		if (_name == "Joueur1")
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

	    if (!texture[0+NI*i].loadFromFile(dossier+to_string(1)+"Rapide"+fin_nom, IntRect(0, 0, 100, 190)))
	    	exit(EXIT_FAILURE);
    	if (!texture[1+NI*i].loadFromFile(dossier+to_string(2)+"Rapide"+fin_nom, IntRect(0, 0, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[2+NI*i].loadFromFile(dossier+to_string(3)+"Rapide"+fin_nom, IntRect(5, 25, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[3+NI*i].loadFromFile(dossier+to_string(4)+"Rapide"+fin_nom, IntRect(10, 30, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[4+NI*i].loadFromFile(dossier+to_string(5)+"Rapide"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[5+NI*i].loadFromFile(dossier+to_string(6)+"Rapide"+fin_nom, IntRect(0, 20, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[6+NI*i].loadFromFile(dossier+to_string(7)+"Rapide"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[7+NI*i].loadFromFile(dossier+to_string(8)+"Rapide"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[8+NI*i].loadFromFile(dossier+to_string(9)+"Rapide"+fin_nom, IntRect(10, 25, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[9+NI*i].loadFromFile(dossier+to_string(10)+"Rapide"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[10+NI*i].loadFromFile(dossier+"Face"+fin_nom,IntRect(5, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[11+NI*i].loadFromFile(dossier+"bas"+fin_nom))
			exit(EXIT_FAILURE);
		if (!texture[12+NI*i].loadFromFile(dossier+"saut1"+fin_nom, IntRect(0, 15, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[13+NI*i].loadFromFile(dossier+"saut2"+fin_nom, IntRect(0, 5, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[14+NI*i].loadFromFile(dossier+"blesse"+fin_nom))
			exit(EXIT_FAILURE);
		if (!texture[15+NI*i].loadFromFile(dossier+"Tirer"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[16+NI*i].loadFromFile(dossier+"sautTirer1"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
		if (!texture[17+NI*i].loadFromFile(dossier+"sautTirer2"+fin_nom, IntRect(0, 10, 100, 190)))
			exit(EXIT_FAILURE);
	}
}

void Robot::vider()
{
	delete joueur;
}

Etat Robot::getStatus() const {return state;}
int Robot::getNbFrame() const {return nbFrame;}
int Robot::getHauteurSaut() const {return hauteurSaut;}
bool Robot::getEnPleinJump() const {return enPleinJump;}
bool Robot::getEnPleinGrandissement() const {return enPleinGrandissement;};
bool Robot::getEnPleinRapetissement() const {return enPleinRapetissement;};
TailleRob Robot::getTaille() const {return taille;};
float Robot::getMinScale() const {return min_scale;};
float Robot::getMaxScale() const {return max_scale;};
Sprite Robot::getSprite() const {return sprite;};
int Robot::getPv() const {return pv;};
int Robot::getTimerBlesse() const {return timerBlesse;};
string Robot::getName() const {return _name;};
int Robot::getIncrementLeft() const {return increment_left;};
bool Robot::getDirection() const {return direction;};
float Robot::getX() const {return sprite.getPosition().x;};
float Robot::getY() const {return sprite.getPosition().y;};
int Robot::getID() const {return ID;};
int Robot::getTimerTir() const {return timerTir;};
bool Robot::getBouclier() const {return bouclier;};
int Robot::getMunitions() const {return nbMunitions;};
int Robot::getTimerBouclier() const {return timerBouclier;};
int Robot::getTimerPetit() const {return timerPetit;};
int Robot::getTimerGrand() const {return timerGrand;};

void Robot::setPv(int nbVie) {pv = nbVie;};
void Robot::setNbFrame(int nbreF) {nbFrame = nbreF;};
void Robot::setRobotActuel(Texture robAct) {robotActuel = robAct;};
void Robot::setStatus(Etat etat) {state = etat;};
void Robot::setTimerBlesse(int t) {timerBlesse = t;};
void Robot::setPosSprite(float x, float y) {sprite.setPosition(x, y);};
void Robot::setEnPleinJump(bool a) {enPleinJump = a;};
void Robot::setHauteurSaut(int h) {hauteurSaut = h;};
void Robot::setTextRect(float w, float h) {sprite.setTextureRect(IntRect(0, 0, w, h));};
void Robot::setEnPleinGrandissement(bool r) {enPleinGrandissement = r;};
void Robot::setEnPleinRapetissement(bool r) {enPleinRapetissement = r;};
void Robot::resetTimerTir() {timerTir = TIMER_TIR;};
void Robot::setTimerTir(int a) {timerTir = a;};
void Robot::setTimerPetit(int a) {timerPetit = a;};
void Robot::setTimerGrand(int a) {timerGrand = a;};
void Robot::setTimerBouclier(int t) {timerBouclier = t;};
void Robot::setMinScale(float min) {min_scale = min;};
void Robot::setMaxScale(float max) {max_scale = max;};
void Robot::setBouclier(bool a) {bouclier = a;};
void Robot::setMunitions(int nbM) {nbMunitions = nbM;};
void Robot::setTaille(TailleRob t) {taille = t;};

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
