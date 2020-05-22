#ifndef MAP_HPP
#define MAP_HPP
#include "obstacle.hpp"
#include "collectable.hpp"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

# define POS_SOL 700

using namespace sf;
using namespace std;

class Map {

	private :
		Obstacle *obs;
		Collectable *collect;
		Texture fond;
		Texture mur;
		Sprite spriteFond;
		Sprite spriteSol;
		vector<Sprite> objets;
		
	
	public :
	
		Map();
		
		void creation_objets();
		Sprite getSpriteFond() const;
		Sprite getSpriteSol() const;
		vector<Sprite> getListObjets() const;
		IntRect getRectObj(int indice) const;


};
#endif

