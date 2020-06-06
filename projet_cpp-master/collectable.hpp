#ifndef COLLECTABLE_HPP
#define COLLECTABLE_HPP
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include "robot.hpp"
#include "parametres.hpp"

// Classe abstraite
class Collectable {

	protected :
		sf::Texture txt;
		sf::Sprite sp;
		bool action_imediate;
		bool spriteStable = false;

	public :

		Collectable();
		Collectable(Collectable const& copy);
		
		virtual ~Collectable();
		
		virtual void activation(Robot &r) = 0; // Fonction virtuelle pure
		void move(sf::Vector2f v);
		void setPos(float x, float y);
		
		sf::Sprite getSprite() const;
		bool getSpriteStable() const;
		void setSprite(sf::Sprite s);
		void setSpriteStable(bool a);


};
#endif
