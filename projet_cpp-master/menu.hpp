#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {

	private :
		Texture fond;
		Texture play;
		Texture fondMap;
		Sprite spriteFond;
		Sprite spritePlay;
		Sprite spriteFondMap;
		int index=0;
	public :

		Menu();
		Sprite getFond() const;
		Sprite getPlay() const;
		Sprite getFondMap() const;
		int getIndex() const;

		void setIndex(int i);


};
#endif
