#include <iostream>
#include <cstdlib>
#include "Members.h"
#include "Date.hpp"
using namespace std;

int Members::nextId = 1;


bool Members::Loan_L(Books* mit, string datumtol){ //k�lcs�nz�s maxim�lis ellen�rz�s n�lk�l (beolvas�shoz) k�nyvre mutat� pointer �s egy helyes form�tum� d�tum alapj�n ha a k�nyv szabad k�lcs�nzi, vagy hamis
if(((mit)->Loan(datumtol, this))){_kivett.push_back(mit);return true;} //ha nincs m�g kik�lcs�n�zve, felvessz�k a list�ba
else{return false;}

}
bool Members::Loan(Books* mit, string datumtol){ //max ellen�rz�tt k�lcs�nz�s (param�terek mint el�bb)
if (_kivett.size()>=_max_konyv){return false;}  //ha m�r nem k�lcs�n�zhet, hamis �rt�k visszaad�sa
return Loan_L(mit, datumtol); //egy�bk�nt az el�z� m�velet futtat�sa

}

/**
 * ha t�rt�nt k�s�s, igaz �rt�ket ad vissza
 */

int Members::Return(int id){  //adott id-ju k�nyv visszav�tele, visszat�r a v�rhat� visszahozatal �s a mai nap k�l�nbs�g�vel napokban (k�s�s)
int kul; //k�l�nbs�g
bool talal = false; //k�nyv keres�se
vector<Books*>::iterator it;
for(it=_kivett.begin();it!=_kivett.end();++it) //v�gigmegy�nk a k�lcs�nz�seket tartalmaz� vektoron, �s ha van megadott id-j� k�nyv meg�llunk
{
    if ((*it)->GetId()==id){ talal = true; break;}
}
if(talal){ //ha tal�ltunk k�nyvet, lek�rdezz�k a d�tum�t, a max visszahoz�si id�pontot
MyDate d(DateWhen((*it)->GetDate())); //saj�t date oszt�ly haszn�lata (napokban t�rolja a d�tumot)
kul = d.maElter(); //a k�s�s kisz�m�t�sa (k�s�s ha 0<)
//kul = _kolcs_hossz-kul;
//delete *it;
(*it)->Return(); //a k�nyv visszviv� fv-�nek megh�v�sa, majd t�rl�s a list�b�l
_kivett.erase(it); //k�lcs�nz�s t�rl�se
return kul;//visszat�r�s a k�s�ssel (ha 0<)
}else{throw INVALID_RETURN;} //ha nincs id, kiv�tel dob�sa

}



void Members::Edit(int func, std::string &mire){ //szerkeszt�s 1-n�v, 2-c�m, 3-el�rhet�s�g, �rt�kek be�ll�t�sa
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

}

void Members::list_det(){ //adott tag r�szletes adatainak kiirat�sa
cout << "-- Tag r�szletes adatai: --" << endl << endl;
Space(40, "-");cout << endl;
cout << "T�pus:\t\t" << _tipus << endl;
cout << "N�v:\t\t" <<  _nev << endl;
cout << "Lakc�m:\t\t"<<  _lakcim << endl;
cout << "El�rhet�s�g:\t"<<  _eler << endl;
cout << "K�lcs�nz�sek:\t";
if(_kivett.size()==0){cout << "NINCS K�LCS�NZ�TT K�NYV" << endl;} // ha nincs k�lcs�nz�s, akkor ezt �rjuk ki, k�l�nben felsoroljuk a kivett k�nyveket
else{
    cout << endl << endl;
    _kivett[0]->list_f_det(); //fejl�c
    for(unsigned int i=0;i<_kivett.size();i++){
    string date =_kivett[i]->GetDate(); //kiv�tel d�tuma
    cout << i+1 << "\t\t"; //ki�rjuk a sorsz�mot
    _kivett[i]->list_det(); //a konkr�t k�nyvet
     cout << date << "\t"; //kiv�tel d�tum�t,
    date = DateWhen(date); //visszahoz�s d�tum�nak sz�m�t�sa
    cout <<date << endl; //�s ki�r�sa

 }
}
}
ostream& operator<<(ostream &os,const Members *m){ //ki�r� oper�tor
os << m->GetType() << ";" << m->_nev << ";" <<  m->_lakcim<< ";" <<  m->_eler << ";" << m->_kivett.size(); //;-el elv�lasztva az alap adatok, �s hogy h�ny k�lcs�nz�s van
if (m->_kivett.size()!=0) { //ha 0 k�sz vagyunk
os <<";"; //ha t�bb felsoroljuk �ket
for(unsigned int i=0;i<m->_kivett.size();i++)
    {
        //cout << "Utolso: " << !(m->_kivett.size()==i) <<" ";
        os << m->_kivett[i]->GetId()<<";"<<m->_kivett[i]->GetDate(); //ki�rjuk a k�nyv id-j�t, �s a kezdeti d�tumot
        if (i+1<m->_kivett.size()){os <<";";} //ha nem az utols�n�l j�runk, ;-is �runk
    }
}

return os; //visszat�r�nk, hogy lehessen << << << halmozni
}
