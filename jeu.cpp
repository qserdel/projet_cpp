#include "jeu.hpp"

using namespace sf;


Jeu::Jeu() : window(VideoMode(TAILLE_WINDOW, TAILLE_WINDOW-290), "SFML window"), rob("Joueur1"), rob2("Joueur2"),map(1)
{
	window.setFramerateLimit(60); // Limite la fenêtre à 60 images par seconde
	// Chargement des textures des pv des robots et création du tableau des sprites
	if (!pvBlue.loadFromFile("images/PVBlue.png"))
		exit(EXIT_FAILURE);
	if (!pvRed.loadFromFile("images/PVRed.png"))
		exit(EXIT_FAILURE);
	for(int i = 0; i < PV_MAX; i++){
		spritesPv1[i].setTexture(pvBlue,true);
		spritesPv1[i].setPosition(Vector2f(10+10*i,0));
		spritesPv2[i].setTexture(pvRed,true);
		spritesPv2[i].setPosition(Vector2f(TAILLE_WINDOW-20-10*i,0));
	}
	// Chargement des textures de fin de partie
	if (!victoire1.loadFromFile("images/victoire1.png"))
		exit(EXIT_FAILURE);
	if (!victoire2.loadFromFile("images/victoire2.png"))
		exit(EXIT_FAILURE);
}

void Jeu::gestionTirs(Robot &rob)
{
	if (rob.getStatus() == TIRER && rob.getTimerTir() <= 0)
	{
		tabBalles.push_back(*(new Balle(rob.getX()+rob.getSprite().getGlobalBounds().width*0.7*rob.getDirection(),
											rob.getY()+rob.getSprite().getGlobalBounds().height/3.6, rob.getDirection(), rob.getID())));
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
    }
    rob.gestionMunitions();
}

void Jeu::gestionAttaques(Robot &rob)
{
	for(int i = 0; i < tabBalles.size(); i++)
    {
      if(tabBalles[i].getX() >= 0 && tabBalles[i].getX() <= TAILLE_WINDOW)
      {
        collision.gestionCollisionBalle(&rob, tabBalles, i, &map, elapsed);
        tabBalles[i].action();
      }
      else
      	tabBalles.erase(tabBalles.begin() + i);
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

    rob.actionBouclier();
    rob2.actionBouclier();
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
	for(int i = 0; i < rob.getPv(); i++)
		window.draw(spritesPv1[i]);
	for(int i = 0; i < rob2.getPv(); i++)
		window.draw(spritesPv2[i]);

    for(int i = 0; i < tabBalles.size(); i++)
  		window.draw(tabBalles[i].getSprite());

    for (int i = 0; i < map.getListObjets().size(); i++)
    	window.draw(map.getListObjets()[i]);

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

int Jeu::play()
{
    /*// Load a music to play
    if (!music.openFromFile("images/BlazerRail.wav"))
        return EXIT_FAILURE;
    // Play the music
		music.setLoop(true);
    music.play();*/

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
					//menu de base
						window.clear();
						window.draw(menu.getFond());
						window.draw(menu.getPlay());
						window.display();
						if(menu.getPlay().getGlobalBounds().contains(Mouse::getPosition().x,Mouse::getPosition().y) && Mouse::isButtonPressed(Mouse::Left))
							menu.setIndex(1);
					break;
					case 1:
					//choix de la map
						window.clear();
						window.draw(menu.getFondMap());
						window.display();
						sleep(milliseconds(50));
						if(Mouse::getPosition().x<333 && Mouse::isButtonPressed(Mouse::Left)){
							map.setIndex(1);
							menu.setIndex(2);
						}
						if(Mouse::getPosition().x>=333 && Mouse::getPosition().x<=666 && Mouse::isButtonPressed(Mouse::Left)){
							map.setIndex(2);
							menu.setIndex(2);
						}
						if(Mouse::getPosition().x>666 && Mouse::isButtonPressed(Mouse::Left)){
							map.setIndex(3);
							menu.setIndex(2);
						}
					break;
					case 2:
					//jeu
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
					//fin du jeu
						window.clear();
						if(rob.getPv()==0){
							spriteVictoire.setTexture(victoire2);
						} else {
							spriteVictoire.setTexture(victoire1);
						}
						window.draw(spriteVictoire);
						window.display();
						rob.setPv(PV_MAX);
						rob2.setPv(PV_MAX);
						rob.setPosSprite(20.f, POS_SOL-HAUTEUR_ROBOT);
						rob2.setPosSprite(TAILLE_WINDOW - LARGEUR_ROBOT - 20.f, POS_SOL-HAUTEUR_ROBOT);
						map.vider();
						menu.setIndex(0);
						sleep(seconds(5));
					break;
				}
			}
		}
		return EXIT_SUCCESS;
}
