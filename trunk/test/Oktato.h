///////////////////////////////////////////////////////////
//  Oktato.h
//  Implementation of the Class Prof
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_084C2B43_2226_49ab_8443_E6E0289A0BB6__INCLUDED_)
#define EA_084C2B43_2226_49ab_8443_E6E0289A0BB6__INCLUDED_

#include "Members.h"
#include "Date.hpp"

class Prof : public Members
{

public:
	Prof(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){

    _kolcs_hossz=365;	 // k�lcs�nz�s max hossza hossza napokban
	_max_konyv = 5000;
	_tipus = "Egyetemi oktat�";
	_tid = 2;
	}
	virtual ~Prof(){}
	bool Loan(Books* mit, std::string datumtol){std::cout << "K�lcs�nz�s t�rt�nt!\n";Members::Loan(mit, datumtol);}
	bool Return(Books mit);
	void spec() {std::cout << "T�pus: " << _tipus << " K�lcs. hossza: " << _kolcs_hossz << ", maxim�lis k�nyvsz�m: " <<_max_konyv << std::endl;}
    std::string DateWhen(std::string datum){MyDate date(datum);date+365;return date.getDate();}

};
#endif // !defined(EA_084C2B43_2226_49ab_8443_E6E0289A0BB6__INCLUDED_)
