#include "jeu.hpp"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "balle.hpp"
#include "collision.hpp"
#include "map.hpp"
#include <SFML/Audio.hpp>

Jeu::Jeu()
{
  // Create the main window
  RenderWindow window(VideoMode(TAILLE_WINDOW, TAILLE_WINDOW), "SFML window");
  window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde

  Robot rob1("Joueur1");
  Robot rob2("Joueur2");
  Collision collision;
  Balle tabBalles[40];
  Map map;
}

int Jeu::play()
{
    // Load a music to play
    /*sf::Music music;
    if (!music.openFromFile("images/HumbleMatch.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();*/


	sf::Clock clock;
    float elapsed = 0;

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

            rob1.detect_KeyPressed();
            rob2.detect_KeyPressed();
            if (rob1.getStatus() == DOWN)
                rob1.move(elapsed);
            if (rob2.getStatus() == DOWN)
                rob2.move(elapsed);
        }

        if (rob1.getStatus() != BLESSE)
        {
		    rob1.move(elapsed);

		    if ((rob1.getEnPleinGrandissement() == true) || (rob1.getTaille() == GRAND))
		        rob1.grandir();

		    if ((rob1.getEnPleinRapetissement() == true) || (rob1.getTaille() == PETIT))
		        rob1.rapetisser();
        }

        if (rob2.getStatus() != BLESSE)
        {
		    rob2.move(elapsed);

		    if ((rob2.getEnPleinGrandissement() == true) || (rob2.getTaille() == GRAND))
		        rob2.grandir();

		    if ((rob2.getEnPleinRapetissement() == true) || (rob2.getTaille() == PETIT))
		        rob2.rapetisser();
        }

        if (rob1.getStatus() == TIRER)
            tabBalles[0] = Balle(rob1.getX()+LARGEUR_ROBOT*rob1.getDirection(),rob1.getY()+HAUTEUR_ROBOT/3,rob1.getDirection());
        if (rob2.getStatus() == TIRER)
            tabBalles[10] = Balle(rob2.getX()+LARGEUR_ROBOT*rob2.getDirection(),rob2.getY()+HAUTEUR_ROBOT/3, rob2.getDirection());

        collision.gestionCollision(&rob1, &tabBalles[10], &map, elapsed);
        collision.gestionCollision(&rob2, &tabBalles[0], &map, elapsed);

        if (rob1.getStatus() == BLESSE)
        	rob1.blessure();
    	  if (rob2.getStatus() == BLESSE)
        	rob2.blessure();

        for(int i=0;i<20;i++){
          //tabBalles[i]
        }
        //if(balle.getSprite().getPosition().x!=-1000){
          tabBalles[0].action();
        //}
        //if(balle2.getSprite().getPosition().x!=-1000){
          tabBalles[10].action();
        //}
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(map.getSpriteFond());
        window.draw(map.getSpriteSol());
        window.draw(rob1.getSprite());
        window.draw(rob2.getSprite());
        window.draw(tabBalles[0].getSprite());
        window.draw(tabBalles[10].getSprite());
        for (int i = 0; i < map.getListObjets().size(); i++)
        {
        	window.draw(map.getListObjets()[i]);
        }


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
