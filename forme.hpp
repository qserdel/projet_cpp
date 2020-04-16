#ifndef FORME_HPP
#define FORME_HPP
#include <SFML/Graphics.hpp>
using namespace sf;

class Forme{
	private:
		//la position du coin haut gauche du rectangle
		int _x;
		int _y;
		//hauteur
		int _h;
		//largeur
		int _l;
		//Sprite attachée à la forme
		Sprite _s;
	public:

		Forme(const int h, const int l, const Sprite s){
			_x=0;
			_y=0;
			_h=h;
			_l=l;
			_s=s;
		}

		Forme(const int x, const int y, const int h, const int l, const Sprite s){
			_x=x;
			_y=y;
			_h=h;
			_l=l;
			_s=s;
		}

		const int getX() const {
			return _x;
		}

		const int getY() const {
			return _y;
		}

		const bool contact(const Forme& f);
		void move(const int& x, const int& y);
		void afficher(RenderWindow window);

		Forme& operator=(const Forme& f) {
			_x=f._x;
			_y=f._y;
			_h=f._h;
			_l=f._l;
			_s=f._s;
			return *this;
		}

};

#endif
