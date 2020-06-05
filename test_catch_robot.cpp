#define CATCH_CONFIG_MAIN // Must only appear in ONE test file
#include "catch.hpp"

#include "robot.hpp"

using namespace std;
using namespace sf;

TEST_CASE( "Robots can be created", "[robot]" ) {

    Robot r("Joueur1", 0, HUMAIN);
    Robot r2("Joueur2", 0, HUMAIN);


    // Tests constructeur
    REQUIRE( r.getName() == "Joueur1" );
    REQUIRE( r.getPv() == 25 );
    REQUIRE( r.getTaille() == STANDARD );

    REQUIRE( r2.getName() == "Joueur2" );
    REQUIRE( r2.getPv() == 25 );



    SECTION( "Write accessors" ) {
        r.setPv(10);
        r.setStatus(NORMAL);
        r.setTaille(PETIT);
        r.setMunitions(3);
        REQUIRE( r.getPv() == 10 );
        REQUIRE( r.getStatus() == NORMAL );
        REQUIRE( r.getTaille() == PETIT );
        REQUIRE( r.getMunitions() == 3 );
    }
    
    SECTION( "Test resetRobot" ) {
        r.setPv(10);
        r.setStatus(DOWN);
        r.setTaille(PETIT);
        r.setHauteurSaut(236);
        r.setMunitions(1);
        r.setNbFrame(13);
        r.setTimerBlesse(2);
        r.setTimerBouclier(66);
        r.setTimerTir(11);
        .setTimerPetit(74);
        r.setPosSprite(534, 185);
        r.getSprite().setScale(0.5);
        REQUIRE( r.getPv() == 10 );
        REQUIRE( r.getStatus() == DOWN );
        REQUIRE( r.getTaille() == PETIT );
        REQUIRE( r.getHauteurSaut() == 236 );
        REQUIRE( r.getNbFrame() == 13);
        REQUIRE( r.getTimerBlesse() == 2 );
        REQUIRE( r.getTimerBouclier() == 66 );
        REQUIRE( r.getTimerTir() == 11 );
        REQUIRE( r.setTimerPetit() == 74 );
        REQUIRE( r.getX() == 534 );
        REQUIRE( r.getY() == 185 );
        REQUIRE( r.getSprite().getScale() == 0.5 );
        
        r.resetRobot();
        
        REQUIRE( r.getPv() == PV_MAX );
        REQUIRE( r.getStatus() == NORMAL );
        REQUIRE( r.getTaille() == STANDARD );
        REQUIRE( r.getHauteurSaut() == 500 );
        REQUIRE( r.getNbFrame() == 0);
        REQUIRE( r.getTimerBlesse() == TIMER_BLESSE );
        REQUIRE( r.getTimerBouclier() == TIMER_BOUCLIER );
        REQUIRE( r.getTimerTir() == 0 );
        REQUIRE( r.setTimerPetit() == TIMER_PETIT );
        REQUIRE( r.getX() == 20 );
        REQUIRE( r.getY() == POS_SOL-HAUTEUR_ROBOT );
        REQUIRE( r.getSprite().getScale() == 1 );
    }
    
    SECTION( "Test rapetisser" ) {
    	float scalePrecX = r.getSprite().getScale().x;
    	float scalePrecY = r.getSprite().getScale().y;
        r.rapetisser();
        REQUIRE( r.getSprite().getScale().x < scalePrecX );
        REQUIRE( r.getSprite().getScale().y < scalePrecY );
    }
    
    SECTION( "Test grandir" ) {
        float scalePrecX = r.getSprite().getScale().x;
    	float scalePrecY = r.getSprite().getScale().y;
        r.grandir();
        REQUIRE( r.getSprite().getScale().x > scalePrecX );
        REQUIRE( r.getSprite().getScale().y > scalePrecY );
    }
    
    SECTION( "Test saut" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.sauter(0.5);
        REQUIRE( r.getRectRobot().top < rectPrec.top ); // L'axe des y étant descendant
        REQUIRE( r.getRectRobot().left == rectPrec.left );
        REQUIRE( r.getRectRobot().width == rectPrec.width );
        REQUIRE( r.getRectRobot().height < rectPrec.height );
    }
    
    SECTION( "Test move à droite" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.setStatus(WALK_RIGHT);
        r.move(0.1);
        REQUIRE( r.getRectRobot().top == rectPrec.top );
        REQUIRE( r.getRectRobot().left > rectPrec.left );
        REQUIRE( r.getRectRobot().width > rectPrec.width );
        REQUIRE( r.getRectRobot().height == rectPrec.height );
    }
    
    SECTION( "Test move à gauche" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.setStatus(WALK_LEFT);
        r.move(0.1);
        REQUIRE( r.getRectRobot().top == rectPrec.top );
        REQUIRE( r.getRectRobot().left < rectPrec.left );
        REQUIRE( r.getRectRobot().width < rectPrec.width );
        REQUIRE( r.getRectRobot().height == rectPrec.height );
    }
    
    SECTION( "Test personnage baissé" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.setStatus(DOWN);
        r.move(0.1);
        REQUIRE( r.getRectRobot().top > rectPrec.top ); // L'axe des y étant descendant
        REQUIRE( r.getRectRobot().left == rectPrec.left );
        REQUIRE( r.getRectRobot().width == rectPrec.width );
        REQUIRE( r.getRectRobot().height > rectPrec.height );
    }
    
    SECTION( "Test timer paralysé" ) {
    	int timerDebut = r.getTimerBlesse();
    	r.setStatus(BLESSE);
        r.blessure();
        REQUIRE( r.getTimerBlesse() < timerDebut ); // Le temps se décrémente bien
        REQUIRE( r.getStatus() == BLESSE );
        
        r.getTimerBlesse(0);
        r.blessure();
        REQUIRE( r.getTimerBlesse() == TIMER_BLESSE ); // On recharge le timer
        REQUIRE( r.getStatus() == NORMAL ); // Le robot retrouve son état normal
    }
    
    SECTION( "Test timer bouclier" ) {
    	int timerDebut = r.getTimerBouclier();
    	r.setBouclier(true);
        r.actionBouclier();
        REQUIRE( r.getTimerBouclier() < timerDebut ); // Le temps se décrémente bien
        
        r.setTimerBouclier(0);
        r.actionBouclier();
        REQUIRE( r.getTimerBouclier() == TIMER_BLOUCLIER ); // Le temps se décrémente bien
        REQUIRE( r.getBouclier() == false );
    }
    
    SECTION( "Test gestion des munitions" ) {
        REQUIRE( r.getMunitions() == 5 ); // Le nombre de munition est initialisé à 5
        
        r.setMunitions(1);
        r.gestionMunitions(); // Le nombre de munitions est inchangé car il en reste encore
        REQUIRE( r.getMunitions() == 1 );
        
        r.effacerMunition();
        r.gestionMunitions(); // Rechargement des munitions
        REQUIRE( r.getMunitions() == 5 );
    }
    
    r.vider();
    r2.vider();
}

