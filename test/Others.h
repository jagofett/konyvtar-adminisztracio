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
	 Others();
	virtual  ~Others();
	bool Loan(Books mit, int datumtol);
	bool Return(Books mit);

};
#endif // !defined(EA_FF0C5023_C9EF_4aff_97AF_AF32717F92E0__INCLUDED_)
