#ifndef ARME_HPP
#define ARME_HPP
#include <iostream>

using namespace std;

class Arme {

	private :
		string _name;
		float debit;  // tirs par seconde
		int puissance; // en pv
		int munitions; // nombre de munitions dans l'arme
		string type_tir;


	public :
		Arme(){
			_name="Pisto-Laser";
			debit = 1;
			puissance = 1;
			munitions= 10000;
			type_tir="droit";
		}
		Arme(string name){
			_name=name;
			if(name=="Carabine-Laser"){
				debit = 0.75;
				puissance = 3;
				munitions=6;
				type_tir="droit";
			}
			else if(name=="Gatling-laser"){
				debit = 3;
				puissance = 1;
				munitions=30;
				type_tir="droit";
			}
			else if(name=="Shotgun-Galaxy"){
				debit = 0.75;
				puissance = 2;
				munitions=8;
				type_tir="angle";
			}
		}



};
#endif
