#ifndef MAP_HPP
#define MAP_HPP
#include "collectable.hpp"
#include "bouclier.hpp"
#include "grandir.hpp"
#include "rapetisser.hpp"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

#define POS_SOL 700
#define TIMER_MAP 200
#define NB_COLLECTABLE 3

using namespace sf;
using namespace std;

class Map {

	private :
		Texture fond;
		Texture mur;
		Sprite spriteFond;
		Sprite spriteSol;
		vector<Sprite> objets;
		vector<Sprite> c;
		float timerMap;
		
	
	public :
	
		Map();
		
		void creation_objets();
		void ajoutCollectable();
		void updateMap();
		void ajouterSpriteListeCollec(Sprite sp);
		
		
		Sprite getSpriteFond() const;
		Sprite getSpriteSol() const;
		vector<Sprite> getListObjets() const;
		IntRect getRectObj(int indice) const;
		vector<Sprite> getListCollec() const;
		IntRect getRectColl(int indice) const;
		void setListCollec(Sprite sp, int i);


};
#endif
