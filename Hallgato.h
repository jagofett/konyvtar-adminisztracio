///////////////////////////////////////////////////////////
//  Hallgato.h
//  Implementation of the Class Student
//  Created on:      28-nov.-2012 18:55:43
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_)
#define EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_

#include "Members.h"
#include "Date.hpp"

class Student : public Members //Egyetemi hallgat�kat  tartalmaz� lesz�rmazott oszt�ly
{

public:
	Student(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){//a sz�l� konstruktora, + a specifikus �rt�kek be�ll�t�sa

    _kolcs_hossz=60;	 // k�lcs�nz�s max hossza hossza napokban
	_max_konyv = 5;
	_tipus = "Egyetemi hallgat�";
	_tid= 1;
	}
	virtual ~Student(){}
    std::string DateWhen(std::string datum){MyDate date(datum);date.addMonth();date.addMonth();return date.getDate();}//visszahoz�si d�tum sz�m�t�sa (sztring)
};
#endif // !defined(EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_)
