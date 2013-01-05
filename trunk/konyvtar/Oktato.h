///////////////////////////////////////////////////////////
//  Oktato.h
//  Implementation of the Class Prof
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_084C2B43_2226_49ab_8443_E6E0289A0BB6__INCLUDED_)
#define EA_084C2B43_2226_49ab_8443_E6E0289A0BB6__INCLUDED_

#include "Members.h"

class Prof : public Members
{

public:
	void Prof();
	virtual void ~Prof();
	book Loan(Books mit, int datumtol);
	bool Return(Books mit);

};
#endif // !defined(EA_084C2B43_2226_49ab_8443_E6E0289A0BB6__INCLUDED_)
