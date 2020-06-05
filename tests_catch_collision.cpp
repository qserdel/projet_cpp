#include "catch.hpp"
#include <SFML/Graphics.hpp>

#include "collision.hpp"
using namespace std;
using namespace sf;

TEST_CASE( "Collision can be created", "[collision]" ) {

    Collision col;

    // Test constructeur
    REQUIRE(col.getAltitude_atterrissage() == 0);



    SECTION( "Tests collisions" ) {
    	Robot r("Joueur1", 0, HUMAIN);
    	Robot r2("Joueur2", 1, HUMAIN);
    	
    	r.setPosSprite(150, 200);
    	r2.setPosSprite(150, 200);
        IntRect rec1(r.getRectRobot());
        IntRect rec2(r2.getRectRobot());
        REQUIRE( col.detectCollision(rec1, rec2) == true ); // rec2 est rec1 sont superposés
        
        r2.setPosSprite(rec1.width + 10, 200);
        rec2 = IntRect(r2.getRectRobot());
        REQUIRE( col.detectCollision(rec1, rec2) == false ); // rec2 est à droite de rec1
        
        r2.setPosSprite(200, rec1.height + 200);
        rec2 = IntRect(r2.getRectRobot());
        REQUIRE( col.detectCollision(rec1, rec2) == false ); // rec2 est en dessous de rec1
        
        r2.setPosSprite(rec1.left - LARGEUR_ROBOT - 10, 200);
        rec2 = IntRect(r2.getRectRobot());
        REQUIRE( col.detectCollision(rec1, rec2) == false ); // rec2 est à gauche de rec1
        
        r2.setPosSprite(200, rec1.top - HAUTEUR_ROBOT - 20);
        rec2 = IntRect(r2.getRectRobot());
        REQUIRE( col.detectCollision(rec1, rec2) == false ); // rec2 est au dessus de rec1
        
        r2.setPosSprite(rec1.width, rec1.height);
        rec2 = IntRect(r2.getRectRobot());
        REQUIRE( col.detectCollision(rec1, rec2) == true ); // rec2 a un angle commun avec rec1 (angle inférieur droit)
        
        Balle balle(rec1.width, 300, true, 1);
        rec2 = IntRect(balle.getRectBalle());
        REQUIRE( col.detectCollision(rec1, rec2) == true ); // rec2 a une arrête commune avec rec1 (arrête droite de rec1 commune avec arrête gauche de rec2)
        
        balle.setX(rec1.left + 10);
        rec2 = IntRect(balle.getRectBalle());
        REQUIRE( col.detectCollision(rec1, rec2) == true ); // rec2 a l'intérieur de rec1
        r.vider();
        r2.vider();
    }
    
    SECTION( "Tests gestionCollisionBalle" ) {
    	Robot r("Joueur1", 0, HUMAIN);
    	vector<Balle*> tBalles;
    	Balle *b1 = new Balle(160, 300, true, 1);
    	tBalles.push_back(b1);
    	b1 = new Balle(600, 300, true, 1);
    	tBalles.push_back(b1);
    	
    	REQUIRE( tBalles.size() == 2 ); // Il y a 2 Balles
    	REQUIRE( r.getStatus() == NORMAL );
    	REQUIRE( r.getPv() == 25 ); // Le robot a tous ses PVs
    	
    	r.setPosSprite(150, 200);
    	col.gestionCollisionBalle(&r, tBalles, 1); // La balle 1 n'est pas en collision avec le robot, on ne la supprime pas
        REQUIRE( tBalles.size() == 2 );
        REQUIRE( r.getStatus() == NORMAL );
    	REQUIRE( r.getPv() == 25 );
        
        col.gestionCollisionBalle(&r, tBalles, 0); // La balle 0 est en collision avec le robot, on la supprime
        REQUIRE( tBalles.size() == 1 );
        REQUIRE( r.getStatus() == BLESSE ); // Le robot est blessé
    	REQUIRE( r.getPv() == 24 ); // Il perd 1 PV
    	while (!tBalles.empty())
    	{
    		tBalles.back();
    		tBalles.pop_back();
    	}
    	REQUIRE( tBalles.size() == 0 );
        r.vider();
    }
    
    SECTION( "Tests detectAtterrissage" ) {
    	Robot r("Joueur1", 0, HUMAIN);
    	Map map(1);  // Il y a un support d'atterrissage sur l'intervalle de coordonnées [450, 550] en x et 150 en y
    	map.create();
    	r.setPosSprite(500, 200 - HAUTEUR_ROBOT);
		IntRect rec1(r.getRectRobot());
		
    	REQUIRE( col.detectAtterrissage(rec1, map) == false );

    	r.setPosSprite(500, 155 - HAUTEUR_ROBOT);
    	rec1 = IntRect(r.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == true ); // Détecte atterrissage sur un objet de la map lorsque le robot en est proche à 20 pixels près
    	
    	r.setPosSprite(650, 140 - HAUTEUR_ROBOT);
    	rec1 = IntRect(r.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == false );
    	
    	r.setPosSprite(500, POS_SOL - HAUTEUR_ROBOT);
    	rec1 = IntRect(r.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == true ); // Détecte une atterrissage au sol
    	map.vider();
        r.vider();
    }
    
    
    SECTION( "Tests atterrissage" ) {
    	Robot r("Joueur1", 0, HUMAIN);
    	Sprite robInit = r.getSprite();
    	r.setEnPleinJump(true);
    	r.sauter(0.1);
    	
    	REQUIRE( (r.getHauteurSaut() < 500) == true );
    	REQUIRE( r.getEnPleinJump() == true );
    	REQUIRE( r.getSprite().getLocalBounds().height > HAUTEUR_ROBOT );
    	REQUIRE( r.getSprite().getLocalBounds().width == LARGEUR_ROBOT );
    	REQUIRE( robInit.getPosition().x == r.getSprite().getPosition().x );
    	REQUIRE( robInit.getPosition().y > r.getSprite().getPosition().y ); // Le robot vient de sauter
    	
		Sprite robPrec = r.getSprite();
    	col.atterrissage(POS_SOL, &r);
    	REQUIRE( r.getHauteurSaut() == 500 ); // Les variables de saut sont réinitialisées
    	REQUIRE( r.getEnPleinJump() == false );
    	REQUIRE( r.getSprite().getLocalBounds().height == HAUTEUR_ROBOT );
    	REQUIRE( r.getSprite().getLocalBounds().width == LARGEUR_ROBOT );
    	REQUIRE( robPrec.getPosition().x == r.getSprite().getPosition().x );
    	REQUIRE( robPrec.getPosition().y < r.getSprite().getPosition().y ); // Le robot vient de retourner au sol
    	REQUIRE( robInit.getPosition().y == r.getSprite().getPosition().y );
    	
    	Robot r2("Joueur2", 1, HUMAIN);
    	r2.setEnPleinJump(true);
    	r2.sauter(0.1);
    	r2.setStatus(DOWN);
    	Sprite rob2Init = r2.getSprite();
    	col.atterrissage(POS_SOL, &r2);
    	REQUIRE( r2.getHauteurSaut() == 500 ); // Les variables de saut sont réinitialisées
    	REQUIRE( r2.getEnPleinJump() == false );
    	REQUIRE( r2.getSprite().getLocalBounds().height == HAUTEUR_ROBOT );
    	REQUIRE( r2.getSprite().getLocalBounds().width == LARGEUR_ROBOT );
    	REQUIRE( rob2Init.getPosition().x == r2.getSprite().getPosition().x );
    	REQUIRE( rob2Init.getPosition().y < r2.getSprite().getPosition().y ); // Le robot vient de retourner au sol en étant baissé
        r.vider();
        r2.vider();
    }
    
    SECTION( "Tests gestionAtterrissage" ) {
    	Robot r("Joueur1", 0, HUMAIN);
    	r.setEnPleinJump(true);
    	r.sauter(0.1);
    	Sprite robPrec = r.getSprite();
    	
    	REQUIRE( (r.getHauteurSaut() < 500) == true );
    	REQUIRE( r.getEnPleinJump() == true );
    	
    	Map map(1);  // Il y a un support d'atterrissage sur l'intervalle de coordonnées [450, 550] en x et 150 en y
    	map.create();
		IntRect rec1(r.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == false );
    	col.gestionAtterrissage(&r, &map, 0.1);
    	REQUIRE( robPrec.getPosition().x == r.getSprite().getPosition().x );
    	REQUIRE( robPrec.getPosition().y == r.getSprite().getPosition().y );
    	REQUIRE( (r.getHauteurSaut() < 500) == true ); // Il y a pas eu d'atterrissage car aucun de détecté
    	REQUIRE( r.getEnPleinJump() == true );

		r.setHauteurSaut(-15);
		r.setPosSprite(500, 150 - r.getSprite().getLocalBounds().height);
		robPrec = r.getSprite();
    	rec1 = IntRect(r.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == true );
    	col.gestionAtterrissage(&r, &map, 0.01);
    	REQUIRE( robPrec.getPosition().y != r.getSprite().getPosition().y ); // Le robot a trouvé un endroit où atterrir
    	REQUIRE( r.getHauteurSaut() == 500 ); // Les variables de saut sont réinitialisées
    	REQUIRE( r.getEnPleinJump() == false );
    	
    	Robot r2("Joueur2", 1, HUMAIN);
    	r2.setPosSprite(545, 150 - r2.getSprite().getLocalBounds().height); // Le robot est en bordure d'un support d'atterrissage
    	rec1 = IntRect(r2.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == true );
    	r2.setPosSprite(r2.getX() + 20, r2.getY()); // Le robot se déplace vers la droite de 20 pixels, il se retrouve dans le vide
    	rec1 = IntRect(r2.getRectRobot());
    	REQUIRE( col.detectAtterrissage(rec1, map) == false );
    	robPrec = r2.getSprite();
		col.gestionAtterrissage(&r2, &map, 0.01); // Le robot est en chute libre
		REQUIRE( robPrec.getPosition().y < r2.getSprite().getPosition().y );
		map.vider();
		r.vider();
		r2.vider();
        
    }
    
    SECTION( "Tests gestionAtterrissageCollec" ) {    	
    	Map map(1);  // Il y a un support d'atterrissage sur l'intervalle de coordonnées [450, 550] en x et 150 en y
    	map.create();
    	map.ajouterListeCollec(new Bouclier);
    	REQUIRE( map.getListCollec().size() == 1 );
    	
    	IntRect obj(map.getRectColl(0)); // La position du collectable est initialisée à y = 0, il n'y a donc aucun atterrissage à détecter pour le moment
    	col.gestionAtterrissageCollec(&map, 0.01); // Tant qu'il n'a pas atterri, l'objet est en chute libre
    	REQUIRE( obj.top < map.getRectColl(0).top );
    	
    	map.setPosCollec(500, 149 - (obj.height - obj.top), 0); // Le collectable est juste au dessus d'un objet sur lequel il peut atterrir
    	obj = IntRect(map.getRectColl(0));
    	REQUIRE( col.detectCollision(obj, map.getRectObj(3)) == false );
    	col.gestionAtterrissageCollec(&map, 0.01); // Le collectable est encore en chute libre, il s'approche davantage de l'objet sur lequel il va pouvoir atterrir
    	REQUIRE( obj.top < map.getRectColl(0).top );
    	
    	obj = IntRect(map.getRectColl(0));
    	REQUIRE( col.detectCollision(obj, map.getRectObj(3)) == true );
    	col.gestionAtterrissageCollec(&map, 0.01); // Le collectable peut désormais atterrir
    	REQUIRE( map.getRectObj(3).top == map.getRectColl(0).height );
    	REQUIRE( map.getSpriteStable(0) == true ); // Le collectable a atterri
    	
    	map.ajouterListeCollec(new Bouclier);
    	REQUIRE( map.getListCollec().size() == 2 );
    	obj = IntRect(map.getRectColl(1));
    	
    	map.setPosCollec(50, POS_SOL - 2 - (obj.height - obj.top), 1); // Le collectable est juste au dessus du sol
    	obj = IntRect(map.getRectColl(1));
    	col.gestionAtterrissageCollec(&map, 0.01); // Le collectable est encore en chute libre, il s'approche davantage du sol où il va pouvoir atterrir
    	REQUIRE( obj.top < map.getRectColl(1).top );
    	
    	obj = IntRect(map.getRectColl(1));
    	col.gestionAtterrissageCollec(&map, 0.01); // Le collectable peut désormais atterrir
    	REQUIRE( POS_SOL == map.getRectColl(1).height );
    	REQUIRE( map.getSpriteStable(1) == true ); // Le collectable a atterri
    	map.vider();
    	REQUIRE( map.getListCollec().size() == 0 );
    	
    }
    
    SECTION( "Tests collisionCollec" ) {  
    	Robot r("Joueur1", 0, HUMAIN);  	
    	Map map(1);  // Il y a un support d'atterrissage sur l'intervalle de coordonnées [450, 550] en x et 150 en y
    	map.create();
    	map.ajouterListeCollec(new Bouclier);
    	map.setPosCollec(835, 530, 0);
    	map.ajouterListeCollec(new Bouclier);
    	map.setPosCollec(500, 650, 1);
    	REQUIRE( map.getListCollec().size() == 2 );
    	
    	col.collisionCollec(&r, &map); // Le robot est en contact avec aucun collectable
    	REQUIRE( map.getListCollec().size() == 2 ); // Aucun collectable supprimé
    	
    	r.setPosSprite(835, 520); // Le robot est en contact avec le premier collectable
    	col.collisionCollec(&r, &map);
    	REQUIRE( map.getListCollec().size() == 1 ); // Un collectable a été supprimé
    	
    	r.setPosSprite(510, 666); // Le robot est en contact avec le dernier collectable
    	col.collisionCollec(&r, &map);
    	REQUIRE( map.getListCollec().size() == 0 ); // Il n'y a plus de collectable
    	map.vider();
    	r.vider();
    }


}

