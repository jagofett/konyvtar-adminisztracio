///////////////////////////////////////////////////////////
//  Hallgato.h
//  Implementation of the Class Student
//  Created on:      28-nov.-2012 18:55:43
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_)
#define EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_

#include "Members.h"

class Student : public Members
{

public:
	void Student();
	virtual void ~Student();
	bool Loan(Books mit, int mikortol);
	bool Return(Books mit);

};
#endif // !defined(EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_)
