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
else{throw INVALID_LOAN;}

}
bool Members::Loan(Books* mit, string datumtol){
if (_kivett.size()>=_max_konyv){throw INVALID_LOAN;}
Loan_L(mit, datumtol);

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
MyDate d((*it)->GetDate());
kul = d.maElter();
kul = _kolcs_hossz-kul;
_kivett.erase(it);
(*it)->Return();
return kul;
}else{throw INVALID_RETURN;}

}



void Members::Edit(){

}


void Members::Space(const int db, const string &mit) const{
for(int i=0;i<db;i++) {cout <<" ";}}
void Members::list(){
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;

 cout<< _id << "\t" <<  _nev;
 Space(30-_nev.length(), " ");
 cout  <<  _lakcim;
 Space(30-_lakcim.length(), " ");
 cout <<  _eler;
 Space(30-_eler.length(), " ");
 cout << _tipus << endl;
 /*for(unsigned int i=0;i<_kivett.size();i++){
    string date =_kivett[i]->GetDate();
    cout << i+1 << "-nek k�lcs�nz�tt k�nyv ID-je: " << _kivett[i]->GetId() << "\t D�tuma: " << date << "\tVisszahoz�s d�tuma: ";
    date = DateWhen(date);

    cout <<date << endl;

 }*/
//spec();
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
