///////////////////////////////////////////////////////////
//  Menu.cpp
//  Implementation of the Class Menu
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#include "Menu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "Date.hpp"
#include "Konyv.h"
#include "Admin.h"
#include "Members.h"
#include "Egyeb.h"
#include "Hallgato.h"
#include "Oktato.h"
#include "Others.h"


using namespace std;
Menu::Menu(){
cout << endl << "----Szoftvertechnologia halad� csoport beadando feladat----" << endl << endl;
cout << "N�v:\t\tMagasv�ri �kos" << endl << "ETR-k�d:\tMAATACI.ELTE" << endl << "Neptun-k�d:\tEGB6EB" << endl << "2012-2013-1, 4-es csoport" << endl;
cout << "Feladat �sszefoglalva:" << endl << "K�sz�ts�nk egy egyetemi k�nyvt�r k�lcs�nz�seit nyilv�ntart� rendszert." << endl;
cout << "A rendszer feladata a k�nyvt�r tagjainak, k�nyveinek," << endl <<"illetve  k�nyvt�rosainak nyilv�ntart�sa." << endl << endl << "-----------------------------------------------------------------" << endl << endl;
cout << "�dv�zl�m a K�nyvt�ri Adminisztr�ci�s Rendszerben!" << endl;
if(!Login()){
throw Menu::AUTH_FALIURE;
}
else{LoadData();}
cout << "Az adatok bet�lt�se sikeres!" << endl;
}
Menu::~Menu(){
SaveData();
cout << "Az adatok ment�se sikeres volt!" << endl;
}




void Menu::Run(string type){

int option = 0;
if (type=="main"){
do
{
    WriteMenu(); //f�men� ki�r�sa
    option = GetInteger("Valasztott menupont: ");
    switch(option)
    {
        case 1:
            Run("book");
            break;
        case 2:
            Run("member");
            break;
        case 3:
            Loan();
            break;
        case 4:
            Return();
            break;
//        case 5:
//            //testPrint();
//            break;
    }
}while(option != 0);
}
if (type=="book")
{
do
{
    WriteMenu("book"); //k�nyvek ki�r�sa
    option = GetInteger("Valasztott menupont: ");

    switch(option)
    {
        case 1:
            ManageBook("list");
            break;
        case 2:
            ManageBook("new");
            break;
        case 3:
            ManageBook("delete");
            break;
        case 4:
            SearchBook();
            break;
    }
}while(option != 0);
}
if (type=="member") //tagok menu
{
do
{
    WriteMenu("member"); //k�nyvek ki�r�sa
    option = GetInteger("Valasztott menupont: ");

    switch(option)
    {
        case 1:
            ManageMember("list");
            break;
        case 2:
            ManageMember("new");
            break;
        case 3:
            ManageMember("delete");
            break;
        case 4:
            ManageMember("edit");
            Run("det");
            break;
    }
}while(option != 0);
}
if (type=="det"){
do{
    WriteMenu("det"); //k�nyvek ki�r�sa
    option = GetInteger("Valasztott menupont: ");

    switch(option)
    {
        case 1:
            ManageMember("edit");
            break;
        case 2:
            ManageMember("write");
            break;
    }
}while(option != 0);


}

//ManageMember();
//ManageBook();
}


