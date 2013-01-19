///////////////////////////////////////////////////////////
//  Egyeb.h
//  Implementation of the Class Citizen
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)
#define EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_

#include "Members.h"
#include "Date.hpp"

class Citizen : public Members //egyéb hallgatókat tartalmazó leszármazott osztály
{

public:
	Citizen(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){ //a szülö konstruktora, + a specifikus értékek beállítása

    _kolcs_hossz=30;	 // kölcsönzés max hossza hossza napokban
	_max_konyv = 4;     //max kölcsönözhetö könyvek száma
	_tipus = "Más egytem polgára"; //típusnév
	_tid = 3;
	}
	virtual ~Citizen(){}
		//void spec() {std::cout << "Típus: " << _tipus << " Kölcs. hossza: " << _kolcs_hossz << ", maximális könyvszám: " <<_max_konyv << std::endl;}

    std::string DateWhen(std::string datum){MyDate date(datum);date.addMonth();return date.getDate();} //visszahozási dátum számítása (sztring)

};
#endif // !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)
