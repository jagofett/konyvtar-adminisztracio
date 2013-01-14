///////////////////////////////////////////////////////////
//  Admin.cpp
//  Implementation of the Class Admin
//  Created on:      28-dec.-2012 19:42:13
//  Original author: Akos
///////////////////////////////////////////////////////////

#include "Admin.h"
#include <fstream>

Admin::Admin()
{
    std::ifstream f; //a bejelentkezesi adatokat tartalmazo fajl

    f.open("pass.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
        while(f.good()) //fajlbeolvasas
        {
            std::string tmp; //ideiglenes fájltárolo
            getline(f, tmp, ';' ); //nev beolvasasa
            if(f.eof()) throw BAD_INPUT; //ha valahol hianyzik egy nev, kivetel dobasa
            nev.push_back(tmp);
            if(f.eof()) throw BAD_INPUT;
            getline(f, tmp, ';' );
            jelszo.push_back(tmp);

        }


        f.close();

    }
    else throw MISSING_FILE;  //ha nem kivétel dobása
}


bool Admin::Login(std::string name, std::string pass)
{
bool ok = false;
for (int i=0;i<nev.size();++i)
{
    if (name == nev[i] && pass == jelszo[i])
    {
        ok = true;
        break;
    }

}
    return ok;
}

bool Admin::Login()
{
    std::string name, pass;
    bool ok = false;
    int i = 0;
    do{
    if (ok == false && i != 0)
    {
    std::cout << "Hibas felhasznalo nev vagy jelszo. Probalja ujra! Meg " << 3-i << " lehetosege van" << std::endl;
    }
    std::cout << "Adja meg felhasznaloi nevet: ";
    getline(std::cin, name);

    std::cout << "Adja meg jelszavat: ";
    getline(std::cin, pass);
    std::cout << std::endl;
    ok = Admin::Login(name, pass);
    i++;
    }while(!ok && i < 3);
    return ok;
}