void Menu::WriteMenu(string type)const{
if (type=="main")
{
    cout << endl << endl;
	cout << "--- F�MENU ---" << endl;
	cout << "Valassz az alabbi opciok kozul!" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - K�nyvek kezel�se:" << endl;
	cout << "\t2 - Tagok kezel�se" << endl;
	cout << "\t3 - K�lcs�nz�s" << endl;
	cout << "\t4 - Visszav�tel" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t0 - Ment�s �s kil�p�s" << endl;
}
if(type=="book")
{
    cout << endl << endl;
	cout << "K�nyvek kezel�se:" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - K�nyvek list�z�sa" << endl;
	cout << "\t2 - �j k�nyv felv�tele" << endl;
	cout << "\t3 - K�nyv t�rl�se" << endl;
	cout << "\t4 - K�nyv keres�se" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza a f�men�be" << endl;
}
if (type == "member")
{
    cout << endl << endl;
	cout << "Tagok kezel�se" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Tagok list�z�sa" << endl;
	cout << "\t2 - Tag felv�tele" << endl;
	cout << "\t3 - Tag t�rl�se" << endl;
	cout << "\t4 - Tag adatainak list�z�sa, szerkeszt�se" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza a f�men�be" << endl;
}
if (type == "det"){
    cout << endl << endl;
	cout << "Tag adatainak kezel�se" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Tag adatainak lek�rdez�se" << endl;
	cout << "\t2 - Tag szerkeszt�se" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza" << endl;


}

}

int Menu::GetInteger(const string& msg) const
{
	int number;
	bool error;
	do
	{
		cout << msg;
		cin >> number;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "A megadott �rtek nem eg�sz sz�m!" << endl;
			error = true;
        }
		else
            error = false;
    }
    while(error);
	return number;
}

string Menu::prot(string &str){ //user input jav�t�sa ;->"," cser�l�s�vel
unsigned tal;

string mit (";");
string mire (",");
tal = str.find( mit );
  while (tal!=string::npos){
    str.replace( tal, mit.size(), mire );
    tal = str.find( mit );
  };
return str;
}

/**
 * k�nyvek m�dos�t�sa, param�terk�nt, hogy milyen muveletet v�gezz�nk.
 */
void Menu::ManageBook(string type){ //kesz (TODO k�lcs�nz�s frissiteni!)
if (_books.size()>0){
if (type=="list"){ //k�nyek list�z�sa
//    cout << "K�NYVEK"<< endl;
    cout << endl;
    _books[0]->list_f();
    for(unsigned int i=0;i<_books.size();++i){_books[i]->list();}
    Space(140, "-");
    cout<< endl;
}

if(type=="delete"){


    char vsz;
    cout << endl << "-- K�nyv t�rl�se --" << endl;
    ManageBook("list");
Clear();

    cout << "V�lasszon k�nyvet a t�rl�shez! Ehhez adja meg a k�nyvhez tartoz� ID-t!" << endl;
    //_id = GetInteger("A v�lasztott ID: ");
    int i;

    if(BookId(i)){
        _books[i]->list_f(); _books[i]->list();
        //a k�nyv kintl�v�s�g�nek ellen�rz�se!
        if(!_books[i]->GetSzabad()){
            cout << endl << endl << "A k�nyv k�lcs�n�zve van, a t�rl�s el�tt vissza kell venni! Megteszi ezt most? (i - igen, minden m�s - nem)" << endl;
            cin >> vsz;
            if(tolower(vsz)=='i'){
                try{

                Return(_books[i]->GetKi()); //finomitas a return muvelet alapj�n
                }catch(Members::Exception ex){cout << "A visszav�tel nem siker�lt, a t�rl�s nem folytathat�!" << endl;}
            }else{cout << "A visszav�tel megszak�tva, a t�rl�s nem folytathat�!" << endl;}
        }
        if(_books[i]->GetSzabad()){ //az�rt nem else, mert k�zbe visszavihett�k a k�nyvet! ha k�zben felszabadult, akkor folytatjuk
        cout << "Biztos t�rli ezt a k�nyvet? (i - igen, minden m�s - nem)" << endl;
        cin >> vsz;
        if (tolower(vsz)!='i'){cout << "A m�velet visszavonva!" << endl;}
        else {

            delete _books[i];
            _books.erase(_books.begin()+i);
            cout << "A k�nyv t�r�lve!" << endl;}
        }
    }else{cout << "Hiba! Nincs ilyen ID, a t�rl�s nem lehets�ges!" << endl;}


}

}else{cout << "Nincs egy k�nyv se az adatb�zisban, ez�rt nem hajthat� v�gre m�velet!" << endl;}
if (type=="new") //�j k�nyv hozz�ad�sa
{
    cout << endl <<  "-- �j k�nyv felv�tele --" << endl;
    string szerz, cim, kiado, isbn;
    char vsz;
    int kiadas, ev;
Clear();
    cout << "Adja meg a k�nyv adatait! (ebben a verzi�ban az �kezetes bet�k nem t�mogatottak!)" << endl; //TODO �kezetes beolvas�s!

    cout << "Szerz�: "; getline(cin, szerz);
    cout  << "A k�nyv c�me: "; getline(cin, cim);
    cout  << "A kiad� neve: "; getline(cin , kiado) ;
    ev = GetInteger("A kiad�s d�tuma: ");
    kiadas = GetInteger("H�nyadik kiad�s? ");
    Clear();
    cout  << "A k�nyv ISBN sz�ma: "; getline(cin , isbn) ; //TODO min hossz ISBN. sz�mnak
    Books* tmp = new Books(prot(szerz), prot(cim), prot(kiado), ev, kiadas, isbn); //prot lecser�li a ;-ket , re f�jlhiba elker�l�se �rdek�ben
    cout << endl;
    tmp->list_f();
    (tmp)->list();
    cout << endl;
    cout << "Helyesek az adatok, l�trehozza a k�nyet? (i - igen, minden m�s - nem) ";
    cin >> vsz;
    if (vsz!='i'){cout << "A m�velet visszavonva!" << endl;delete tmp;}
    else {_books.push_back(tmp);cout << "A k�nyv l�trehozva!" << endl;}
}

}


