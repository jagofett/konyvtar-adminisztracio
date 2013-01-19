#include <iostream>
#include <cstdlib>
#include "Members.h"
#include "Date.hpp"
using namespace std;

int Members::nextId = 1;


bool Members::Loan_L(Books* mit, string datumtol){ //kölcsönzés maximális ellenörzés nélkül (beolvasáshoz) könyvre mutató pointer és egy helyes formátumú dátum alapján ha a könyv szabad kölcsönzi, vagy hamis
if(((mit)->Loan(datumtol, this))){_kivett.push_back(mit);return true;} //ha nincs még kikölcsönözve, felvesszük a listába
else{return false;}

}
bool Members::Loan(Books* mit, string datumtol){ //max ellenörzött kölcsönzés (paraméterek mint elöbb)
if (_kivett.size()>=_max_konyv){return false;}  //ha már nem kölcsönözhet, hamis érték visszaadása
return Loan_L(mit, datumtol); //egyébként az elözö müvelet futtatása

}

/**
 * ha történt késés, igaz értéket ad vissza
 */

int Members::Return(int id){  //adott id-ju könyv visszavétele, visszatér a várható visszahozatal és a mai nap különbségével napokban (késés)
int kul; //különbség
bool talal = false; //könyv keresése
vector<Books*>::iterator it;
for(it=_kivett.begin();it!=_kivett.end();++it) //végigmegyünk a kölcsönzéseket tartalmazó vektoron, és ha van megadott id-jü könyv megállunk
{
    if ((*it)->GetId()==id){ talal = true; break;}
}
if(talal){ //ha találtunk könyvet, lekérdezzük a dátumát, a max visszahozási idöpontot
MyDate d(DateWhen((*it)->GetDate())); //saját date osztály használata (napokban tárolja a dátumot)
kul = d.maElter(); //a késés kiszámítása (késés ha 0<)
//kul = _kolcs_hossz-kul;
//delete *it;
(*it)->Return(); //a könyv visszvivó fv-ének meghívása, majd törlés a listából
_kivett.erase(it); //kölcsönzés törlése
return kul;//visszatérés a késéssel (ha 0<)
}else{throw INVALID_RETURN;} //ha nincs id, kivétel dobása

}



void Members::Edit(int func, std::string &mire){ //szerkesztés 1-név, 2-cím, 3-elérhetöség, értékek beállítása
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

}

void Members::list_det(){ //adott tag részletes adatainak kiiratása
cout << "-- Tag részletes adatai: --" << endl << endl;
Space(40, "-");cout << endl;
cout << "Típus:\t\t" << _tipus << endl;
cout << "Név:\t\t" <<  _nev << endl;
cout << "Lakcím:\t\t"<<  _lakcim << endl;
cout << "Elérhetöség:\t"<<  _eler << endl;
cout << "Kölcsönzések:\t";
if(_kivett.size()==0){cout << "NINCS KÖLCSÖNZÖTT KÖNYV" << endl;} // ha nincs kölcsönzés, akkor ezt írjuk ki, különben felsoroljuk a kivett könyveket
else{
    cout << endl << endl;
    _kivett[0]->list_f_det(); //fejléc
    for(unsigned int i=0;i<_kivett.size();i++){
    string date =_kivett[i]->GetDate(); //kivétel dátuma
    cout << i+1 << "\t\t"; //kiírjuk a sorszámot
    _kivett[i]->list_det(); //a konkrét könyvet
     cout << date << "\t"; //kivétel dátumát,
    date = DateWhen(date); //visszahozás dátumának számítása
    cout <<date << endl; //és kiírása

 }
}
}
ostream& operator<<(ostream &os,const Members *m){ //kiíró operátor
os << m->GetType() << ";" << m->_nev << ";" <<  m->_lakcim<< ";" <<  m->_eler << ";" << m->_kivett.size(); //;-el elválasztva az alap adatok, és hogy hány kölcsönzés van
if (m->_kivett.size()!=0) { //ha 0 kész vagyunk
os <<";"; //ha több felsoroljuk öket
for(unsigned int i=0;i<m->_kivett.size();i++)
    {
        //cout << "Utolso: " << !(m->_kivett.size()==i) <<" ";
        os << m->_kivett[i]->GetId()<<";"<<m->_kivett[i]->GetDate(); //kiírjuk a könyv id-ját, és a kezdeti dátumot
        if (i+1<m->_kivett.size()){os <<";";} //ha nem az utolsónál járunk, ;-is írunk
    }
}

return os; //visszatérünk, hogy lehessen << << << halmozni
}
