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
 * tipus a gyerekei közul valasztjuk ki.
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
	//std::deque<Books*> kivett; //a kikölcsönzött könyvek listája
	int kolcs_hossz;	 // kölcsönzés max hossza hossza napokban
	int max_konyv; //max kolcsonzott konyvek szama

};
#endif // !defined(MEMBERS_H)
