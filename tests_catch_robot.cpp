#define CATCH_CONFIG_MAIN // Must only appear in ONE test file
#include "catch.hpp"
#include <SFML/Graphics.hpp>
//Ou si installé par la distribution : #include <catch2/catch.hpp>

#include "robot.hpp"
using namespace std;
using namespace sf;

TEST_CASE( "Robots can be created", "[robot]" ) {

    // Pour chaque SECTION, cet initialisation est faite - voir https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#test-cases-and-sections
    // Et pour plus d'infos : https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md#type-parametrised-test-cases
    Robot r("Joueur1");
    Robot r2("Joueur2");


    // Tests constructeur
    REQUIRE(r.getName() == "Joueur1");
    REQUIRE(r.getPv() == 25);
    REQUIRE(r.getTaille() == STANDARD);

    REQUIRE(r2.getName() == "Joueur2");
    REQUIRE(r2.getPv() == 25);



    SECTION( "Write accessors" ) {
        r.setPv(10);
        r.setStatus(NORMAL);
        REQUIRE( r.getPv() == 10);
        REQUIRE( r.getStatus() == NORMAL);
    }
    
    SECTION( "Test rapetisser" ) {
    	float scalePrecX = r.getSprite().getScale().x;
    	float scalePrecY = r.getSprite().getScale().y;
        r.rapetisser();
        REQUIRE( r.getSprite().getScale().x < scalePrecX);
        REQUIRE( r.getSprite().getScale().y < scalePrecY);
    }
    
    SECTION( "Test grandir" ) {
        float scalePrecX = r.getSprite().getScale().x;
    	float scalePrecY = r.getSprite().getScale().y;
        r.grandir();
        REQUIRE( r.getSprite().getScale().x > scalePrecX);
        REQUIRE( r.getSprite().getScale().y > scalePrecY);
    }
    
    SECTION( "Test saut" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.sauter(0.5);
        REQUIRE( r.getRectRobot().top < rectPrec.top);  // L'axe des y étant descendant
        REQUIRE( r.getRectRobot().left == rectPrec.left);
        REQUIRE( r.getRectRobot().width == rectPrec.width);
        REQUIRE( r.getRectRobot().height < rectPrec.height);
    }
    
    SECTION( "Test move à droite" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.setStatus(WALK_RIGHT);
        r.move(0.1);
        REQUIRE( r.getRectRobot().top == rectPrec.top);
        REQUIRE( r.getRectRobot().left > rectPrec.left);
        REQUIRE( r.getRectRobot().width > rectPrec.width);
        REQUIRE( r.getRectRobot().height == rectPrec.height);
    }
    
    SECTION( "Test move à gauche" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.setStatus(WALK_LEFT);
        r.move(0.1);
        REQUIRE( r.getRectRobot().top == rectPrec.top);
        REQUIRE( r.getRectRobot().left < rectPrec.left);
        REQUIRE( r.getRectRobot().width < rectPrec.width);
        REQUIRE( r.getRectRobot().height == rectPrec.height);
    }
    
    SECTION( "Test personnage baissé" ) {
    	IntRect rectPrec = r.getRectRobot();
        r.setStatus(DOWN);
        r.move(0.1);
        REQUIRE( r.getRectRobot().top > rectPrec.top);  // L'axe des y étant descendant
        REQUIRE( r.getRectRobot().left == rectPrec.left);
        REQUIRE( r.getRectRobot().width == rectPrec.width);
        REQUIRE( r.getRectRobot().height > rectPrec.height);
    }
    
    SECTION( "Test timer paralysé" ) {
    	int timerDebut = r.getTimerBlesse();
        r.blessure();
        REQUIRE( r.getTimerBlesse() < timerDebut); // Le temps se décrémente bien
    }

}

