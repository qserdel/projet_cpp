#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "balle.hpp"
#include "collision.hpp"

using namespace sf;


int main()
{
    // Create the main window
    RenderWindow window(VideoMode(1000, 1000), "SFML window");
    window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde

    // Load a sprite to display
    Robot rob("Joueur1");
    Robot rob2("Joueur2");
    Balle balle;
    Collision collision(balle, rob);

    rob.message();


    // Create a graphical text to display
    /*Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    Text text("Hello SFML", font, 50);
    // Load a music to play
    Music music;
    if (!music.openFromFile("nice_music.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();*/


    Texture fond;
    if(!fond.loadFromFile("images/fond.jpg",IntRect(100,300,1100,1000)))
      return EXIT_FAILURE;
    Sprite spriteFond(fond);
    spriteFond.setPosition(Vector2f(0.f, 0.f));

    Texture mur;
    if(!mur.loadFromFile("images/mur.jpg",IntRect(0,0,1000,50)))
      return EXIT_FAILURE;
    Sprite spriteMur(mur);
    Sprite spriteMur2(mur);
    Sprite spriteMur3(mur);
    Sprite spriteMur4(mur);
    spriteMur.setPosition(Vector2f(0.f, 0.f));
    spriteMur2.setPosition(Vector2f(0.f, 660.f));

    //sprite.setColor(Color(250, 200, 200, 255)); // Choix de la couleur du sprite

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
            if ((rob.getStatus() == DOWN))
            {
              rob.move(elapsed);
            }
            if((rob2.getStatus() == DOWN))
            {
              rob2.move(elapsed);
            }
        }

        rob.move(elapsed);
        rob2.move(elapsed);

        if ((rob.getEnPleinGrandissement() == true) || (rob.getTaille() == GRAND))
            rob.grandir();

        if ((rob.getEnPleinRapetissement() == true) || (rob.getTaille() == PETIT))
            rob.rapetisser();

        if ((rob2.getEnPleinGrandissement() == true) || (rob2.getTaille() == GRAND))
            rob2.grandir();

        if ((rob2.getEnPleinRapetissement() == true) || (rob2.getTaille() == PETIT))
            rob2.rapetisser();

        if (rob.getTir() == true) // La balle continue de bouger tant qu'elle est dans la fenêtre
            rob.setTir(balle.action());

        collision.gestionCollision(&rob, &balle);


	//sprite.rotate(1.f); // Tourne d'un certain angle par rapport à l'angle actuel


        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(spriteFond);
        window.draw(rob.getSprite());
        window.draw(rob2.getSprite());
        window.draw(balle.getSprite());

        //window.draw(spriteMur);
        window.draw(spriteMur2);

        // Draw the string
        //window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
