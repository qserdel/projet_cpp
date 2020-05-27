#ifndef COLLECTABLE_HPP
#define COLLECTABLE_HPP
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

using namespace sf;


class Collectable {

	protected :
		Texture txt;
		Sprite sp;
		bool action_imediate;

	public :

		Collectable();
		void apparition();
		
		Sprite getSprite();


};
#endif
