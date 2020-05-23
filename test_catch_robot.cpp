#define CATCH_CONFIG_MAIN // Must only appear in ONE test file
#include "catch.hpp"
#include <SFML/Graphics.hpp>
//Ou si installé par la distribution : #include <catch2/catch.hpp>

#include "robot.hpp"

TEST_CASE( "Points can be created, manipulated with arithmetic operators", "[robot]" ) {

    // Pour chaque SECTION, cet initialisation est faite - voir https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#test-cases-and-sections
    // Et pour plus d'infos : https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md#type-parametrised-test-cases
    Robot r("Joueur1");
    Robot r2("Joueur2");


    // Tests constructeur
    REQUIRE(r.getName() == "Joueur1");
    REQUIRE(r.getPv() == 3);

    REQUIRE(r2.getName() == "Joueur2");
    REQUIRE(r2.getPv() == 3);



    SECTION( "write accessors" ) {
        r.setPv(10);
        r.setStatus(NORMAL);
        REQUIRE( r.getPv() == 10);
        REQUIRE( r.getStatus() == NORMAL);
    }

}

