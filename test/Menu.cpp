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
cout << endl << "----Szoftvertechnologia haladó csoport beadando feladat----" << endl << endl;
cout << "Név:\t\tMagasvári Ákos" << endl << "ETR-kód:\tMAATACI.ELTE" << endl << "Neptun-kód:\tEGB6EB" << endl << "2012-2013-1, 4-es csoport" << endl;
cout << "Feladat összefoglalva:" << endl << "Készítsünk egy egyetemi könyvtár kölcsönzéseit nyilvántartó rendszert." << endl;
cout << "A rendszer feladata a könyvtár tagjainak, könyveinek," << endl <<"illetve  könyvtárosainak nyilvántartása." << endl << endl << "-----------------------------------------------------------------" << endl << endl;
cout << "Üdvözlöm a Könyvtári Adminisztrációs Rendszerben!" << endl;
if(!Login()){
throw Menu::AUTH_FALIURE;
}
}
Menu::~Menu(){
SaveData();
}




void Menu::Run(string type){

int option = 0;
if (type=="main"){
LoadData();
cout << "Az adatok betöltése sikeres!" << endl;
do
{
    WriteMenu(); //fömenü kiírása
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
    WriteMenu("book"); //könyvek kiírása
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
/*        case 5:
            //testPrint();
            break;*/
    }
}while(option != 0);
}
if (type=="member")
{
do
{
    WriteMenu("member"); //könyvek kiírása
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
            break;
/*        case 5:
            //testPrint();
            break;*/
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
	cout << "--- FÖMENU ---" << endl;
	cout << "Valassz az alabbi opciok kozul!" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Könyvek kezelése:" << endl;
	cout << "\t2 - Tagok kezelése" << endl;
	cout << "\t3 - Kölcsönzés" << endl;
	cout << "\t4 - Visszavétel" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t0 - Kilepes" << endl;
}
if(type=="book")
{
//    cout << "\t-----------------" << endl;
	cout << "Könyvek kezelése:" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Könyvek listázása" << endl;
	cout << "\t2 - Új könyv felvétele" << endl;
	cout << "\t3 - Könyv törlése" << endl;
	cout << "\t4 - Könyv keresése" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza a fömenübe" << endl;
}
if (type == "member")
{
//    cout << "\t-----------------" << endl;
	cout << "Tagok kezelése" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Tagok listázása" << endl;
	cout << "\t2 - Tag felvétele" << endl;
	cout << "\t3 - Tag törlése" << endl;
	cout << "\t4 - Tag adatainak listázása, szerkesztése" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza a fömenübe" << endl;
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
			cout << "A megadott értek nem egész szám!" << endl;
			error = true;
        }
		else
            error = false;
    }
    while(error);
	return number;
}

