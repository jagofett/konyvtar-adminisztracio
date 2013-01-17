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



Menu::Menu(){
if(Login()){
LoadData();
}
else throw Menu::AUTH_FALIURE;
}

Menu::~Menu(){
SaveData();
}




void Menu::Run(){
ManageMember();
ManageBook();
}


void Menu::LoadData(){
    std::ifstream f; //a konyveket tartalmazo fajl
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
    std::ofstream f; //a konyveket tartalmazo fajl
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
    if(i+1<_members.size()){f<<std::endl;}
    }

	f.close();
    }
    else throw MISSING_FILE;  //ha nem kiv�tel dob�sa*/
}



void Menu::WriteMenu(string type){

}


/**
 * k�nyvek m�dos�t�sa, param�terk�nt, hogy milyen m�veletet v�gezz�nk.
 */
void Menu::ManageBook(std::string type){
if (type=="list"){
    cout << "KONYVEK"<< endl;
    for(unsigned int i=0;i<_books.size();++i){_books[i]->list();}
    cout<< endl;
}
}


/**
 * k�nyvek keres�se
 */
void Menu::SearchBook(){

}


/**
 * tagok kezel�se, param�terk�nt a m�velet t�pusa
 */
void Menu::ManageMember(std::string type){
if (type=="list"){

	cout << "Tagok: " <<endl;
    for(unsigned int i=0;i<_members.size();++i){_members[i]->list();}

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
bool ok;
Admin p; //MISSING_FILE,BAD_INPUT kiv�telek keletkezhetnek, ha az pass.dat hib�s!
ok = p.Login();
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

