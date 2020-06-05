#include "catch.hpp"

#include "reparer.hpp"

using namespace std;
using namespace sf;

TEST_CASE( "Reparer can be created", "[reparer]" ) {

    Reparer reparer;

    // Tests constructeur
    REQUIRE( reparer.getSpriteStable() == false );
    REQUIRE( reparer.getSprite().getPosition().y == 0 );



    SECTION( "Test activation de la réparation" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 r.setPv(1);
    	 REQUIRE( r.getPv() == 1 );
    	 
    	 reparer.activation(r);
    	 REQUIRE( r.getPv() == 4 );
    	 
    	 r.setPv(23);
    	 REQUIRE( r.getPv() == 23 );
    	 REQUIRE( r.getPv() < PV_MAX );
    	 
    	 reparer.activation(r);
    	 REQUIRE( r.getPv() == PV_MAX );
    	 
    	 r.vider();
    }
    
    SECTION( "Test du polymorphisme avec la fonction activation de la réparation" ) {
    	 Robot r("Joueur1", 0, HUMAIN);
    	 r.setPv(1);
    	 Collectable *collec = new Reparer();
    	 
    	 REQUIRE( r.getPv() == 1 );
    	 
    	 reparer.activation(r);
    	 REQUIRE( r.getPv() == 4 );
    	 
    	 r.setPv(23);
    	 REQUIRE( r.getPv() == 23 );
    	 REQUIRE( r.getPv() < PV_MAX );
    	 
    	 reparer.activation(r);
    	 REQUIRE( r.getPv() == PV_MAX );

    	 r.vider();
    	 delete collec;
    }

}