/**
 * k�nyvek keres�se
 */
void Menu::SearchBook(){
cout << endl << "-- K�ny keres�se --" << endl;
cout << "Mi alapj�n keresel? (1 - Szerz�, 2 - C�m, 3 - ISBN, 4 - azonos�t�)" << endl;
int vsz, db;
Clear();
vsz = GetInteger("Keres�s alapja: ");
string mit;
Clear();
cout << "�rd be a keresend� sz�veget! " << endl;
cin >> mit;
if(_books.size()>0){
_books[0]->list_f();
db = 0;
for(int i = 0;i<_books.size();++i)
{
   if (_books[i]->Search(vsz,mit)) {_books[i]->list();db++;};
}
if (db==0) {cout << "FIGYELEM! Nincs tal�lat!" << endl;}
}else {cout << "Nincs egy k�nyv se!" << endl;}//nincs k�nyv

}
void Menu::Clear()const{
    cin.clear(); //cin tisztitasa, hogy rendesen m�k�dj�n a beolvasas (getline �s >> kever�se miatt van r� sz�ks�g)
    cin.sync();
}

bool Menu::MemberId(int& i){
Clear();
_id = 0;
_id = GetInteger("A v�lasztott ID: ");
i = 0;
for(i=0;i<_members.size();++i){if (_id==(_members[i])->GetId()){break;}}
return i<_members.size();
}

bool Menu::BookId(int& i, bool in){
if(in){ //ha a felhaszn�l�t�l kell bek�rni az adatot
Clear();
_id = 0;
_id = GetInteger("A v�lasztott ID: ");
}else {_id = i;} //ha param�terk�nt adott id-t keres�nk (f�jlbeolvas�s)
i = 0;
for(i=0;i<_books.size();++i){if (_id==(_books[i])->GetId()){break;}}
return i<_books.size();
}
/**
 * tagok kezel�se, param�terk�nt a muvelet t�pusa
 */
