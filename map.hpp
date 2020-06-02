#ifndef MAP_HPP
#define MAP_HPP
#include "bouclier.hpp"
#include "grandir.hpp"
#include "rapetisser.hpp"
#include "reparer.hpp"
#include "robot.hpp"
#include <vector>
#include <ctime>


#define POS_SOL 700
#define TIMER_MAP 250
#define NB_COLLECTABLE 4


class Map {

	private :
		int index;
		Texture fond;
		Texture mur;
		Sprite spriteFond;
		Sprite spriteSol;
		vector<Sprite> objets;
		vector<Collectable *> c;
		float timerMap;


	public :

		Map(int index);

		void create();
		void creation_objets();
		void ajoutCollectable();
		void updateMap();
		void ajouterSpriteListeCollec(Collectable *cnew);
		void supprimerCollec(int indice);
		void supprimerObjet(int indice);
		void setPosCollec(float x, float y, int indice);
		void moveCollec(Vector2f v, int indice);
		void gestionCollectable(Collectable *co, Robot *rob);
		void vider();

		Sprite getSpriteFond() const;
		Sprite getSpriteSol() const;
		Sprite getSpriteCollec(int indice) const;
		bool getSpriteStable(int i) const;
		vector<Sprite> getListObjets() const;
		IntRect getRectObj(int indice) const;
		vector<Collectable *> getListCollec() const;
		IntRect getRectColl(int indice) const;
		int getTimerMap() const;
		void setListCollec(Collectable *cnew, int i);
		void setSpriteStable(bool a, int i);
		void setIndex(int i);
		void setTimerMap(int t);


};
#endif
