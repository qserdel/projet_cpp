#include "jeu.hpp"


Jeu::Jeu() : window(VideoMode(TAILLE_WINDOW, TAILLE_WINDOW), "SFML window"), rob("Joueur1"), rob2("Joueur2")
{
	window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde
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

    for(int i = 0; i < 10; i++){
      if(tabBalles[i].getX()>=0 && tabBalles[i].getX()<=1000)
        window.draw(tabBalles[i].getSprite());
    }
    for (int i = 0; i < map.getListObjets().size(); i++)
    {
    	window.draw(map.getListObjets()[i]);
    }
    for (int i = 0; i < map.getListCollec().size(); i++)
    {
    	window.draw(map.getListCollec()[i]);
    }

    // Update the window
    window.display();
}

int Jeu::play()
{
    // Load a music to play
    /*sf::Music music;
    if (!music.openFromFile("images/HumbleMatch.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();*/
	map.ajouterSpriteListeCollec(bouclier.getSprite());
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
				std::cout<<rob.getStatus()<<endl;
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
        map.updateMap();
		draw();
    }
    return EXIT_SUCCESS;
}
