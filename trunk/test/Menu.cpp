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
if(Login()){
LoadData();
cout << "Az adatok betöltése sikeres!" << endl;
}
else throw Menu::AUTH_FALIURE;
}

Menu::~Menu(){
SaveData();
}




void Menu::Run(){
int option = 0;
do
{
    WriteMenu(); //főmenü kiírása
    option = GetInteger("Valasztott menupont: ");

    switch(option)
    {
        case 1:
            testAppend();
            break;
        case 2:
            testPrepend();
            break;
        case 3:
            testPop();
            break;
        case 4:
            testMax();
            break;
        case 5:
            testPrint();
            break;
    }
}
while(option != 0);
ManageMember();
ManageBook();
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
	for(unsigned int i=0;i<_books.size();i++){f<<(*_books[i]);}
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



void Menu::WriteMenu(string type){
if (type=="main")
{
    cout << endl << endl;
	cout << "--- FÖMENU ---" << endl;
	cout << "Valassz az alabbi opciok kozul!" << endl;
	cout << "\t1 - Elem hozzafuzese a lancolt lista vegere" << endl;
	cout << "\t2 - Elem hozzafuzese a lancolt lista elejere" << endl;
	cout << "\t3 - Elem kivetele a lancolt lista elejerol" << endl;
	cout << "\t4 - Maximalis ertek megkeresese" << endl;
	cout << "\t5 - Lancolt lista kiirasa" << endl;
	cout << "\t0 - Kilepes" << endl;
}
}


/**
 * könyvek módosítása, paraméterként, hogy milyen muveletet végezzünk.
 */
void Menu::ManageBook(string type){
if (type=="list"){
    cout << "KONYVEK"<< endl;
    for(unsigned int i=0;i<_books.size();++i){_books[i]->list();}
    cout<< endl;
}
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
if (type=="list"){

	cout << "Tagok: " <<endl;
    for(unsigned int i=0;i<_members.size();++i){_members[i]->list();}

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

