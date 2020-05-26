#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "balle.hpp"
#include "collision.hpp"
#include "map.hpp"
#include <SFML/Audio.hpp>


int main()
{
    // Create the main window
    RenderWindow window(VideoMode(TAILLE_WINDOW, TAILLE_WINDOW), "SFML window");
    window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde

    Robot rob("Joueur1");
    Robot rob2("Joueur2");
    Collision collision;
    Balle tabBalles[10];
    Map map;


    // Load a music to play
    //sf::Music music;
    //if (!music.openFromFile("images/HumbleMatch.ogg"))
    //    return EXIT_FAILURE;
    // Play the music
    //music.play();


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

            rob.detect_KeyPressed();
            rob2.detect_KeyPressed();
            if (rob.getStatus() == DOWN)
                rob.move(elapsed);
            if (rob2.getStatus() == DOWN)
                rob2.move(elapsed);
        }

        if (rob.getStatus() != BLESSE)
        {
		    rob.move(elapsed);

		    if ((rob.getEnPleinGrandissement() == true) || (rob.getTaille() == GRAND))
		        rob.grandir();

		    if ((rob.getEnPleinRapetissement() == true) || (rob.getTaille() == PETIT))
		        rob.rapetisser();
        }

        if (rob2.getStatus() != BLESSE)
        {
		    rob2.move(elapsed);

		    if ((rob2.getEnPleinGrandissement() == true) || (rob2.getTaille() == GRAND))
		        rob2.grandir();

		    if ((rob2.getEnPleinRapetissement() == true) || (rob2.getTaille() == PETIT))
		        rob2.rapetisser();
        }
        //tirs du joueur1
        if (rob.getStatus() == TIRER)
        {
          for (int i=0;i<5;i++){
            if(tabBalles[i].getX()<=0 || tabBalles[i].getX()>=1000){
              tabBalles[i] = Balle(rob.getX()+LARGEUR_ROBOT*0.7*rob.getDirection(),rob.getY()+HAUTEUR_ROBOT/3.6,rob.getDirection());
            }
            else {
              tabBalles[0] = Balle(rob.getX()+LARGEUR_ROBOT*0.7*rob.getDirection(),rob.getY()+HAUTEUR_ROBOT/3.6,rob.getDirection());
            }
          }
        }
        // tirs du joueur 2
        if (rob2.getStatus() == TIRER)
        {
          for (int i=5;i<10;i++){
            if(tabBalles[i].getX()<=0 || tabBalles[i].getX()>=1000){
              tabBalles[i] = Balle(rob2.getX()+LARGEUR_ROBOT*0.7*rob2.getDirection(),rob2.getY()+HAUTEUR_ROBOT/3.6,rob2.getDirection());
            }
            else {
              tabBalles[5] = Balle(rob2.getX()+LARGEUR_ROBOT*0.7*rob2.getDirection(),rob2.getY()+HAUTEUR_ROBOT/3.6,rob2.getDirection());
            }
          }
        }
        //gestion des collisions
        for(int i=0;i<5;i++)
        {
          if(tabBalles[5+i].getX()>=0 && tabBalles[5+i].getX()<=1000){
            collision.gestionCollision(&rob, &tabBalles[5+i], &map, elapsed);
            tabBalles[5+i].action();
          }
          if(tabBalles[i].getX()>=0 && tabBalles[i].getX()<=1000){
            collision.gestionCollision(&rob2, &tabBalles[i], &map, elapsed);
            tabBalles[i].action();
          }
        }
        //collisions pour l'atterissage des robots //TODO separer balle et atterissage
        collision.gestionCollision(&rob,&tabBalles[5],&map,elapsed);
        collision.gestionCollision(&rob2,&tabBalles[0],&map,elapsed);
        //degats si touchés
        if (rob.getStatus() == BLESSE)
        	rob.blessure();
    	  if (rob2.getStatus() == BLESSE)
        	rob2.blessure();

        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(map.getSpriteFond());
        window.draw(map.getSpriteSol());
        window.draw(rob.getSprite());
        window.draw(rob2.getSprite());
        for(int i=0; i<10;i++){
          if(tabBalles[i].getX()>=0 && tabBalles[i].getX()<=1000)
            window.draw(tabBalles[i].getSprite());
        }
        for (int i = 0; i < map.getListObjets().size(); i++)
        {
        	window.draw(map.getListObjets()[i]);
        }


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
