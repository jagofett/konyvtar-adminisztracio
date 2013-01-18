///////////////////////////////////////////////////////////
//  Konyv.cpp
//  Implementation of the Class Books
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#include <iostream>
#include "Konyv.h"

using namespace std;

int Books::nextId = 1; //az elso könyv id-je.

Books::Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn) :  _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    _szabad = true;
    _id = ++nextId;
    _datum = "0"; //nincs kölcsönözve
}
Books::Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn) : _id(id), _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    if (id>nextId)
    {
        nextId=id;
    }
    _szabad = true; //a tagok betoltesekor allitjuk be
    _datum = "0"; //nincs kölcsönözve
} //betolteskor meghivott konstruktors


bool Books::Loan(string datum, Members* ki) {
    if(this->_szabad) {_szabad = false; _datum=datum; _ki = ki;return true;} //ha szabad a könyv, kölcsönzés beállítása, egyébként hamissal visszatérés
    else {return false;}
} //kolcsonzes, datum beallitasa
void Books::list()
{
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;
string kol = (_szabad)? "igen":"nem";
    cout<< _id << "\t" <<  _szerzo<< "\t" <<  _cim << "\t\t" <<  _kiado << "\t\t" <<  _evszam << "\t" <<  _kiadas << ". kiadas\t" <<  _isbn << "\t " << kol;
    if (_ki != 0){cout << " (" << _ki->GetNev() << ", id=" << _ki->GetId() <<")";}
    cout << endl;
}


/**
 * könyv szerkesztése
 */
void Books::Edit()
{

}

ostream& operator<<(ostream &os,const Books &b)
{
    os << b._id << ";" <<  b._szerzo<< ";" <<  b._cim << ";" <<  b._kiado << ";" <<  b._evszam << ";" <<  b._kiadas << ";" <<  b._isbn  << endl;

    return os;
}
