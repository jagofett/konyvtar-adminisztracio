///////////////////////////////////////////////////////////
//  Admin.h
//  Implementation of the Class Admin
//  Created on:      28-dec.-2012 19:42:13
//  Original author: Akos
///////////////////////////////////////////////////////////
#if !defined(ADMIN_H)
#define ADMIIN_H

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
#endif // !defined(ADMIN_H)
