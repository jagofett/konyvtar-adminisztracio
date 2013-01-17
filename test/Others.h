///////////////////////////////////////////////////////////
//  Others.h
//  Implementation of the Class Others
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_FF0C5023_C9EF_4aff_97AF_AF32717F92E0__INCLUDED_)
#define EA_FF0C5023_C9EF_4aff_97AF_AF32717F92E0__INCLUDED_

#include "Members.h"

class Others : public Members
{

public:
	Others(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){
    //{
    //Members(nev, cim, eler);
    _kolcs_hossz=14;	 // kölcsönzés max hossza hossza napokban
	_max_konyv = 2;
	_tipus = "Egyéb";
	}
	~Others(){}
	bool Loan(Books* mit, std::string datumtol){std::cout << "Kölcsönzés történt!\n";Members::Loan(mit, datumtol);}

	void spec() {std::cout << "Típus: " << _tipus << " Kölcs. hossza: " << _kolcs_hossz << ", maximális könyvszám: " <<_max_konyv << std::endl;}
};
#endif // !defined(EA_FF0C5023_C9EF_4aff_97AF_AF32717F92E0__INCLUDED_)
