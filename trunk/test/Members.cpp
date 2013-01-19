#include <iostream>
#include <cstdlib>
#include "Members.h"
#include "Date.hpp"
using namespace std;

int Members::nextId = 1;

/**
 * k�lcs�nz�s: figyelni, hogy a k�nyv k�lcs�n�zhet�, �s a tag m�g k�lcs�n�zhet, ha
 * sikertelen hamis �rt�k visszaad�s
 *
 * tagt�pusonk�nt v�ltozik a k�lcs�nz� m�velet
 */
bool Members::Loan_L(Books* mit, string datumtol){ //a para
if(((mit)->Loan(datumtol, this))){_kivett.push_back(mit);return true;} //ha nincs m�g kik�lcs�n�zve, felvessz�k a list�ba
else{return false;}

}
bool Members::Loan(Books* mit, string datumtol){
if (_kivett.size()>=_max_konyv){return false;}
return Loan_L(mit, datumtol);

}

/**
 * ha t�rt�nt k�s�s, igaz �rt�ket ad vissza
 */

int Members::Return(int id){
int kul;
bool talal = false;
vector<Books*>::iterator it;
for(it=_kivett.begin();it!=_kivett.end();++it)
{
    if ((*it)->GetId()==id){ talal = true; break;}
}
if(talal){
MyDate d(DateWhen((*it)->GetDate()));
kul = d.maElter();
//kul = _kolcs_hossz-kul;
//delete *it;
(*it)->Return();
_kivett.erase(it);
return kul;
}else{throw INVALID_RETURN;}

}



void Members::Edit(int func, std::string &mire){
switch(func){
    case 1:
        _nev = mire;
        break;
    case 2:
        _lakcim = mire;
        break;
    case 3:
        _eler = mire;
        break;
}
}

void Members::list_f(){
//form�z�s, fejl�c ki�r�sa
cout << " ID\t" <<  "N�V";
Space(27, " ");
cout <<  "LAKC�M";
Space(44, " ");
cout << "EL�RHET�S�G";
Space(29, " ");
cout  << "TAGT�PUS" << "\t\t" << "K�LCS�NZ�SEK" << endl;
Space(160, "-");
cout << endl;

}

void Members::Space(const int db, const string &mit) const{
for(int i=0;i<db;i++) {cout <<mit;}}


void Members::list(){

 cout << "| " << _id << "\t" <<  _nev;
 Space(30-_nev.length(), " ");
 cout  <<  _lakcim;
 Space(50-_lakcim.length(), " ");
 cout <<  _eler;
 Space(40-_eler.length(), " ");
 cout << _tipus;
 Space(25-_tipus.length(), " ");
 cout << _kivett.size() << " db" << endl;
 /*for(unsigned int i=0;i<_kivett.size();i++){
    string date =_kivett[i]->GetDate();
    cout << i+1 << "-nek k�lcs�nz�tt k�nyv ID-je: " << _kivett[i]->GetId() << "\t D�tuma: " << date << "\tVisszahoz�s d�tuma: ";
    date = DateWhen(date);

    cout <<date << endl;

 }*/
}

void Members::list_det(){
cout << "-- Tag r�szletes adatai: --" << endl << endl;
Space(40, "-");cout << endl;
cout << "T�pus:\t\t" << _tipus << endl;
cout << "N�v:\t\t" <<  _nev << endl;
cout << "Lakc�m:\t\t"<<  _lakcim << endl;
cout << "El�rhet�s�g:\t"<<  _eler << endl;
cout << "K�lcs�nz�sek:\t";
if(_kivett.size()==0){cout << "NINCS K�LCS�NZ�TT K�NYV" << endl;}
else{
    cout << endl << endl;
    _kivett[0]->list_f_det();
    for(unsigned int i=0;i<_kivett.size();i++){
    string date =_kivett[i]->GetDate();
    cout << i+1 << "\t\t";
    _kivett[i]->list_det();
     cout << date << "\t";
    date = DateWhen(date);
    cout <<date << endl;

 }
}
}
ostream& operator<<(ostream &os,const Members *m){
os << m->GetType() << ";" << m->_nev << ";" <<  m->_lakcim<< ";" <<  m->_eler << ";" << m->_kivett.size();
if (m->_kivett.size()!=0) {
os <<";";
for(unsigned int i=0;i<m->_kivett.size();i++)
    {
        //cout << "Utolso: " << !(m->_kivett.size()==i) <<" ";
        os << m->_kivett[i]->GetId()<<";"<<m->_kivett[i]->GetDate();
        if (i+1<m->_kivett.size()){os <<";";}
    }
}

return os;
}
