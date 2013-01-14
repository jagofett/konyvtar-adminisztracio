///////////////////////////////////////////////////////////
//  Admin.h
//  Implementation of the Class Admin
//  Created on:      28-dec.-2012 19:42:13
//  Original author: Akos
///////////////////////////////////////////////////////////
#if !defined(EA_5009F861_ABFC_4054_9D93_CA94F5B67F7C__INCLUDED_)
#define EA_5009F861_ABFC_4054_9D93_CA94F5B67F7C__INCLUDED_

#include <vector>
#include <iostream>

class Admin
{

public:

	Admin();
	virtual ~Admin(){}

	bool Login(std::string name, std::string pass);
	bool Login();
	enum Exception {MISSING_FILE,BAD_INPUT};

private:
	std::vector<std::string> jelszo;
	std::vector<std::string> nev;

};
#endif // !defined(EA_5009F861_ABFC_4054_9D93_CA94F5B67F7C__INCLUDED_)
