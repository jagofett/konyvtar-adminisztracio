#include <iostream>
#include <cstdlib>
#include "Members.h"
#include "Date.hpp"
using namespace std;

int Members::nextId = 1;
 Members::~Members(){

}


/**
 * kölcsönzés: figyelni, hogy a könyv kölcsönözhetõ, és a tag még kölcsönözhet, ha
 * sikertelen hamis érték visszaadás
 *
 * tagtípusonként változik a kölcsönzõ mûvelet
 */
bool Members::Loan_L(Books* mit, string datumtol){ //a para
if(((mit)->Loan(datumtol, this))){_kivett.push_back(mit);return true;} //ha nincs még kikölcsönözve, felvesszük a listába
else{throw INVALID_LOAN;}

}
bool Members::Loan(Books* mit, string datumtol){
if (_kivett.size()>=_max_konyv){throw INVALID_LOAN;}
Loan_L(mit, datumtol);

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

void Members::list(){
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;

 cout<< _id << "\t" <<  _nev<< "\t" <<  _lakcim << "\t" <<  _eler  << endl;
 for(unsigned int i=0;i<_kivett.size();i++){
    MyDate date(_kivett[i]->GetDate());
    cout << i+1 << "-nek kölcsönzött könyv ID-je: " << _kivett[i]->GetId() << "\t Dátuma: " << date << "\tVisszahozás dátuma: ";
    switch(_kolcs_hossz){
    case 365:
        date = date + 365;
        break;
    case 30:
        date.addMonth();
        break;
    case 60:
        date.addMonth();
        date.addMonth();
        break;
    default:
        date = date + _kolcs_hossz;
        break;
    }
    cout <<date << endl;

 }
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