void Menu::ManageMember(string type){
if(_members.size()!=0) //ha van tag
{
if (type=="list"){ //tagok list�z�sa

    //fejl�c
    cout << endl;
    _members[0]->list_f();
    //az adott adatok ki�r�sa
    for(unsigned int i=0;i<_members.size();++i){_members[i]->list();}
    Space(160, "-");
    cout << endl;

} // list�z�s v�ge
if (type=="delete")
{
    char vsz;
    cout << "-- Tag t�rl�se --" << endl;
    ManageMember("list");


    cout << "V�lasszon tagot a t�rl�shez! Ehhez adja meg a taghoz tartozo ID-t!" << endl;
//    _id = GetInteger("A v�lasztott ID: ");
    int i;
//    for(i=0;i<_members.size();++i){if (_id==(_members[i])->GetId()){break;}}   //a felh. �ltal megadott id keres�se
    if(MemberId(i)){
        _members[i]->list_det(); //a t�rl�sre kijel�lt tag list�z�sa
        //a tag k�lcs�nz�seinek ellen�rz�se!
        if(!_members[i]->GetKolcsSize()==0){
            cout << endl << "A tagnak �l� k�lcs�nz�sei vannak, ezeket meg kell sz�ntetni, miel�tt t�r�ln�! Megteszi ezt most?" << endl << "i - igen, minden m�s - nem : "; //TODO ha a visszav�tl k�sz, ezt megoldani
            Clear();
            cin >> vsz;
            if(tolower(vsz)=='i') //ha a k�lcs�nz�tt k�nyveket vissza kell venni:
            {
                try{
                cout << "Kintl�v�s�gek visszav�tele folyamatban." << endl << endl;
                int meret = _members[i]->GetKolcsSize();
                for(int j=0;j<meret;++j){
                    _id = _members[i]->FirstKolcs()->GetId();
                    cout << _id << " ID-j� k�nyv visszav�tele...";

                    int keses = Return(_members[i]);
                    if (keses>0){cout <<endl << "FIGYELEM!"<< endl << keses << " nap k�s�ssel hozt�k vissza a k�nyvet!" << endl;}
                    cout << "A k�nyv visszav�ve!" << endl;
                    }
                    cout << endl << "Minden k�lcs�nz�tt k�nyv visszav�ve!" << endl;
                    }catch(Members::Exception ex){cout << "A visszav�tel nem siker�lt, a t�rl�s nem folytathat�!" << endl;}
            }else{cout << "Kintl�v�s�gek visszav�tele megszak�tva, a t�rl�s nem folytathat�!" << endl;} //ha nem vessz�k vissza a k�nyveket

        }//�l� k�lcs visszav�tel�nek v�ge
        if(_members[i]->GetKolcsSize()==0){ // ha  felszabad�tottuk a tagot, akkor folytatjuk (vagy nincs k�lcs�nz�se)
        cout << "Biztos t�rli ezt a tagot? (i - igen, minden m�s - nem)" << endl;
        cin >> vsz;
        if (tolower(vsz)!='i'){cout << "A m�velet visszavonva!" << endl;}
        else {

            delete _members[i];
            _members.erase(_members.begin()+i);
            cout << "A tag t�r�lve!" << endl;}
        }
    }else{cout << "Hiba! Nincs ilyen ID, a t�rl�s nem lehets�ges!" << endl;}

} //t�rl�s v�ge
if(type=="edit"){ //r�szletes list�z�s
    cout << endl << "-- V�lasztott tag adatainak list�z�sa --" << endl;

    ManageMember("list"); //�sszes tag list�z�sa, hogy l�ssuk, mib�l lehet v�lasztani
    cout << "K�rem v�lasszon egy tagot, akinek tov�bbi adataira k�v�ncsi! Az ID-j�t adja meg!" << endl;
    Clear();
    int i;

    if(MemberId(i)){
    _members[i]->list_det();
    _id = i; //elt�roljuk a priv�t tagban, hogy hanyadik elemet vizsg�ltuk
    }else{cout << "Hiba! Nincs ilyen ID, a list�z�s nem lehets�ges!" << endl;}
}
if(type=="write"){
    if(!(_id<_members.size())){cout << "K�rlek v�lassz egy ID-t!" << endl;ManageMember("edit");}else{ //helyes ID v�laszt�s kik�nyszer�t�se
    int vsz = 0;
    char v;
    string mod, nev, cim, eler;
    nev = _members[_id]->GetNev();
    cim = _members[_id]->GetCim();
    eler = _members[_id]->GetEler();
    Clear();
    cout << endl << "-- V�lasztott tag adatainak szerkeszt�se --" << endl;
    _members[_id]->list_det();
    cout << "Melyik adattagot m�dos�tja? 1 - N�v, 2 - Lakc�m, 3 - El�rhet�s�g, 4 - T�pus" << endl;
    vsz = GetInteger("A v�lasztott adattag: ");
    Clear();
    switch(vsz){
    case 1:

        cout << "Mi legyen a tag �j neve? ";
        getline(cin, mod);
        Clear();
        cout << "R�gz�ti a m�dos�t�st? (" << nev << "->" << mod << ") i - igen, minden m�s - nem" << endl;
        cin >> v;
        Clear();

        break;
    case 2:
        cout << "Mi legyen a tag �j lakc�me? ";
        getline(cin, mod);
        Clear();
        cout << "R�gz�ti a m�dos�t�st? (" << cim<< "->" << mod << ") i - igen, minden m�s - nem" << endl;
        cin >>v;
        Clear();
        break;
    case 3:
        cout << "Mi legyen a tag �j el�rhet�s�ge? ";
        getline(cin, mod);
        Clear();
        cout << "R�gz�ti a m�dos�t�st? (" <<eler << "->" << mod << ") i - igen, minden m�s - nem" << endl;
        cin >>v;
        Clear();
        break;
    case 4:
        cout << "Mi legyen a tag �j t�pusa?" << endl << "(1 - Egyetemi Hallgato, 2 - Egyetemi Oktato, 3 - Egy�b Egyetemhez tartozo szem�ly, minden m�s - Mindenki m�s)" << endl;
        getline(cin, mod);
        Clear();
        cout << "R�gz�ti a m�dos�t�st? i - igen, minden m�s - nem" << endl;
        cin >> v;
        Clear();
        break;
    }
if(vsz>=1 && vsz<=4 && tolower(v)=='i'){ //ha �rv�seset v�lasztott, �s elfogadta a v�ltoz�sokat
    if(vsz!=4){
    _members[_id]->Edit(vsz, mod);
    cout << "A m�dos�t�s siker�lt!" << endl;
    }
    else{ //ha tipust kell v�ltoztatni: �j p�ld�ny, a r�git r�ir�n�tjuk, �s a m�g�ttes adat�t t�r�lj�k
        if(_members[_id]->GetKolcsSize()==0){
        Members* tmp;
        int tp = atoi(mod.c_str());
        if (tp == 1){ tmp = new Student(nev, cim, eler);} //hallgato
        else if (tp == 2){ tmp = new Prof(nev, cim, eler);} // tan�r
        else if (tp == 3){ tmp = new Citizen(nev, cim, eler);} //egy�b egyetem
        else{ tmp = new Others(nev, cim, eler);} //mindenki m�s
        if(!tmp->Kolcs()){cout << "Figyelem! A tagnak t�bb k�nyve van, mint az �j t�pusa engedn�!" << endl << "Addig nem lehets�ges a k�lcs�nz�s, am�g nem cs�kken a megengedett al� ez a sz�m! (" << tmp->MaxKolcs() << " db)" << endl;}
        _members.erase(_members.begin()+_id);
        _members[_id] = tmp;
        cout << "A m�dos�t�s siker�lt!" << endl;
        }else{cout << endl << "A tagnak �l� k�lcs�nz�sei vannak! A t�pusm�dos�t�s csak akkor t�mogatott, ha nincsenek k�lcs�nz�sek!" << endl;}
    }

}else{cout << endl << "Nem t�rt�nt m�dos�t�s!" << endl;}
_members[_id]->list_det();
    }//l�tez� id v�ge
} // m�doss�t�s v�ge
}else {cout << "Nincs egy tag sem az adatb�zisban, k�rlek vegy�l fel p�rat!" << endl;} //ha nincs tag

if (type=="new") //�j k�nyv hozz�ad�sa
{
    cout <<endl << "-- �j tag felv�tele --" << endl;
    string nev, cim, eler;
    char vsz;
    int tp;
    cin.clear();
    cin.sync();
    cout << "Adja meg az �j tag adatait! (ebben a verzi�ban az �kezetes bet�k nem t�mogatottak!)" << endl; //TODO �kezetes beolvas�s!

//t.push_back(new Citizen("Egyetemi Polg�r", "ELTE", "elte@inf.com"));

    cout << "N�v: "; getline(cin, nev);
    cout  << "Lakc�m: "; getline(cin, cim);
    cout  << "El�rhetos�g (email/telefon): "; getline(cin , eler) ;
    cout << "Adja meg, milyen t�pusu a tag! (1 - Egyetemi Hallgato, 2 - Egyetemi Oktato, 3 - Egy�b Egyetemhez tartozo szem�ly, 4 - Mindenki m�s)" << endl;
    cout << "Ha nem megfelelo sz�mot ad meg, 4-es t�pus fog �rv�nyes�lni!"<< endl;
    tp = GetInteger("A v�lasztott t�pus: ");
    Members* tmp;
    prot(nev);prot(cim);prot(eler); //szab�lytalan karakter (;) kiz�r�sa
    if (tp == 1){ tmp = new Student(nev, cim, eler);} //hallgato
    else if (tp == 2){ tmp = new Prof(nev, cim, eler);} // tan�r
    else if (tp == 3){ tmp = new Citizen(nev, cim, eler);} //egy�b egyetem
    else{ tmp = new Others(nev, cim, eler);} //mindenki m�s
    //Books* tmp = new Books(prot(szerz), prot(cim), prot(kiado), ev, kiadas, isbn); //prot lecser�li a ;-ket , re f�jlhiba elker�l�se �rdek�ben
    cout << endl;
    tmp->list_f();
    (tmp)->list();
    cout << endl;
    cout << "Helyesek az adatok, felveszi a tagot? (i - igen, minden m�s - nem) ";
    cin >> vsz;
    if (tolower(vsz)!='i'){cout << "A m�velet visszavonva!" << endl;delete tmp;}
    else {_members.push_back(tmp);cout << "A tag felv�ve!" << endl;}
}//�j tag v�ge

}


