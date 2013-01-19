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

class Admin //bejelentkeztet�st v�gz� oszt�ly
{

public:

	Admin(); //pass.dat megnyit�sa, �s a benne l�v� adatok beolvas�sa a megfelel� vektorokba, kiv�telek dob�sa, ha nem l�tezik a f�jl, vagy hib�s
	virtual ~Admin(){}


	bool Login(); //bejelentkeztet�si folyamat, 3 lehet�s�g, sz�vegek ki�r�sa, �s a m�sik Login h�v�sa a megfelel� param�terekkel
	enum Exception {MISSING_FILE,BAD_INPUT}; //a nevek maguk�rt besz�lnek

private:
	bool Login(std::string name, std::string pass); //t�nyleges ellen�rz�st v�gz� oszt�ly, igaz ha l�tezik a megadott jelsz� n�v p�ros
	std::vector<std::string> jelszo;
	std::vector<std::string> nev;

};
#endif // !defined(ADMIN_H)