string Menu::prot(string &str){ //user input javítása ;->"," cserélésével
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
 * könyvek módosítása, paraméterként, hogy milyen muveletet végezzünk.
 */
void Menu::ManageBook(string type){
if (_books.size()>0){
if (type=="list"){ //könyek listázása
//    cout << "KÖNYVEK"<< endl;

    _books[0]->list_f();
    for(unsigned int i=0;i<_books.size();++i){_books[i]->list();}
    Space(130, "-");
    cout<< endl;
}

if (type=="new") //új könyv hozzáadása
{
    cout << "-- Új könyv felvétele --" << endl;
    string szerz, cim, kiado;
    char vsz;
    int kiadas, ev, isbn;
    cin.clear(); //cin tisztitasa, hogy rendesen müködjön a beolvasas (getline és >> keverése miatt van rá szükség)
    cin.sync();
    cout << "Adja meg a könyv adatait! (ebben a verzióban az ékezetes betük nem támogatottak!)" << endl; //TODO ékezetes beolvasás!

    cout << "Szerzö: "; getline(cin, szerz);
    cout  << "A könyv címe: "; getline(cin, cim);
    cout  << "A kiadó neve: "; getline(cin , kiado) ;
    ev = GetInteger("A kiadás dátuma: ");
    kiadas = GetInteger("Hányadik kiadás? ");
    isbn = GetInteger("A könyv ISBN száma: "); //TODO min hossz ISBN. számnak
    Books* tmp = new Books(prot(szerz), prot(cim), prot(kiado), ev, kiadas, isbn); //prot lecseréli a ;-ket , re fájlhiba elkerülése érdekében
    cout << endl;
    tmp->list_f();
    (tmp)->list();
    cout << endl;
    cout << "Helyesek az adatok, létrehozza a könyet? (i - igen, minden más - nem) ";
    cin >> vsz;
    if (vsz!='i'){cout << "A müvelet visszavonva!" << endl;delete tmp;}
    else {_books.push_back(tmp);cout << "A könyv létrehozva!" << endl;}
}
if(type=="delete"){
    int id;
    bool van = false;
    char vsz;
    cout << "-- Könyv törlése --" << endl;
    ManageBook("list");
    cin.clear(); //cin tisztitasa, hogy rendesen müködjön a beolvasas (getline és >> keverése miatt van rá szükség)
    cin.sync();

    cout << "Válasszon könyvet a törléshez! Ehhez adja meg a könyvhez tartozó ID-t!" << endl;
    id = GetInteger("A választott ID: ");
    int i=0;
    int ind;
    for(;i<_books.size();++i){
        if (id==(_books[i])->GetId()){van=true;break;}
       // cout << _books[i]->GetId() << "==" << id << " ";
//        ind = id;
//        ++i;
    }
    cout << endl << i << endl;
   // i = ind-1;
    if(i<_books.size()){
        _books[i]->list_f(); _books[i]->list();
        //a könyv kintlévöségének ellenörzése!
        if(!_books[i]->GetSzabad()){
            cout << "A könyv kölcsönözve van, a törlés elött vissza kell venni! Megteszi ezt most? (i - igen, minden más - nem)" << endl;
            cin >> vsz;
            if(tolower(vsz)=='i'){
                try{

                (_books[i]->GetKi())->Return(id); //finomitas a return muvelet alapján
                }catch(Members::Exception ex){cout << "A visszavétel nem sikerült, a törlés nem folytatható!" << endl;}
            }
        }
        if(_books[i]->GetSzabad()){ //azért nem else, mert közbe visszavihettük a könyvet! ha közben felszabadult, akkor folytatjuk
        cout << "Biztos törli ezt a könyvet? (i - igen, minden más - nem)" << endl;
        cin >> vsz;
        if (tolower(vsz)!='i'){cout << "A müvelet visszavonva!" << endl;}
        else {

            delete _books[i];
            _books.erase(_books.begin()+i);
            cout << "A könyv törölve!" << endl;}
        }
    }else{cout << "Hiba! Nincs ilyen ID, a törlés nem lehetséges!" << endl;}


}

}else{cout << "Nincs egy könyv se az adatbázisban, ezért nem hajtható végre müvelet!" << endl;}
}


/**
 * könyvek keresése
 */
void Menu::SearchBook(){

}


/**
 * tagok kezelése, paraméterként a muvelet típusa
 */
void Menu::ManageMember(string type){
if (type=="list"){ //tagok listázása
    if(_members.size()!=0) //ha van tag
    {
    //fejléc
    _members[0]->list_f();
    //az adott adatok kiírása
    for(unsigned int i=0;i<_members.size();++i){_members[i]->list();}
    Space(120, "-");
    cout << endl;
    }else {cout << "Nincs egy tag sem az adatbázisban, kérlek vegyél fel párat!" << endl;}
}
if (type=="new") //új könyv hozzáadása
{
    cout << "-- Új tag felvétele --" << endl;
    string nev, cim, eler;
    char vsz;
    int tp;
    cin.clear();
    cin.sync();
    cout << "Adja meg az új tag adatait! (ebben a verzióban az ékezetes betük nem támogatottak!)" << endl; //TODO ékezetes beolvasás!

//t.push_back(new Citizen("Egyetemi Polgár", "ELTE", "elte@inf.com"));

    cout << "Név: "; getline(cin, nev);
    cout  << "Lakcím: "; getline(cin, cim);
    cout  << "Elérhetoség (email/telefon): "; getline(cin , eler) ;
    cout << "Adja meg, milyen típusu a tag! (1 - Egyetemi Hallgato, 2 - Egyetemi Oktato, 3 - Egyéb Egyetemhez tartozo személy, 4 - Mindenki más" << endl;
    cout << "Ha nem megfelelo számot ad meg, 4-es típus fog érvényesülni!"<< endl;
    tp = GetInteger("A választott típus: ");
    Members* tmp;
    prot(nev);prot(cim);prot(eler); //szabálytalan karakter (;) kizárása
    if (tp == 1){ tmp = new Student(nev, cim, eler);} //hallgato
    else if (tp == 2){ tmp = new Prof(nev, cim, eler);} // tanár
    else if (tp == 3){ tmp = new Citizen(nev, cim, eler);} //egyéb egyetem
    else{ tmp = new Others(nev, cim, eler);} //mindenki más
    //Books* tmp = new Books(prot(szerz), prot(cim), prot(kiado), ev, kiadas, isbn); //prot lecseréli a ;-ket , re fájlhiba elkerülése érdekében
    cout << endl;
    tmp->list_f();
    (tmp)->list();
    cout << endl;
    cout << "Helyesek az adatok, felveszi a tagot? (i - igen, minden más - nem) ";
    cin >> vsz;
    if (tolower(vsz)!='i'){cout << "A müvelet visszavonva!" << endl;delete tmp;}
    else {_members.push_back(tmp);cout << "A tag felvéve!" << endl;}

}




}


/**
 * kölcsönzés
 */
void Menu::Loan(){

}


/**
 * visszahozatal
 * visszatérési érték hogy történt-e késés
 */
bool Menu::Return(){

	return false;
}


bool Menu::Login(){
try{
cout << "Kérem jelentkezzen be!" << endl;
bool ok;
Admin p; //MISSING_FILE,BAD_INPUT kivételek keletkezhetnek, ha a pass.dat hibás!
//ok = p.Login();
ok = true;
return ok;
}catch(Admin::Exception ex){throw BAD_AUTHFILE;}
}

Books* Menu::idToPoint(int id){
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
}



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
            _books.push_back(new Books(atoi(id.c_str()), szer, cim, kia, atoi(ev.c_str()), atoi(kiadas.c_str()), atoi(isbn.c_str())));
            }

        }


        f.close();
    }
    else throw MISSING_FILE;  //ha nem sikerült a fájlt megnyitni kivétel dobása*/
    }
    //tagok betöltése
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
                Books* p= idToPoint(id);
                if (p==0){throw BAD_INPUT;} //ha nincs olyan konyv, kivetel dobasa
                tmp->Loan_L(p, date);
            }
            if (nev!=""){
            _members.push_back(tmp);
            }

        }

        f.close();
    }
    else throw MISSING_FILE;  //ha nem sikerült a fájlt megnyitni kivétel dobása
    }
}

void Menu::SaveData(){
    ofstream f; //a konyveket tartalmazo fajl
    //könyvek kimentése
    f.open("konyv.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
	for(unsigned int i=0;i<_books.size();i++){f<<(_books[i]);}
	f.close();
    }
    else throw MISSING_FILE;  //ha nem kivétel dobása*/

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
    else throw MISSING_FILE;  //ha nem kivétel dobása*/
}

