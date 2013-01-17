///////////////////////////////////////////////////////////
//  Egyeb.h
//  Implementation of the Class Citizen
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)
#define EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_

#include "Members.h"

class Citizen : public Members
{

public:
	Citizen(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){

    _kolcs_hossz=30;	 // kölcsönzés max hossza hossza napokban
	_max_konyv = 4;
	}
	virtual ~Citizen();
	bool Loan(Books mit, int datumtol);
	bool Return(Books mit);

};
#endif // !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)
