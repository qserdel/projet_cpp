#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;


int main()
{
    // Create the main window
    RenderWindow window(VideoMode(1000, 1000), "SFML window");
    // Load a sprite to display
    Texture texture[10];
    Texture robotActuel;
    if (!texture[0].loadFromFile("images/1Rapide.jpg", IntRect(0, 0, 120, 190))) // Charge l'image est l'affiche dans la dimension que l'on souhaite (rognage)
        return EXIT_FAILURE;
    if (!texture[1].loadFromFile("images/2Rapide.jpg", IntRect(0, 0, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[2].loadFromFile("images/3Rapide.jpg", IntRect(5, 25, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[3].loadFromFile("images/4Rapide.jpg", IntRect(10, 30, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[4].loadFromFile("images/5Rapide.jpg", IntRect(0, 10, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[5].loadFromFile("images/6Rapide.jpg", IntRect(0, 20, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[6].loadFromFile("images/7Rapide.jpg", IntRect(0, 10, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[7].loadFromFile("images/8Rapide.jpg", IntRect(0, 10, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[8].loadFromFile("images/9Rapide.jpg", IntRect(10, 25, 120, 190)))
    	return EXIT_FAILURE;
    if (!texture[9].loadFromFile("images/10Rapide.jpg", IntRect(0, 10, 120, 190)))
    	return EXIT_FAILURE;
    if (!robotActuel.loadFromFile("images/Face.jpg", IntRect(0, 0, 120, 190)))
    	return EXIT_FAILURE;
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
    sprite.setPosition(Vector2f(20.f, 200.f)); // Choix de la position du sprite

    int compteur = -1;

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
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
            	sprite.move(Vector2f(10.f, 0.f)); // Déplacement par rapport à la position actuelle
            	if(++compteur == 9)
            		compteur = 0;
            	robotActuel = texture[compteur];
	    }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
            	sprite.move(Vector2f(-10.f, 0.f)); // Déplacement par rapport à la position actuelle
            	if(--compteur == 0)
            		compteur = 9;
            	robotActuel = texture[compteur];
	    }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            	sprite.move(Vector2f(0.f, -10.f)); // Déplacement par rapport à la position actuelle
            if (Keyboard::isKeyPressed(Keyboard::Down))
            	sprite.move(Vector2f(0.f, 10.f)); // Déplacement par rapport à la position actuelle

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
