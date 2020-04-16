#ifndef EQUIPEMENT_HPP
#define EQUIPEMENT_HPP
#include <iostream>

using namespace std;

class Equipement {

	private :
		string _name;

	public :
	
		Equipement(){
			_name="vide";			
		}
		
		Equipement(string name){
			_name=name;			
		}
	

};
#endif
