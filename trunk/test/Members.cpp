#include <iostream>
#include <cstdlib>
#include "Members.h"
#include "Date.hpp"
using namespace std;

int Members::nextId = 1;

/**
 * kölcsönzés: figyelni, hogy a könyv kölcsönözhetõ, és a tag még kölcsönözhet, ha
 * sikertelen hamis érték visszaadás
 *
 * tagtípusonként változik a kölcsönzõ mûvelet
 */
bool Members::Loan_L(Books* mit, string datumtol){ //a para
if(((mit)->Loan(datumtol, this))){_kivett.push_back(mit);return true;} //ha nincs még kikölcsönözve, felvesszük a listába
else{return false;}

}
bool Members::Loan(Books* mit, string datumtol){
if (_kivett.size()>=_max_konyv){return false;}
return Loan_L(mit, datumtol);

}

/**
 * ha történt késés, igaz értéket ad vissza
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
//formázás, fejléc kiírása
cout << " ID\t" <<  "NÉV";
Space(27, " ");
cout <<  "LAKCÍM";
Space(44, " ");
cout << "ELÉRHETÖSÉG";
Space(29, " ");
cout  << "TAGTÍPUS" << "\t\t" << "KÖLCSÖNZÉSEK" << endl;
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
    cout << i+1 << "-nek kölcsönzött könyv ID-je: " << _kivett[i]->GetId() << "\t Dátuma: " << date << "\tVisszahozás dátuma: ";
    date = DateWhen(date);

    cout <<date << endl;

 }*/
}

void Members::list_det(){
cout << "-- Tag részletes adatai: --" << endl << endl;
Space(40, "-");cout << endl;
cout << "Típus:\t\t" << _tipus << endl;
cout << "Név:\t\t" <<  _nev << endl;
cout << "Lakcím:\t\t"<<  _lakcim << endl;
cout << "Elérhetöség:\t"<<  _eler << endl;
cout << "Kölcsönzések:\t";
if(_kivett.size()==0){cout << "NINCS KÖLCSÖNZÖTT KÖNYV" << endl;}
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
