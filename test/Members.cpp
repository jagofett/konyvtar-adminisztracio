#include <iostream>
#include <stdio.h>
#include "Members.h"
//#include "Date.hpp"
using namespace std;
class MyDate;
int Members::nextId = 1;
 Members::~Members(){

}


/**
 * k�lcs�nz�s: figyelni, hogy a k�nyv k�lcs�n�zhet�, �s a tag m�g k�lcs�n�zhet, ha
 * sikertelen hamis �rt�k visszaad�s
 *
 * tagt�pusonk�nt v�ltozik a k�lcs�nz� m�velet
 */
bool Members::Loan_L(Books* mit, string datumtol){ //a para

if(((mit)->Loan(datumtol, this))){_kivett.push_back(mit);return true;} //ha nincs m�g kik�lcs�n�zve, felvessz�k a list�ba
else{return  false;}

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
//MyDate d((*it)->GetDate());
//kul = d.maElter();
cout <<kul << " napja vetted ki!\n";
_kivett.erase(it);
(*it)->Return();
}else{throw INVALID_RETURN;}
}



void Members::Edit(){

}

void Members::list(){
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;

 cout<< _id << "\t" <<  _nev<< "\t" <<  _lakcim << "\t" <<  _eler  << endl;
 for(unsigned int i=0;i<_kivett.size();i++){
   cout << i << "-nek k�lcs�nz�tt k�nyv ID-je: " << _kivett[i]->GetId() << "\t D�tuma: " << _kivett[i]->GetDate() << endl;
 }
}

ostream& operator<<(ostream &os,const Members &m){
os << m._nev << ";" <<  m._lakcim<< ";" <<  m._eler << ";" << m._kivett.size();
if (m._kivett.size()!=0) {
os <<";";
for(unsigned int i=0;i<m._kivett.size();i++)
    {
        //cout << "Utolso: " << !(m._kivett.size()==i) <<" ";
        os << m._kivett[i]->GetId()<<";"<<m._kivett[i]->GetDate();
        if (i+1<m._kivett.size()){os <<";";}
    }
}
    os << endl;

return os;
}
