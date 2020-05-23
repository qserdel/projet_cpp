#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "balle.hpp"
#include "collision.hpp"
#include "map.hpp"


int main()
{
    // Create the main window
    RenderWindow window(VideoMode(TAILLE_WINDOW, TAILLE_WINDOW), "SFML window");
    window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde

    // Load a sprite to display
    Robot rob("Joueur1");
    Robot rob2("Joueur2");
    Balle balle;
    Collision collision(balle, rob);
    Map map;


    // Load a music to play
    /*Music music;
    if (!music.openFromFile("nice_music.ogg"))
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
        
        if (rob.getTir() == true)  // La balle continue de bouger tant qu'elle est dans la fenêtre
            rob.setTir(balle.action());
        if (rob2.getTir() == true)  // La balle continue de bouger tant qu'elle est dans la fenêtre
            rob2.setTir(balle.action());
        
        collision.gestionCollision(&rob, &balle, &map, elapsed);
        collision.gestionCollision(&rob2, &balle, &map, elapsed);
        
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
        window.draw(balle.getSprite());
        for (int i = 0; i < map.getListObjets().size(); i++)
        {
        	window.draw(map.getListObjets()[i]);
        }


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
