///////////////////////////////////////////////////////////
//  Admin.h
//  Implementation of the Class Admin
//  Created on:      28-dec.-2012 19:42:13
//  Original author: Akos
///////////////////////////////////////////////////////////
#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include <iostream>

class Admin //bejelentkeztetést végzö osztály
{

public:

	Admin(); //pass.dat megnyitása, és a benne lévö adatok beolvasása a megfelelö vektorokba, kivételek dobása, ha nem létezik a fájl, vagy hibás
	virtual ~Admin(){}


	bool Login(); //bejelentkeztetési folyamat, 3 lehetöség, szövegek kiírása, és a másik Login hívása a megfelelö paraméterekkel
	enum Exception {MISSING_FILE,BAD_INPUT}; //a nevek magukért beszélnek

private:
	bool Login(std::string name, std::string pass); //tényleges ellenörzést végzö osztály, igaz ha létezik a megadott jelszó név páros
	std::vector<std::string> jelszo;
	std::vector<std::string> nev;

};
#endif // !defined(ADMIN_H)
