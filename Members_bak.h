///////////////////////////////////////////////////////////
//  Members.h
//  Implementation of the Class Members
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(MEMBERS_H)
#define MEMBERS_H

#include <queue>
#include "Konyv.h"


/**
 * tipus a gyerekei k�zul valasztjuk ki.
 */
class Members
{

public:
	Members();
	~Members();
	virtual bool Loan(Books mit, int datumtol);
	virtual bool Return(Books mit);
	void Edit();

private:
	std::string nev;
	std::string lakcim;
	std::string elerhetoseg;
	//std::deque<Books*> kivett; //a kik�lcs�nz�tt k�nyvek list�ja
	int kolcs_hossz;	 // k�lcs�nz�s max hossza hossza napokban
	int max_konyv; //max kolcsonzott konyvek szama

};
#endif // !defined(MEMBERS_H)
