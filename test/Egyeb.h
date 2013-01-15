///////////////////////////////////////////////////////////
//  Egyeb.h
//  Implementation of the Class Oth_citizen
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)
#define EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_

#include "Members.h"

class Oth_citizen : public Members
{

public:
	void Oth_citizen();
	virtual void ~Oth_citizen();
	book Loan(Books mit, int datumtol);
	bool Return(Books mit);

};
#endif // !defined(EA_EDA710D9_7DA0_45c9_A572_2F7B636FB49A__INCLUDED_)
