///////////////////////////////////////////////////////////
//  Members.h
//  Implementation of the Class Members
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_E20A01E4_A0E8_46e7_B222_1829BCB89111__INCLUDED_)
#define EA_E20A01E4_A0E8_46e7_B222_1829BCB89111__INCLUDED_

#include "Konyv.h"

/**
 * tipus a gyerekei közul valasztjuk ki.
 */
class Members
{

public:
	void Members();
	virtual void ~Members();
	virtual bool Loan(Books mit, int datumtol);
	virtual bool Return(Books mit);
	void Edit();

private:
	std::string nev;
	std::string lakcim;
	/**
	 * mobilszam vagy email
	 */
	std::string elerhetoseg;
	/**
	 * a kikölcsönzött könyvek listája
	 */
	list<Books*> kivett;
	/**
	 * kölcsönzés hossza napokban
	 */
	int kolcs_hossz;
	/**
	 * kolcsonzott konyvek szama
	 */
	int max_konyv;

};
#endif // !defined(EA_E20A01E4_A0E8_46e7_B222_1829BCB89111__INCLUDED_)
