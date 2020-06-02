#include "catch.hpp"
#include <SFML/Graphics.hpp>

#include "map.hpp"

TEST_CASE( "Map can be created", "[map]" ) {

    Map map(1);
    Map map2(2);
    Map map3(3);

    // Tests constructeur
    REQUIRE( map.getListObjets().size() == 4 );
    REQUIRE( map2.getListObjets().size() == 5 );
    REQUIRE( map3.getListObjets().size() == 5 );
    REQUIRE( map.getListCollec().size() == 0 );
    REQUIRE( map2.getListCollec().size() == 0 );
    REQUIRE( map3.getListCollec().size() == 0 );



    SECTION( "Test creation_objets" ) {
    	 map.creation_objets();
    	 Vector2f pos(200, 500);
    	 Vector2f pos1(50, 300);
		 Vector2f pos2(750, 300);
		 Vector2f pos3(450, 150);
    	 REQUIRE( pos.x == map.getRectObj(0).left );
    	 REQUIRE( pos.y == map.getRectObj(0).top );
    	 REQUIRE( pos1.x == map.getRectObj(1).left );
    	 REQUIRE( pos1.y == map.getRectObj(1).top );
    	 REQUIRE( pos2.x == map.getRectObj(2).left );
    	 REQUIRE( pos2.y == map.getRectObj(2).top );
    	 REQUIRE( pos3.x == map.getRectObj(3).left );
    	 REQUIRE( pos3.y == map.getRectObj(3).top );
    	 
    	 map2.creation_objets();
    	 pos = Vector2f(100, 530);
    	 pos1 = Vector2f(600, 530);
		 pos2 = Vector2f(100, 180);
		 pos3 = Vector2f(600, 180);
		 Vector2f pos4(450, 360);
    	 REQUIRE( pos.x == map2.getRectObj(0).left );
    	 REQUIRE( pos.y == map2.getRectObj(0).top );
    	 REQUIRE( pos1.x == map2.getRectObj(1).left );
    	 REQUIRE( pos1.y == map2.getRectObj(1).top );
    	 REQUIRE( pos2.x == map2.getRectObj(2).left );
    	 REQUIRE( pos2.y == map2.getRectObj(2).top );
    	 REQUIRE( pos3.x == map2.getRectObj(3).left );
    	 REQUIRE( pos3.y == map2.getRectObj(3).top );
    	 REQUIRE( pos4.x == map2.getRectObj(4).left );
    	 REQUIRE( pos4.y == map2.getRectObj(4).top );
    	 
    	 map3.creation_objets();
    	 pos = Vector2f(150, 360);
    	 pos1 = Vector2f(600, 530);
		 pos2 = Vector2f(100, 530);
		 pos3 = Vector2f(600, 530);
		 pos4 = Vector2f(450, 180);
    	 REQUIRE( pos.x == map3.getRectObj(0).left );
    	 REQUIRE( pos.y == map3.getRectObj(0).top );
    	 REQUIRE( pos1.x == map3.getRectObj(1).left );
    	 REQUIRE( pos1.y == map3.getRectObj(1).top );
    	 REQUIRE( pos2.x == map3.getRectObj(2).left );
    	 REQUIRE( pos2.y == map3.getRectObj(2).top );
    	 REQUIRE( pos3.x == map3.getRectObj(3).left );
    	 REQUIRE( pos3.y == map3.getRectObj(3).top );
    	 REQUIRE( pos4.x == map3.getRectObj(4).left );
    	 REQUIRE( pos4.y == map3.getRectObj(4).top );
    }
    
    SECTION( "Tests d'ajouts et de suppression de collectables" ) {
    	 Collectable *co = new Bouclier;
    	 map.ajouterSpriteListeCollec(co);
    	 REQUIRE( map.getListCollec().size() == 1 );
    	 
    	 co = new Grandir;
    	 map.ajouterSpriteListeCollec(co);
    	 REQUIRE( map.getListCollec().size() == 2 );
    	 
    	 map.supprimerCollec(1);
    	 REQUIRE( map.getListCollec().size() == 1 );
    	 
    	 map.supprimerCollec(0);
    	 REQUIRE( map.getListCollec().size() == 0 ); // La liste de collectables est vide
    }
    
    SECTION( "Test setPosCollec" ) {
    	 Collectable *co = new Rapetisser;
    	 map.ajouterSpriteListeCollec(co);
    	 REQUIRE( map.getListCollec().size() == 1 );
    	 
    	 IntRect rec(map.getRectColl(0));
    	 map.setPosCollec(rec.left + 15, rec.top + 95, 0);
    	 REQUIRE( rec.left != map.getRectColl(0).left );
    	 REQUIRE( rec.top != map.getRectColl(0).top );
    }
    
    SECTION( "Test moveCollec" ) {
    	 Collectable *co = new Reparer;
    	 map.ajouterSpriteListeCollec(co);
    	 REQUIRE( map.getListCollec().size() == 1 );
    	 
    	 IntRect rec(map.getRectColl(0));
    	 Vector2f v(81.f, 76.f);
    	 map.moveCollec(v, 0);
    	 REQUIRE( rec.left != map.getRectColl(0).left );
    	 REQUIRE( rec.top != map.getRectColl(0).top );
    }
    
    SECTION( "Test ajoutCollectable" ) {
    	 REQUIRE( map.getListCollec().size() == 0 );
    	 map.ajoutCollectable();
    	 REQUIRE( map.getListCollec().size() == 1 );
    }
    
    SECTION( "Tests updateMap" ) {
    	 map.updateMap();
    	 REQUIRE( map.getTimerMap() < TIMER_MAP );
    	 REQUIRE( map.getListCollec().size() == 0 );
    	 
    	 map.setTimerMap(1);
    	 map.updateMap();
    	 REQUIRE( map.getListCollec().size() == 1 ); // On ajoute un collectable à liste des collectables
    	 REQUIRE( map.getTimerMap() == TIMER_MAP ); // On relance le timer
    }
    
    SECTION( "Tests gestionCollectable" ) {
    	 Robot r("Joueur1");
    	 
    	 Collectable *co = new Bouclier;
    	 map.ajouterSpriteListeCollec(co);
    	 
    	 co = new Grandir;
    	 map.ajouterSpriteListeCollec(co);
    	 
    	 co = new Rapetisser;
    	 map.ajouterSpriteListeCollec(co);
    	 
    	 co = new Reparer;
    	 map.ajouterSpriteListeCollec(co);
    	 REQUIRE( map.getListCollec().size() == 4 );
    	 
    	 map.gestionCollectable(map.getListCollec()[0], &r);
    	 REQUIRE( r.getBouclier() == true );
    	 REQUIRE( r.getTimerBouclier() < TIMER_BOUCLIER );
    	 
    	 map.gestionCollectable(map.getListCollec()[1], &r);
    	 REQUIRE( r.getEnPleinGrandissement() == true );
    	 REQUIRE( r.getMaxScale() == 2 );
    	 
    	 map.gestionCollectable(map.getListCollec()[2], &r);
    	 REQUIRE( r.getEnPleinRapetissement() == true );
    	 REQUIRE( r.getMinScale() == 0.5 );
    	 
    	 r.setPv(r.getPv() - 5);
    	 map.gestionCollectable(map.getListCollec()[3], &r); // Le robot gagne 3 PVs
    	 REQUIRE( r.getPv() == PV_MAX - 2 );
    	 map.gestionCollectable(map.getListCollec()[3], &r); // Le robot atteint son quota maximum de PVs
    	 REQUIRE( r.getPv() == PV_MAX );
    }
}

