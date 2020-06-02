#include "catch.hpp"
#include <SFML/Graphics.hpp>

#include "balle.hpp"

TEST_CASE( "Balle can be created", "[balle]" ) {

    Balle balle(48, 649, true, 0);

    // Tests constructeur
    REQUIRE( balle.getX() == 48 );
    REQUIRE( balle.getSprite().getPosition().y == 649 );
    REQUIRE( balle.getID() == 0 );
    REQUIRE( balle.getDir() == true );
    
    // Tests constructeur par copie
    Balle balleCopy(balle);
    REQUIRE( balle.getX() == balleCopy.getX() );
    REQUIRE( balle.getSprite().getPosition().y == balleCopy.getSprite().getPosition().y );
    REQUIRE( balle.getID() == balleCopy.getID() );
    REQUIRE( balle.getDir() == balleCopy.getDir() );
    

    SECTION( "Test action/déplacement de la balle" ) {
    	 float posXPrec(balle.getX()); // Les balles ne se déplacent que selon l'axe des x
    	 balle.action(); // Déplacement vers la droite
    	 REQUIRE( posXPrec < balle.getX() );
    	 
    	 balle.setDir(false);
    	 posXPrec = balle.getX();
    	 balle.action(); // Déplacement vers la gauche
    	 REQUIRE( posXPrec > balle.getX() );
    }
    

}