/**
 * k�lcs�nz�s
 */
void Menu::Loan(){
cout << endl << "-- K�nyv k�lcs�nz�se --" << endl;
int i = 0;
int j = 0; //j - tagazonosito, i - k�nyvazon
char biztos;
_id = -1;
cout << "K�rlek v�laszd a tagot, aki k�lcs�n�zni akar! Az ID-j�t add meg!" << endl;
ManageMember("list");
if(MemberId(j)){ //ha val�s tag

cout << "K�rlek v�laszd ki a k�lcs�nzend� k�nyvet! Az ID-j�t add meg!" << endl;
ManageBook("list");

if(BookId(i)){ //val�s ID-t adott meg
    if (_books[i]->GetSzabad()){ //ha szabad a k�nyv
        //tag adatainak list�z�sa, meger�sit�s k�r�se a k�lcs�nz�sre
        cout << "K�lcs�nz� tag adatai: " << endl;
        _members[j]->list_det();
        cout << endl << "A k�lcs�nzend� k�nyv adatai: "<< endl << endl;
        _books[i]->list_f();
        _books[i]->list();
        if(!_members[j]->Kolcs()){cout << endl << endl << "HIBA! A tag el�rte a maxim�lis k�lcs�n�zhet� mennyis�get, a k�lcs�nz�s nem lehets�ges!" << endl;} //ha nem k�lcs�n�zhet m�r
        else{
        cout << endl << "R�gz�ti a k�lcs�nz�st? (i - igen, minden m�s  - nem)" << endl;
        Clear();
        cin >> biztos;
        if (tolower(biztos)!='i'){cout << "A k�lcs�nz�s visszavonva!" << endl;}
        else{   //ha meger�s�tett a k�lcs�nz�s, megpr�b�ljuk v�grehajtani

        MyDate* ma = new MyDate();
        string dat = ma->getDate();
        if(!(_members[j]->Loan(_books[i], dat))){cout << "Sikertelen k�lcs�nz�s, a tag nem k�lcs�n�zhet t�bb k�nyvet!";} //ha nem siker�lt a k�lcs�nz�s, t�ll�pte a keretet.
        else{
            cout << "Sikeres k�lcs�nz�s" << endl;
            ManageBook("list");}
        }//k�lcs�nz�s v�ge
        } //lehets�ges k�lcs�nz�s v�ge
    }else {cout << "Hiba! A k�nyv m�r k�lcs�n�zve van! Pr�b�ljon m�sik k�nyvet k�lcs�n�zni!" << endl;}

}//book Id check v�ge
else{cout << "Hiba! Nincs ilyen K�nyv-ID, a k�lcs�nz�s nem lehets�ges!" << endl;}
}//member ID check v�ge
else{cout << "Hiba! Nincs ilyen Tag-ID, a k�lcs�nz�s nem lehets�ges!" << endl;}
}

