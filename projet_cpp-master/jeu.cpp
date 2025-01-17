#include "jeu.hpp"

using namespace sf;
using namespace std;

Jeu::Jeu() : window(VideoMode(TAILLE_WINDOW_X, TAILLE_WINDOW_Y), "SFML window"), rob("Joueur1", 0, HUMAIN), rob2("Joueur2", 1, HUMAIN), map(1)
{
	window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde
	// Chargement des textures des pv des robots et création du tableau des sprites
	if (!pvBlue.loadFromFile("images/PVBlue.png"))
		exit(EXIT_FAILURE);
	if (!pvRed.loadFromFile("images/PVRed.png"))
		exit(EXIT_FAILURE);
	for(int i = 0; i < PV_MAX; i++){ // Placement des PVs dans la fenêtre
		spritesPv1[i].setTexture(pvBlue,true);
		spritesPv1[i].setPosition(Vector2f(10+10*i,0));
		spritesPv2[i].setTexture(pvRed,true);
		spritesPv2[i].setPosition(Vector2f(TAILLE_WINDOW_X-20-10*i,0));
	}
	// Chargement des textures de fin de partie
	if (!victoire1.loadFromFile("images/victoire1.png"))
		exit(EXIT_FAILURE);
	if (!victoire2.loadFromFile("images/victoire2.png"))
		exit(EXIT_FAILURE);
	// Load a music to play
    if (!music.openFromFile("images/BlazerRail.wav"))
        exit(EXIT_FAILURE);
}

void Jeu::gestionTirs(Robot &rob)
{
	if (rob.getStatus() == TIRER && rob.getTimerTir() <= 0)
	{
		tabBalles.push_back(new Balle(rob.getX()+rob.getSprite().getGlobalBounds().width*0.7*rob.getDirection(),
											rob.getY()+rob.getSprite().getGlobalBounds().height/3.6, rob.getDirection(), rob.getID()));
		rob.effacerMunition();
		rob.resetTimerTir();
	}
}

void Jeu::updateActionRobot(Robot &rob)
{
	if (rob.getStatus() != BLESSE)
    {
	    rob.move(elapsed);

	    if (rob.getEnPleinGrandissement() || (rob.getTaille() == GRAND))
	        rob.grandir();

	    if (rob.getEnPleinRapetissement() || (rob.getTaille() == PETIT))
	        rob.rapetisser();
        
        if (rob.getBouclier() == true)
			rob.actionBouclier();
    }
    rob.gestionMunitions();
}

void Jeu::gestionAttaques(Robot &rob)
{
	for(int i = 0; i < tabBalles.size(); i++)
    {
      if(tabBalles[i]->getX() >= 0-tabBalles[i]->getLargeur() && tabBalles[i]->getX() <= TAILLE_WINDOW_X)
      {
        collision.gestionCollisionBalle(&rob, tabBalles, i);
        tabBalles[i]->action();
      }
      else // Si la balle est hors de la fenêtre, on la supprime
      {
      	delete tabBalles[i];
      	tabBalles.erase(tabBalles.begin() + i);
	  }
  	}
  	if (rob.getStatus() == BLESSE)
    	rob.blessure();
}

void Jeu::update()
{
	updateActionRobot(rob);
	updateActionRobot(rob2);

	// Tirs
	gestionTirs(rob);
	gestionTirs(rob2);


    // Gestion des attaques
    gestionAttaques(rob);
    gestionAttaques(rob2);

    // Collisions pour l'atterissage des robots
    collision.gestionAtterrissage(&rob, &map, elapsed);
    collision.gestionAtterrissage(&rob2, &map, elapsed);
    collision.gestionAtterrissageCollec(&map, elapsed);

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

	// Affichage des PVs de chaque robot
	for(int i = 0; i < rob.getPv(); i++)
		window.draw(spritesPv1[i]);
	for(int i = 0; i < rob2.getPv(); i++)
		window.draw(spritesPv2[i]);

    for(int i = 0; i < tabBalles.size(); i++)
  		window.draw(tabBalles[i]->getSprite());

    for (int i = 0; i < map.getListObjets().size(); i++)
    	window.draw(map.getSpriteObj(i));

    for (int i = 0; i < map.getListCollec().size(); i++)
    	window.draw(map.getSpriteCollec(i));

	if (rob.getBouclier())
	{
		CircleShape bouclier(Bouclier::formationBouclier(rob));
		window.draw(bouclier);
	}

	if (rob2.getBouclier())
	{
		CircleShape bouclier2(Bouclier::formationBouclier(rob2));
		window.draw(bouclier2);
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

void Jeu::clearBalles()
{
	while (!tabBalles.empty())
	{
		delete tabBalles.back();
		tabBalles.pop_back();
	}
}

int Jeu::play()
{
    // Play the music
	music.setLoop(true);
    music.play();

    // Start the game loop
    while (window.isOpen())
		{
			// Process events
			Event event;
			while (window.pollEvent(event)){
				// Close window: exit
				if (event.type == Event::Closed)
					window.close();
				switch(menu.getIndex()){
					case 0:
					// Menu de base
						window.clear();
						window.draw(menu.getFond());
						window.draw(menu.getPlay());
						window.display();
						if(menu.getPlay().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && Mouse::isButtonPressed(Mouse::Left))
							menu.setIndex(1);
					break;
					case 1:
					// Choix de la map
						window.clear();
						window.draw(menu.getFondMap());
						window.display();
						sleep(milliseconds(70));
						if(Mouse::getPosition(window).x<TAILLE_WINDOW_X/3 && Mouse::isButtonPressed(Mouse::Left)){
							map.setIndex(1);
							menu.setIndex(2);
						}
						if(Mouse::getPosition(window).x>=TAILLE_WINDOW_X/3 && Mouse::getPosition(window).x<=2*TAILLE_WINDOW_X/3 && Mouse::isButtonPressed(Mouse::Left)){
							map.setIndex(2);
							menu.setIndex(2);
						}
						if(Mouse::getPosition(window).x>2*TAILLE_WINDOW_X/3 && Mouse::isButtonPressed(Mouse::Left)){
							map.setIndex(3);
							menu.setIndex(2);
						}
					break;
					case 2:
					// Jeu
						while(rob.getPv()>0 && rob2.getPv()>0){
							window.pollEvent(event);
							elapsed = clock.restart().asSeconds();
							// Close window: exit
							if (event.type == Event::Closed)
						    	window.close();

							rob.detect_KeyPressed();
							rob2.detect_KeyPressed();
							if (rob.getStatus() == DOWN)
						    	rob.move(elapsed);
							if (rob2.getStatus() == DOWN)
						    	rob2.move(elapsed);

							update();
							updateMap();
							draw();
						}
						menu.setIndex(3);
					break;
					case 3:
					// Fin du jeu
						window.clear();
						if(rob.getPv() == 0){
							spriteVictoire.setTexture(victoire2);
						} else {
							spriteVictoire.setTexture(victoire1);
						}
						window.draw(spriteVictoire);
						window.display();
						rob.resetRobot();
						rob2.resetRobot();						
						map.vider();
						clearBalles();
						menu.setIndex(0);
						sleep(seconds(5));
					break;
				}
			}
		}
		map.vider();
		clearBalles();
		rob.vider();
		rob2.vider();
		return EXIT_SUCCESS;
}
