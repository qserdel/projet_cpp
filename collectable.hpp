#ifndef COLLECTABLE_HPP
#define COLLECTABLE_HPP
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

enum {BOUCLIER, GRANDIR, RAPETISSER, REPARER};

using namespace sf;


class Collectable {

	protected :
		Texture txt;
		Sprite sp;
		bool action_imediate;
		int number;
		bool spriteStable = false;

	public :

		Collectable();
		Collectable(int n);
		Collectable(Collectable const& copy);
		
		void move(Vector2f v);
		void setPos(float x, float y);
		
		Sprite getSprite() const;
		int getNumber() const;
		bool getSpriteStable() const;
		void setSprite(Sprite s);
		void setSpriteStable(bool a);


};
#endif