/**
 * visszahozatal
 * visszat�r�si �rt�k hogy t�rt�nt-e k�s�s
 */
void Menu::Return(){
cout << endl << "-- K�nyv visszav�tele --" << endl;
int i = 0; // i - k�nyvazon
_id = -1; //
char biztos; //meger�s�t�s t�rol�sa
cout << "K�rlek v�laszd a k�nyvet, amit visszahoztak! Az ID-j�t add meg!" << endl;
ManageBook("list");
if(BookId(i)){ //ha val�s k�nyv
    int keses;
    cout << "R�szletes adatok a k�lcs�nz�r�l: " << endl;
    _books[i]->GetKi()->list_det();
    cout << "R�gz�ti a visszav�telt? (i - igen, minden m�s  - nem)" << endl;
    Clear();
    cin >> biztos;
    if (tolower(biztos)!='i'){cout << "A m�velet visszavonva! Nem t�rt�nt visszav�tel." << endl;}
    else{
    try{
    keses = Return(_books[i]->GetKi());
    if (keses>0){cout <<endl << "FIGYELEM!"<< endl << keses << " nap k�s�ssel hozt�k vissza a k�nyvet!" << endl;}
    cout << "A visszav�tel siker�lt." << endl;

    }catch(Members::Exception ex){cout << "A visszav�tel nem siker�lt, a k�nyv nem tal�lhat�!" << endl;}

    }//visszav�tel v�ge

}//member ID check v�ge
else{cout << "Hiba! Nincs ilyen K�nyv-ID, a visszav�tel nem lehets�ges!" << endl;}
}

