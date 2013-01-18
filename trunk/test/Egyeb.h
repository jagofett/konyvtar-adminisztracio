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

class Citizen : public Members
{

public:
	Citizen(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){

    _kolcs_hossz=30;	 // k�lcs�nz�s max hossza hossza napokban
	_max_konyv = 4;
	_tipus = "M�s egytem polg�ra";
	_tid = 3;
	}
	virtual ~Citizen(){}
		void spec() {std::cout << "T�pus: " << _tipus << " K�lcs. hossza: " << _kolcs_hossz << ", maxim�lis k�nyvsz�m: " <<_max_konyv << std::endl;}

	bool Return(Books mit);
    std::string DateWhen(std::string datum){MyDate date(datum);date.addMonth();return date.getDate();}

};
#endif // !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)