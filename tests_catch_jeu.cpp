#include "catch.hpp"
#include <SFML/Graphics.hpp>

#include "jeu.hpp"
using namespace std;
using namespace sf;

TEST_CASE( "Jeu can be created", "[Jeu]" ) {

    Jeu jeu;

    // Test constructeur
    REQUIRE( jeu.getTab().size() == 0 );
    

    

    SECTION( "Test gestionTirs" ) {
    	 Robot r("Joueur1");
    	 
    	 jeu.gestionTirs(r);
    	 REQUIRE( jeu.getTab().size() == 0 );
    	 REQUIRE( r.getMunitions() == 5 );
    	 REQUIRE( r.getTimerTir() == 0 );
    	 
    	 r.setStatus(TIRER);
    	 r.setTimerTir(-15);
    	 jeu.gestionTirs(r);
    	 REQUIRE( jeu.getTab().size() == 1 );
    	 REQUIRE( r.getMunitions() == 4 );
    	 REQUIRE( r.getTimerTir() == TIMER_TIR );

    }
    
    SECTION( "Test updateActionRobot" ) {
    	 Robot r("Joueur1");
    	 sf::Sprite spPrec(r.getSprite());
    	 r.setEnPleinGrandissement(true);
    	 r.setMunitions(0);
    	 jeu.updateActionRobot(r);
    	 REQUIRE( r.getSprite().getScale().x > spPrec.getScale().x );
    	 REQUIRE( r.getMunitions() == 5 );
    	 
    	 r.setTaille(GRAND);
    	 r.setMunitions(0);
    	 jeu.updateActionRobot(r);
    	 REQUIRE( r.getTimerGrand() < TIMER_GRAND ); // Le temps se décrémente
    	 REQUIRE( r.getMunitions() == 5 );
    	 
    	 spPrec = sf::Sprite(r.getSprite());
    	 r.setEnPleinRapetissement(true);
    	 r.setMunitions(0);
    	 jeu.updateActionRobot(r);
    	 REQUIRE( r.getSprite().getScale().x < spPrec.getScale().x );
    	 REQUIRE( r.getMunitions() == 5 );
    	 
    	 r.setTaille(PETIT);
    	 r.setMunitions(0);
    	 jeu.updateActionRobot(r);
    	 REQUIRE( r.getTimerPetit() < TIMER_PETIT ); // Le temps se décrémente
    	 REQUIRE( r.getMunitions() == 5 );

    	 r.setStatus(WALK_RIGHT);
    	 jeu.setElapsed(0.1);
    	 spPrec = sf::Sprite(r.getSprite());
    	 r.setMunitions(0);
    	 jeu.updateActionRobot(r);
    	 REQUIRE( r.getX() > spPrec.getPosition().x ); // Le robot s'est déplacé vers la droite
    	 REQUIRE( r.getMunitions() == 5 );
    	 
    	 r.setStatus(BLESSE);
    	 r.setEnPleinRapetissement(true);
    	 spPrec = sf::Sprite(r.getSprite());
    	 r.setMunitions(0);
    	 jeu.updateActionRobot(r);
    	 REQUIRE( r.getX() == spPrec.getPosition().x ); // Le robot n'a pas bougé puisqu'il est blessé
     	 REQUIRE( r.getSprite().getScale().x == spPrec.getScale().x ); // Il ne peut même pas changer de taille
     	 REQUIRE( r.getMunitions() == 5 ); // Les munitions sont tout de même rechargées

    }
    
    SECTION( "Test gestionAttaques" ) {
    	 Robot r("Joueur1");
    	 Robot r2("Joueur2");
    	 
    	 r.setStatus(TIRER);
    	 r.setTimerTir(-15);
    	 jeu.gestionTirs(r);
    	 r.setTimerTir(-15);
    	 jeu.gestionTirs(r);
    	 REQUIRE( jeu.getTab().size() == 2 );
    	 
    	 r2.setPosSprite(500, r.getY());
    	 jeu.getTab()[0]->setX(500);
    	 sf::Sprite balPrec(jeu.getTab()[1]->getSprite());
    	 jeu.gestionAttaques(r2);
    	 REQUIRE( jeu.getTab().size() == 1 ); // La balle en collision avec le robot2 a été supprimée
    	 REQUIRE( jeu.getTab()[0]->getX() > balPrec.getPosition().x ); // La balle restante s'est déplacée vers la droite
    	 
    	 jeu.getTab()[0]->setX(-15); // La balle est hors de la fenêtre
    	 jeu.gestionAttaques(r2);
    	 REQUIRE( jeu.getTab().size() == 0 ); // Elle est donc supprimée
    	 
    	 r.setStatus(BLESSE);
    	 jeu.gestionAttaques(r);
    	 REQUIRE( r.getTimerBlesse() < TIMER_BLESSE ); // Le timer se décrémente

    }
    

}

