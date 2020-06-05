#include "catch.hpp"

#include "bouclier.hpp"

using namespace std;
using namespace sf;

TEST_CASE( "Bouclier can be created", "[bouclier]" ) {

    Bouclier bouclier;

    // Tests constructeur
    REQUIRE( bouclier.getSpriteStable() == false );
    REQUIRE( bouclier.getSprite().getPosition().y == 0 );



    SECTION( "Test activation du bouclier" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 REQUIRE( r.getBouclier() == false );
    	 REQUIRE( r.getTimerBouclier() == TIMER_BOUCLIER );
    	 
    	 bouclier.activation(r);
    	 REQUIRE( r.getBouclier() == true );
    	 REQUIRE( r.getTimerBouclier() < TIMER_BOUCLIER );
    	 r.vider();
    }
    
    SECTION( "Test du polymorphisme avec la fonction activation du bouclier" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 Collectable *collec = new Bouclier();
    	 REQUIRE( r.getBouclier() == false );
    	 REQUIRE( r.getTimerBouclier() == TIMER_BOUCLIER );
    	 
    	 collec->activation(r);
    	 REQUIRE( r.getBouclier() == true );
    	 REQUIRE( r.getTimerBouclier() < TIMER_BOUCLIER );
    	 r.vider();
    	 delete collec;
    }
    
    SECTION( "Test de la formation du bouclier" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 CircleShape protect = bouclier.formationBouclier(r);
    	 REQUIRE( (int)protect.getRadius() == (int)sqrt(pow(HAUTEUR_ROBOT, 2) + pow(LARGEUR_ROBOT, 2))/2 );
    	 REQUIRE( protect.getPosition().x == r.getX()+LARGEUR_ROBOT/2-protect.getRadius() );
    	 REQUIRE( floor(protect.getPosition().y) == ceil(r.getY()+HAUTEUR_ROBOT/2-protect.getRadius()) );
    	 REQUIRE( protect.getFillColor().r == 255 );
    	 REQUIRE( protect.getFillColor().g == 0 );
    	 REQUIRE( protect.getFillColor().b == 0 );
    	 REQUIRE( protect.getFillColor().a == 50 );
    	 r.vider();
    	 
    	 Robot r2("Joueur2", 1, HUMAIN);
    	 protect = bouclier.formationBouclier(r2);
    	 REQUIRE( (int)protect.getRadius() == (int)sqrt(pow(HAUTEUR_ROBOT, 2) + pow(LARGEUR_ROBOT, 2))/2 );
    	 REQUIRE( protect.getPosition().x == r2.getX()+LARGEUR_ROBOT/2-protect.getRadius() );
    	 REQUIRE( floor(protect.getPosition().y) == ceil(r2.getY()+HAUTEUR_ROBOT/2-protect.getRadius()) );
    	 REQUIRE( protect.getFillColor().r == 0 );
    	 REQUIRE( protect.getFillColor().g == 0 );
    	 REQUIRE( protect.getFillColor().b == 255 );
    	 REQUIRE( protect.getFillColor().a == 50 );
    	 r2.vider();
    }

}

