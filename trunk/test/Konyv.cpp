///////////////////////////////////////////////////////////
//  Konyv.cpp
//  Implementation of the Class Books
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include "Konyv.h"

using namespace std;

int Books::nextId = 1; //az elso könyv id-je.
int Books::_sz_len = 0; //alapértelmezett szerzöhossz
int Books::_k_len = 0; //alapértelmezett kiado
int Books::_c_len = 0; //alapértelmezett cim



Books::Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn) :  _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    _szabad = true; //létrejöttekor nincs kolcsonozve
    _id = ++nextId; //beállítjuk a jelenlegi id-t majd növeljük a statikus értéjket
    _datum = "0"; //nincs kölcsönözve, így 0
    _ki = 0; //nem kölcsönözte senki
    //hosszmegállapítás
    _sz_len = (szerzo.size()>_sz_len && szerzo.size()<=40)? szerzo.size():_sz_len;
    _k_len = (kiado.size()>_k_len && kiado.size()<=40)? kiado.size():_k_len;
    _c_len = (cim.size()>_c_len && cim.size()<=40)? cim.size():_c_len;
}
Books::Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn) : _id(id), _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    if (id>nextId)
    {
        nextId=id; //következö id meghatározása: ha a beolvasottak közt van nagyobb, akkor arra állítjuk
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
} //kolcsonzes, datum beallitasa vége

void Books::list() //egyszerü listázás
{
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;
string kol = (_szabad)? "+":"-"; //szabadhoz megfelelö karakter
string tab = (_isbn.size()<17)? "\t\t":"\t";  //elválasztás hossz alapján
    cout << "| " << _id << "\t" <<  _szerzo;
    Space(_sz_len-_szerzo.size()+2, " ");
    cout <<  _cim;
    Space(_c_len-_cim.size()+2, " ");
    cout <<  _kiado;
    Space(_k_len-_kiado.size()+2, " ");
    cout  <<  _evszam << "\t  " <<  _kiadas << ".\t" <<  _isbn << tab << kol;
    if (_ki != 0){cout << " (" << _ki->GetNev() << ", meddig:" << _ki->DateWhen(_datum) <<")";}
    cout << endl;
}
void Books::list_f(){
    cout<< "  ID\t" <<  "SZERZO";
    Space(_sz_len-4, " ");
    cout <<  "CÍM";
    Space(_c_len-1, " ");
    cout <<  "KIADÓ";
    Space(_k_len-4, " ");
    cout <<  "ÉVSZÁM\t" << "KIADÁS\t" <<  "ISBN\t\t"<< "KÖLCSÖNÖZHETÖ" <<  endl;
    Space(160, "-");
    cout << endl;

}

void Books::list_f_det(){
    cout<< "No.\t" <<  "SZERZO";
    Space(_sz_len-4, " ");
    cout <<  "CÍM";
    Space(_c_len-1, " ");
    cout <<  "KIADÓ";
    Space(_k_len-4, " ");
    cout <<  "ÉVSZÁM\t" << "KIADÁS\t" <<  "ISBN\t\t  "<< "KIVÉTEL" << "\t\t" << "VISSZAHOZÁS" <<  endl;
    Space(160, "-");
    cout << endl;

}

void Books::list_det(){
    string tab = (_isbn.size()<10)? "\t   ":"  ";
    cout  <<  _szerzo;
    Space(_sz_len-_szerzo.size()+2, " ");
    cout <<  _cim;
    Space(_c_len-_cim.size()+2, " ");
    cout <<  _kiado;
    Space(_k_len-_kiado.size()+2, " ");
    cout  <<  _evszam << "\t" <<  _kiadas << ".\t" <<  _isbn << tab;

}

string Books::ToLower(string mit){ //string kisbetüssé alakítása, kereséshez pl (karakterenként alkalmazzuk a beépített fv-t)
for(int i=0;i<mit.size();++i)
{
    mit[i] = tolower(mit[i]);
}
return mit;
}

/**
 * könyv keresése
 */
bool Books::Search(int mit, std::string& szoveg) //keresés: 1-szerzö, 2-cim, 3-isbn, 4-id
{
stringstream sor; //id-hoz szükséges, hogy sztring-é tudjuk alakítani
bool found = false;
switch(mit){

case 1:
    found = ToLower(_szerzo.substr(0,szoveg.size())) ==(ToLower(szoveg));
    break;
case 2:
    found = ToLower(_cim.substr(0,szoveg.size())) ==(ToLower(szoveg));
    break;
case 3:
    found = ToLower(_isbn.substr(0,szoveg.size())) ==(ToLower(szoveg));
    break;
case 4:
    sor << _id;
    found = ToLower(sor.str().substr(0,szoveg.size())) ==(ToLower(szoveg));
    break;
}
return found; //találtunk-e eredményt

}

ostream& operator<<(ostream &os,const Books *b) //megfelelö formátumú kiírás
{
    os << b->_id << ";" <<  b->_szerzo<< ";" <<  b->_cim << ";" <<  b->_kiado << ";" <<  b->_evszam << ";" <<  b->_kiadas << ";" <<  b->_isbn << endl;

    return os;
}
