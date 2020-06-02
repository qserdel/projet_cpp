#include "menu.hpp"

using namespace sf;

Menu::Menu(){
  if(!fond.loadFromFile("images/menu.png"))
    exit(EXIT_FAILURE);
  if(!play.loadFromFile("images/play.png"))
    exit(EXIT_FAILURE);
  if(!fondMap.loadFromFile("images/mapMenu.png"))
    exit(EXIT_FAILURE);
  spriteFond.setTexture(fond);
  spritePlay.setTexture(play);
  spritePlay.setPosition(350,275);
  spriteFondMap.setTexture(fondMap);
}

Sprite Menu::getFond() const {return spriteFond;};
Sprite Menu::getPlay() const {return spritePlay;};
Sprite Menu::getFondMap() const {return spriteFondMap;};
int Menu::getIndex() const {return index;};

void Menu::setIndex(int i) {index=i;};