int Menu::Return(Members* mit){
int mennyi;
mennyi = (mit->Return(_id));
return mennyi;
}


bool Menu::Login(){
try{
cout << "K�rem jelentkezzen be!" << endl;
bool ok;
Admin p; //MISSING_FILE,BAD_INPUT kiv�telek keletkezhetnek, ha a pass.dat hib�s!
//ok = p.Login();
ok = true;
return ok;
}catch(Admin::Exception ex){throw BAD_AUTHFILE;}
}

/*Books* Menu::idToPoint(int id){
//cout << "\n\n--ITERATOROK--\n\n";
bool talal = false;
vector<Books*>::iterator it;
for(it=_books.begin();it!=_books.end();++it)
{
    if ((*it)->GetId()==id){ talal = true; break;}
}
Books *p = 0;
if(talal){p=*it;}
return p;
}*/



void Menu::LoadData(){
    ifstream f; //a konyveket tartalmazo fajl
    //konyvek beolvasasa
    {
    string szer, cim, kia, id, ev, kiadas, isbn, tmp; //ideiglenes adatokat tartalmazo valtozok
    f.open("konyv.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
        while(f.good()) //fajlbeolvasas
        {
//            f>>id;
            getline(f, id, ';' ); //id
            getline(f, szer, ';' ); //szerzo beolvasasa
            getline(f, cim, ';' ); //cim
            getline(f, kia, ';' ); //kiado
            getline(f, ev, ';' ); //kiadas eve
            getline(f, kiadas, ';' ); //hanyadik kiadas
            getline(f, isbn, '\n' ); //isbn
            if (id!=""){
            _books.push_back(new Books(atoi(id.c_str()), szer, cim, kia, atoi(ev.c_str()), atoi(kiadas.c_str()), isbn));
            }

        }


        f.close();
    }
    else throw MISSING_FILE;  //ha nem siker�lt a f�jlt megnyitni kiv�tel dob�sa*/
    }
    //tagok bet�lt�se
    {
    string tipus, nev, cim, eler, db_s, kolcs, date;
    int db, id, tp; //id=kolcsonzott konyv id-je, db az osszes kolcsonzes db-szama
    f.open("tagok.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
        while(f.good()) //fajlbeolvasas
        {
        stringstream sor;
        string tmp_sor;
        getline(f,tmp_sor);
        sor << tmp_sor;
//            f>>id;
            getline(sor, tipus, ';' ); //tipus
            getline(sor, nev, ';' ); //nev
            getline(sor, cim, ';' ); //cim
            getline(sor, eler, ';' ); //elerhetoseg
            getline(sor, db_s, ';' ); //kolcsonzesek szama
        if (tipus!=""){ //ha v�letlen nem egy �res sor lenne
            tp = atoi(tipus.c_str());
            Members* tmp;
            if (tp == 1){ tmp = new Student(nev, cim, eler);}
            else if (tp == 2){ tmp = new Prof(nev, cim, eler);}
            else if (tp == 3){ tmp = new Citizen(nev, cim, eler);}
            else{ tmp = new Others(nev, cim, eler);}


            //Others *tmp = new Others(nev, cim, eler);
            db = atoi(db_s.c_str());
            for(int i=1;i<=db;i++)
            {
                getline(sor, kolcs, ';' ); //adott kolcsonzes
                getline(sor, date, ';' ); //adott kolcsonzes datuma

                id = atoi(kolcs.c_str());
                //Books* p= idToPoint(id);

                if (!BookId(id, false)){throw BAD_INPUT;} //ha nincs olyan konyv, kivetel dobasa
                if (!tmp->Loan_L(_books[id], date)){throw BAD_INPUT;}
            }

            _members.push_back(tmp);
            }

        }

        f.close();
    }
    else throw MISSING_FILE;  //ha nem siker�lt a f�jlt megnyitni kiv�tel dob�sa
    }
}

void Menu::SaveData(){
    ofstream f; //a konyveket tartalmazo fajl
    //k�nyvek kiment�se
    f.open("konyv.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
	for(unsigned int i=0;i<_books.size();i++){f<<(_books[i]);}
	f.close();
    }
    else throw MISSING_FILE;  //ha nem kiv�tel dob�sa*/

    //tagok kimentese
    f.open("tagok.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
	for(unsigned int i=0;i<_members.size();i++){
    f<<(_members[i]);
    if(i+1<_members.size()){f<<endl;}
    }

	f.close();
    }
    else throw MISSING_FILE;  //ha nem kiv�tel dob�sa*/
}

