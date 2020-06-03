#ifndef MAP_HPP
#define MAP_HPP
#include "bouclier.hpp"
#include "grandir.hpp"
#include "rapetisser.hpp"
#include "reparer.hpp"
#include "robot.hpp"
#include "parametres.hpp"
#include <vector>
#include <ctime>


class Map {

	private :
		int index;
		sf::Texture fond;
		sf::Texture mur;
		sf::Sprite spriteFond;
		sf::Sprite spriteSol;
		std::vector<sf::Sprite> objets;
		std::vector<Collectable *> c;
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
		void moveCollec(sf::Vector2f v, int indice);
		void gestionCollectable(Collectable *co, Robot *rob);
		void vider();

		sf::Sprite getSpriteFond() const;
		sf::Sprite getSpriteSol() const;
		sf::Sprite getSpriteCollec(int indice) const;
		bool getSpriteStable(int i) const;
		std::vector<sf::Sprite> getListObjets() const;
		sf::IntRect getRectObj(int indice) const;
		std::vector<Collectable *> getListCollec() const;
		sf::IntRect getRectColl(int indice) const;
		int getTimerMap() const;
		void setListCollec(Collectable *cnew, int i);
		void setSpriteStable(bool a, int i);
		void setIndex(int i);
		void setTimerMap(int t);

};
#endif
