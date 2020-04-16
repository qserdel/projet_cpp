#include "forme.hpp"

const bool Forme::contact(const Forme& f){

	return false; //TODO remplir ça
}

void Forme::move(const int& x, const int& y){
	this->_x=x;
	this->_y=y;
}

void Forme::afficher(RenderWindow window){
	this->_s.setPosition(Vector2f(this->_x, this->_y));
	window.draw(_s);
}
