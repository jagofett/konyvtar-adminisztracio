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

int Books::nextId = 1; //az elso k�nyv id-je.
int Books::_sz_len = 0; //alap�rtelmezett szerz�hossz
int Books::_k_len = 0; //alap�rtelmezett kiado
int Books::_c_len = 0; //alap�rtelmezett cim



Books::Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn) :  _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    _szabad = true; //l�trej�ttekor nincs kolcsonozve
    _id = ++nextId; //be�ll�tjuk a jelenlegi id-t majd n�velj�k a statikus �rt�jket
    _datum = "0"; //nincs k�lcs�n�zve, �gy 0
    _ki = 0; //nem k�lcs�n�zte senki
    //hosszmeg�llap�t�s
    _sz_len = (szerzo.size()>_sz_len && szerzo.size()<=40)? szerzo.size():_sz_len;
    _k_len = (kiado.size()>_k_len && kiado.size()<=40)? kiado.size():_k_len;
    _c_len = (cim.size()>_c_len && cim.size()<=40)? cim.size():_c_len;
}
Books::Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn) : _id(id), _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
{
    if (id>nextId)
    {
        nextId=id; //k�vetkez� id meghat�roz�sa: ha a beolvasottak k�zt van nagyobb, akkor arra �ll�tjuk
    }
    _szabad = true; //a tagok betoltesekor allitjuk be
    _datum = "0"; //nincs k�lcs�n�zve
    _ki = 0;
    _sz_len = (szerzo.size()>_sz_len && szerzo.size()<=40)? szerzo.size():_sz_len;
    _k_len = (kiado.size()>_k_len && kiado.size()<=40)? kiado.size():_k_len;
    _c_len = (cim.size()>_c_len && cim.size()<=40)? cim.size():_c_len;
} //betolteskor meghivott konstruktors


bool Books::Loan(string datum, Members* ki) {
    if(this->_szabad) {_szabad = false; _datum=datum; _ki = ki;return true;} //ha szabad a k�nyv, k�lcs�nz�s be�ll�t�sa, egy�bk�nt hamissal visszat�r�s
    else {return false;}
} //kolcsonzes, datum beallitasa v�ge

void Books::list() //egyszer� list�z�s
{
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;
string kol = (_szabad)? "+":"-"; //szabadhoz megfelel� karakter
string tab = (_isbn.size()<17)? "\t\t":"\t";  //elv�laszt�s hossz alapj�n
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
    cout <<  "C�M";
    Space(_c_len-1, " ");
    cout <<  "KIAD�";
    Space(_k_len-4, " ");
    cout <<  "�VSZ�M\t" << "KIAD�S\t" <<  "ISBN\t\t"<< "K�LCS�N�ZHET�" <<  endl;
    Space(160, "-");
    cout << endl;

}

void Books::list_f_det(){
    cout<< "No.\t" <<  "SZERZO";
    Space(_sz_len-4, " ");
    cout <<  "C�M";
    Space(_c_len-1, " ");
    cout <<  "KIAD�";
    Space(_k_len-4, " ");
    cout <<  "�VSZ�M\t" << "KIAD�S\t" <<  "ISBN\t\t  "<< "KIV�TEL" << "\t\t" << "VISSZAHOZ�S" <<  endl;
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

string Books::ToLower(string mit){ //string kisbet�ss� alak�t�sa, keres�shez pl (karakterenk�nt alkalmazzuk a be�p�tett fv-t)
for(int i=0;i<mit.size();++i)
{
    mit[i] = tolower(mit[i]);
}
return mit;
}

/**
 * k�nyv keres�se
 */
bool Books::Search(int mit, std::string& szoveg) //keres�s: 1-szerz�, 2-cim, 3-isbn, 4-id
{
stringstream sor; //id-hoz sz�ks�ges, hogy sztring-� tudjuk alak�tani
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
return found; //tal�ltunk-e eredm�nyt

}

ostream& operator<<(ostream &os,const Books *b) //megfelel� form�tum� ki�r�s
{
    os << b->_id << ";" <<  b->_szerzo<< ";" <<  b->_cim << ";" <<  b->_kiado << ";" <<  b->_evszam << ";" <<  b->_kiadas << ";" <<  b->_isbn << endl;

    return os;
}
