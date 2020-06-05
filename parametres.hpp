#ifndef PARAMETRES_HPP
#define PARAMETRES_HPP

enum Touche {RIGHT, LEFT, UP, DOWN1, SHOOT, RIGHT1, LEFT1, UP1, DOWN2, SHOOT1, RIEN};

enum Type {HUMAIN, IA};

enum Etat {NORMAL, WALK_LEFT, WALK_RIGHT, DOWN, BLESSE, TIRER};

enum TailleRob {PETIT, STANDARD, GRAND};

#define NI 18 // Nombre d'images dans un sens (robot profil droit par exemple)

#define HAUTEUR_ROBOT 135
#define LARGEUR_ROBOT 100

#define TAILLE_WINDOW_X 1000 // Taille de la fenêtre de jeu
#define TAILLE_WINDOW_Y 730 // Taille de la fenêtre de jeu

#define GRAVITE -10
#define POS_SOL 700

#define TIMER_BLESSE 30
#define TIMER_PETIT 300
#define TIMER_GRAND 300
#define TIMER_TIR 30
#define TIMER_BOUCLIER 500
#define TIMER_MAP 300

#define PV_MAX 25

#define NB_COLLECTABLE 4

#endif
