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
int Books::_sz_len = 0; //az elso könyv id-je.
int Books::_k_len = 0; //az elso könyv id-je.
int Books::_c_len = 0; //az elso könyv id-je.



Books::Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn) :  _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    _szabad = true;
    _id = ++nextId;
    _datum = "0"; //nincs kölcsönözve
    _ki = 0;
    _sz_len = (szerzo.size()>_sz_len && szerzo.size()<=40)? szerzo.size():_sz_len;
    _k_len = (kiado.size()>_k_len && kiado.size()<=40)? kiado.size():_k_len;
    _c_len = (cim.size()>_c_len && cim.size()<=40)? cim.size():_c_len;
}
Books::Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn) : _id(id), _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    if (id>nextId)
    {
        nextId=id;
    }
    _szabad = true; //a tagok betoltesekor allitjuk be
    _datum = "0"; //nincs kölcsönözve
    _ki = 0;
    _sz_len = (szerzo.size()>_sz_len && szerzo.size()<=40)? szerzo.size():_sz_len;
    _k_len = (kiado.size()>_k_len && kiado.size()<=40)? kiado.size():_k_len;
    _c_len = (cim.size()>_c_len && cim.size()<=40)? cim.size():_c_len;
} //betolteskor meghivott konstruktors


bool Books::Loan(string datum, Members* ki) {
    if(this->_szabad) {_szabad = false; _datum=datum; _ki = ki;return true;} //ha szabad a könyv, kölcsönzés beállítása, egyébként hamissal visszatérés
    else {return false;}
} //kolcsonzes, datum beallitasa
void Books::list()
{
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;
string kol = (_szabad)? "igen":"nem";
    cout<< _id << "\t" <<  _szerzo;
    Space(_sz_len-_szerzo.size()+2, " ");
    cout <<  _cim;
    Space(_c_len-_cim.size()+2, " ");
    cout <<  _kiado;
    Space(_k_len-_kiado.size()+2, " ");
    cout  <<  _evszam << "\t" <<  _kiadas << ".\t" <<  _isbn << "\t " << kol;
    if (_ki != 0){cout << " (" << _ki->GetNev() << ", id=" << _ki->GetId() <<")";}
    cout << endl;
}
void Books::list_f(){
    cout<< "ID\t" <<  "SZERZO";
    Space(_sz_len-4, " ");
    cout <<  "CÍM";
    Space(_c_len-1, " ");
    cout <<  "KIADÓ";
    Space(_k_len-4, " ");
    cout <<  "ÉVSZÁM\t" << "KIADÁS\t" <<  "ISBN\t\t"<< "KÖLCSÖNÖZHETÖ" <<  endl;
    Space(130, "-");
    cout << endl;

}

/**
 * könyv szerkesztése
 */
void Books::Edit()
{

}

ostream& operator<<(ostream &os,const Books *b)
{
    os << b->_id << ";" <<  b->_szerzo<< ";" <<  b->_cim << ";" <<  b->_kiado << ";" <<  b->_evszam << ";" <<  b->_kiadas << ";" <<  b->_isbn << endl;

    return os;
}
