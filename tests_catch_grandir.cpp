#include "catch.hpp"

#include "grandir.hpp"

using namespace std;
using namespace sf;

TEST_CASE( "Grandir can be created", "[grandir]" ) {

    Grandir grandir;

    // Tests constructeur
    REQUIRE( grandir.getSpriteStable() == false );
    REQUIRE( grandir.getSprite().getPosition().y == 0 );



    SECTION( "Test activation du grandissement" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 r.setEnPleinRapetissement(true);
    	 r.setTaille(PETIT);
    	 r.setTimerPetit(12);
    	 r.setMaxScale(1);
    	 
    	 REQUIRE( r.getEnPleinGrandissement() == false );
    	 REQUIRE( r.getMaxScale() == 1 );
    	 REQUIRE( r.getEnPleinRapetissement() == true );
    	 REQUIRE( r.getTaille() == PETIT );
    	 REQUIRE( r.getTimerPetit() < TIMER_PETIT );
    	 
    	 grandir.activation(r);
    	 REQUIRE( r.getEnPleinGrandissement() == true );
    	 REQUIRE( r.getMaxScale() == 2 );
    	 REQUIRE( r.getEnPleinRapetissement() == false );
    	 REQUIRE( r.getTimerPetit() == TIMER_PETIT );
    	 r.vider();
    }
    
    SECTION( "Test du polymorphisme avec la fonction activation du grandissement" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 r.setEnPleinRapetissement(true);
    	 r.setTaille(PETIT);
    	 r.setTimerPetit(12);
    	 r.setMaxScale(1);
    	 Collectable *collec = new Grandir();
    	 
    	 REQUIRE( r.getEnPleinGrandissement() == false );
    	 REQUIRE( r.getMaxScale() == 1 );
    	 REQUIRE( r.getEnPleinRapetissement() == true );
    	 REQUIRE( r.getTaille() == PETIT );
    	 REQUIRE( r.getTimerPetit() < TIMER_PETIT );
    	 
    	 collec->activation(r);
    	 REQUIRE( r.getEnPleinGrandissement() == true );
    	 REQUIRE( r.getMaxScale() == 2 );
    	 REQUIRE( r.getEnPleinRapetissement() == false );
    	 REQUIRE( r.getTimerPetit() == TIMER_PETIT );
    	 r.vider();
    	 delete collec;
    }

}

