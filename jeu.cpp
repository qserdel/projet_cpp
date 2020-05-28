#include "jeu.hpp"

using namespace sf;


Jeu::Jeu() : window(VideoMode(TAILLE_WINDOW, TAILLE_WINDOW), "SFML window"), rob("Joueur1"), rob2("Joueur2")
{
	window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde
	//chargement des textures des pv des robots et création du tableau des sprites
	if (!pvBlue.loadFromFile("images/PVBlue.png"))
		exit(EXIT_FAILURE);
	if (!pvRed.loadFromFile("images/PVRed.png"))
		exit(EXIT_FAILURE);
	for(int i=0;i<PV_MAX;i++){
		spritesPv1[i].setTexture(pvBlue,true);
		spritesPv1[i].setPosition(Vector2f(10+10*i,0));
		spritesPv2[i].setTexture(pvRed,true);
		spritesPv2[i].setPosition(Vector2f(TAILLE_WINDOW-20-10*i,0));
	}
}


void Jeu::update()
{
	if (rob.getStatus() != BLESSE)
        {
		    rob.move(elapsed);

		    if (rob.getEnPleinGrandissement() || (rob.getTaille() == GRAND))
		        rob.grandir();

		    if (rob.getEnPleinRapetissement() || (rob.getTaille() == PETIT))
		        rob.rapetisser();
        }

        if (rob2.getStatus() != BLESSE)
        {
		    rob2.move(elapsed);

		    if (rob2.getEnPleinGrandissement() || (rob2.getTaille() == GRAND))
		        rob2.grandir();

		    if (rob2.getEnPleinRapetissement() || (rob2.getTaille() == PETIT))
		        rob2.rapetisser();
        }
        // tirs du joueur1
        if (rob.getStatus() == TIRER)
        {
          for (int i = NB_BALLES*rob.getID(); i < NB_BALLES + NB_BALLES*rob.getID(); i++){
            if(tabBalles[i].getX() <= 0 || tabBalles[i].getX() >= 1000){
              tabBalles[i] = Balle(rob.getX()+LARGEUR_ROBOT*0.7*rob.getDirection(),rob.getY()+HAUTEUR_ROBOT/3.6,rob.getDirection());
            }
            else {
              tabBalles[NB_BALLES*rob.getID()] = Balle(rob.getX()+LARGEUR_ROBOT*0.7*rob.getDirection(),rob.getY()+HAUTEUR_ROBOT/3.6,rob.getDirection());
            }
          }
        }
        // tirs du joueur2
        if (rob2.getStatus() == TIRER)
        {
          for (int i = NB_BALLES*rob2.getID(); i < NB_BALLES + NB_BALLES*rob2.getID(); i++){
            if(tabBalles[i].getX() <= 0 || tabBalles[i].getX() >= 1000){
              tabBalles[i] = Balle(rob2.getX()+LARGEUR_ROBOT*0.7*rob2.getDirection(),rob2.getY()+HAUTEUR_ROBOT/3.6,rob2.getDirection());
            }
            else {
              tabBalles[NB_BALLES*rob2.getID()] = Balle(rob2.getX()+LARGEUR_ROBOT*0.7*rob2.getDirection(),rob2.getY()+HAUTEUR_ROBOT/3.6,rob2.getDirection());
            }
          }
        }
        // gestion des collisions
        for(int i = 0; i < NB_BALLES; i++)
        {
          if(tabBalles[NB_BALLES*(1-rob.getID())+i].getX() >= 0 && tabBalles[NB_BALLES*(1-rob.getID())+i].getX() <= 1000){
            collision.gestionCollisionBalle(&rob, &tabBalles[NB_BALLES*(1-rob.getID())+i], &map, elapsed);
            tabBalles[NB_BALLES*(1-rob.getID())+i].action();
          }
          if(tabBalles[NB_BALLES*(1-rob2.getID())+i].getX() >= 0 && tabBalles[NB_BALLES*(1-rob2.getID())+i].getX() <= 1000){
            collision.gestionCollisionBalle(&rob2, &tabBalles[NB_BALLES*(1-rob2.getID())+i], &map, elapsed);
            tabBalles[NB_BALLES*(1-rob2.getID())+i].action();
          }
        }
        // collisions pour l'atterissage des robots
        collision.gestionAtterrissage(&rob,&map,elapsed);
        collision.gestionAtterrissage(&rob2,&map,elapsed);
        collision.gestionAtterrissageCollec(&map, elapsed);
        // degats si touchés
        if (rob.getStatus() == BLESSE)
        	rob.blessure();
	  	if (rob2.getStatus() == BLESSE)
        	rob2.blessure();
}

void Jeu::draw()
{
	// Clear screen
    window.clear();
    // Draw the sprite
    window.draw(map.getSpriteFond());
    window.draw(map.getSpriteSol());
    window.draw(rob.getSprite());
    window.draw(rob2.getSprite());
		
		//affichage des pv de chaque robots
		for(int i=0;i<rob.getPv();i++)
			window.draw(spritesPv1[i]);
		for(int i=0;i<rob2.getPv();i++)
			window.draw(spritesPv2[i]);

    for(int i = 0; i < 10; i++){
      if(tabBalles[i].getX()>=0 && tabBalles[i].getX()<=TAILLE_WINDOW)
        window.draw(tabBalles[i].getSprite());
    }
    for (int i = 0; i < map.getListObjets().size(); i++)
    {
    	window.draw(map.getListObjets()[i]);
    }
    for (int i = 0; i < map.getListCollec().size(); i++)
    {
    	window.draw(map.getSpriteCollec(i));
    }

    // Update the window
    window.display();
}

void Jeu::updateMap()
{
	map.updateMap();
	collision.collisionCollec(&rob, &map);
	collision.collisionCollec(&rob2, &map);
}

int Jeu::play()
{
    // Load a music to play
    /*sf::Music music;
    if (!music.openFromFile("images/HumbleMatch.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();*/
	//map.ajouterSpriteListeCollec(bouclier);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        elapsed = clock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();

            rob.detect_KeyPressed();
            rob2.detect_KeyPressed();
            if (rob.getStatus() == DOWN)
                rob.move(elapsed);
            if (rob2.getStatus() == DOWN)
                rob2.move(elapsed);
        }

        update();
        updateMap();
		draw();
    }
    return EXIT_SUCCESS;
}
