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
if(Login()){
LoadData();
cout << "Az adatok bet�lt�se sikeres!" << endl;
}
else throw Menu::AUTH_FALIURE;
}

Menu::~Menu(){
SaveData();
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
	cout << "--- F�MENU ---" << endl;
	cout << "Valassz az alabbi opciok kozul!" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - K�nyvek kezel�se:" << endl;
	cout << "\t2 - Tagok kezel�se" << endl;
	cout << "\t3 - K�lcs�nz�s" << endl;
	cout << "\t4 - Visszav�tel" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t0 - Kilepes" << endl;
}
if(type=="book")
{
//    cout << "\t-----------------" << endl;
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
//    cout << "\t-----------------" << endl;
	cout << "Tagok kezel�se" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Tagok list�z�sa" << endl;
	cout << "\t2 - Tag felv�tele" << endl;
	cout << "\t3 - Tag t�rl�se" << endl;
	cout << "\t4 - Tag adatainak list�z�sa, szerkeszt�se" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza a f�men�be" << endl;
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
void Menu::ManageBook(string type){
if (type=="list"){ //k�nyek list�z�sa
//    cout << "K�NYVEK"<< endl;
    cout<< "ID\t" <<  "SZERZO\t\t" <<  "C�M\t\t\t" <<  "KIAD�\t\t" <<  "�VSZ�M\t" << "KIAD�S\t\t" <<  "ISBN\t\t"<< "K�LCS�N�ZHET�\t" <<  endl;
    Space(130, "-");
    cout << endl;
    for(unsigned int i=0;i<_books.size();++i){_books[i]->list();}
    Space(130, "-");
    cout<< endl;
}
if (type=="new") //�j k�nyv hozz�ad�sa
{
    cout << "-- �j k�nyv felv�tele --" << endl;
    string szerz, cim, kiado;
    char vsz;
    int kiadas, ev, isbn;
    cin.clear();
    cin.sync();
    cout << "Adja meg a k�nyv adatai! (ebben a verzi�ban az �kezetes bet�k nem t�mogatottak!)" << endl; //TODO �kezetes beolvas�s!

    cout << "Szerz�: "; getline(cin, szerz);
    cout << endl << "A k�nyv c�me: "; getline(cin, cim);
    cout << endl << "A kiad� neve: "; getline(cin , kiado) ;
    cout << endl; ev = GetInteger("A kiad�s d�tuma: ");
    cout << endl; kiadas = GetInteger("H�nyadik kiad�s? ");
    cout << endl; isbn = GetInteger("A k�nyv ISBN sz�ma: ");
    Books* tmp = new Books(prot(szerz), prot(cim), prot(kiado), ev, kiadas, isbn); //prot lecser�li a ;-ket , re f�jlhiba elker�l�se �rdek�ben
    cout << endl;
    (tmp)->list();
    cout << endl;
    cout << "Helyesek az adatok, l�trehozza a k�nyet? (i - igen) ";
    cin >> vsz;
    if (vsz!='i'){cout << "A m�velet visszavonva!" << endl;delete tmp;}
    else {_books.push_back(tmp);cout << "A k�nyv l�trehozva!" << endl;}


    //k.push_back(new Books("Nagy G�bor", "C++ haladoknak", "Petofi", 2012, 3, 123445));
}


}


/**
 * k�nyvek keres�se
 */
void Menu::SearchBook(){

}


/**
 * tagok kezel�se, param�terk�nt a muvelet t�pusa
 */
void Menu::ManageMember(string type){
if (type=="list"){ //tagok list�z�sa
//form�z�s, fejl�c ki�r�sa
cout << "ID\t" <<  "N�V";
Space(27, " ");
cout <<  "LAKC�M";
Space(24, " ");
cout << "EL�RHET�S�G";
Space(19, " ");
cout  << "TAGT�PUS" << endl;
Space(120, "-");
cout << endl;
//az adott adatok ki�r�sa
for(unsigned int i=0;i<_members.size();++i){_members[i]->list();}
Space(120, "-");
cout << endl;
}




}


/**
 * k�lcs�nz�s
 */
void Menu::Loan(){

}


/**
 * visszahozatal
 * visszat�r�si �rt�k hogy t�rt�nt-e k�s�s
 */
bool Menu::Return(){

	return false;
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
    else throw MISSING_FILE;  //ha nem siker�lt a f�jlt megnyitni kiv�tel dob�sa
    }
}

void Menu::SaveData(){
    ofstream f; //a konyveket tartalmazo fajl
    //k�nyvek kiment�se
    f.open("konyv.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
	for(unsigned int i=0;i<_books.size();i++){f<<(*_books[i]);}
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

