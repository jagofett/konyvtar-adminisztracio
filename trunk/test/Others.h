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
    _kolcs_hossz=14;	 // k�lcs�nz�s max hossza hossza napokban
	_max_konyv = 2;
	_tipus = "Egy�b";
	}
	~Others(){}
	bool Loan(Books* mit, std::string datumtol){std::cout << "K�lcs�nz�s t�rt�nt!\n";Members::Loan(mit, datumtol);}

	void spec() {std::cout << "T�pus: " << _tipus << " K�lcs. hossza: " << _kolcs_hossz << ", maxim�lis k�nyvsz�m: " <<_max_konyv << std::endl;}
};
#endif // !defined(EA_FF0C5023_C9EF_4aff_97AF_AF32717F92E0__INCLUDED_)
