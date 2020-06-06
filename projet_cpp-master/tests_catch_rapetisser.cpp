#include "catch.hpp"

#include "rapetisser.hpp"

using namespace std;
using namespace sf;

TEST_CASE( "Rapetisser can be created", "[rapetisser]" ) {

    Rapetisser rapetisser;

    // Tests constructeur
    REQUIRE( rapetisser.getSpriteStable() == false );
    REQUIRE( rapetisser.getSprite().getPosition().y == 0 );



    SECTION( "Test activation du rapetissement" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 r.setEnPleinGrandissement(true);
    	 r.setTaille(GRAND);
    	 r.setTimerGrand(12);
    	 r.setMinScale(1);
    	 
    	 REQUIRE( r.getEnPleinGrandissement() == true );
    	 REQUIRE( r.getMinScale() == 1 );
    	 REQUIRE( r.getEnPleinRapetissement() == false );
    	 REQUIRE( r.getTaille() == GRAND );
    	 REQUIRE( r.getTimerGrand() < TIMER_GRAND );
    	 
    	 rapetisser.activation(r);
    	 REQUIRE( r.getEnPleinGrandissement() == false );
    	 REQUIRE( r.getMinScale() == 0.5 );
    	 REQUIRE( r.getEnPleinRapetissement() == true );
    	 REQUIRE( r.getTimerGrand() == TIMER_GRAND );
    	 r.vider();
    }
    
    SECTION( "Test du polymorphisme avec la fonction activation du rapetissement" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 r.setEnPleinGrandissement(true);
    	 r.setTaille(GRAND);
    	 r.setTimerGrand(12);
    	 r.setMinScale(1);
    	 Collectable *collec = new Rapetisser();
    	 
    	 REQUIRE( r.getEnPleinGrandissement() == true );
    	 REQUIRE( r.getMinScale() == 1 );
    	 REQUIRE( r.getEnPleinRapetissement() == false );
    	 REQUIRE( r.getTaille() == GRAND );
    	 REQUIRE( r.getTimerGrand() < TIMER_GRAND );
    	 
    	 collec->activation(r);
    	 REQUIRE( r.getEnPleinGrandissement() == false );
    	 REQUIRE( r.getMinScale() == 0.5 );
    	 REQUIRE( r.getEnPleinRapetissement() == true );
    	 REQUIRE( r.getTimerGrand() == TIMER_GRAND );
    	 r.vider();
    	 delete collec;
    }

}

