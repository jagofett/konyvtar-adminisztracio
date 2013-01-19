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

class Student : public Members //Egyetemi hallgatókat  tartalmazó leszármazott osztály
{

public:
	Student(std::string nev, std::string cim, std::string eler): Members(nev, cim, eler){//a szülö konstruktora, + a specifikus értékek beállítása

    _kolcs_hossz=60;	 // kölcsönzés max hossza hossza napokban
	_max_konyv = 5;
	_tipus = "Egyetemi hallgató";
	_tid= 1;
	}
	virtual ~Student(){}
    std::string DateWhen(std::string datum){MyDate date(datum);date.addMonth();date.addMonth();return date.getDate();}//visszahozási dátum számítása (sztring)
};
#endif // !defined(EA_DC6545E7_A9DB_4a2f_9FE0_067DC9B1F53E__INCLUDED_)
