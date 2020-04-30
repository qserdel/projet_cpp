#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "robot.hpp"

using namespace sf;


int main()
{
    // Create the main window
    RenderWindow window(VideoMode(1000, 1000), "SFML window");
    // Load a sprite to display
    Robot rob;
    Texture texture[10];
    Texture robotActuel;

    if (!robotActuel.loadFromFile("images/Face.jpg", IntRect(0, 0, 120, 190)))
    	return EXIT_FAILURE;
    rob.message();
    rob.chargement_image(texture);
    Sprite sprite(robotActuel);

    //Sprite sprite1(texture);
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

    sprite.setColor(Color(250, 200, 200, 255)); // Choix de la couleur du sprite
    sprite.setPosition(Vector2f(20.f, 525.f)); // Choix de la position du sprite


    int compteur = -1;
	float x = 10;
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();

            rob.move(event, texture, &robotActuel, &compteur, &sprite);

        }

	//sprite.scale(Vector2f(0.999f, 0.999f)); // Modifie l'échelle par rapport à l'échelle actuelle
	//sprite.rotate(1.f); // Tourne d'un certain angle par rapport à l'angle actuel


        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(spriteFond);
        window.draw(sprite);

        //window.draw(spriteMur);
        window.draw(spriteMur2);
        //window.draw(sprite1);
        // Draw the string
        //window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
