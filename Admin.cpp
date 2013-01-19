///////////////////////////////////////////////////////////
//  Admin.cpp
//  Implementation of the Class Admin
//  Created on:      28-dec.-2012 19:42:13
//  Original author: Akos
///////////////////////////////////////////////////////////

#include "Admin.h"
#include <fstream>

Admin::Admin() //adatok beolvas�sa
{
    std::ifstream f; //a bejelentkezesi adatokat tartalmazo fajl

    f.open("pass.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
        while(f.good()) //fajlbeolvasas
        {
            std::string tmp; //ideiglenes f�jlt�rolo

            getline(f, tmp, ';' ); //nev beolvasasa
            if (tmp!=""){ //ha nem ures a beolvasott resz, berakjuk a megfelelo helyre
            nev.push_back(tmp);
            }
            getline(f, tmp, '\n' );
            if (tmp!=""){
            jelszo.push_back(tmp);
            }

        }


        f.close();
        if(nev.size()!= jelszo.size() || nev.size()==0) throw BAD_INPUT; //ha nem egyforma a nevek �s jelszavak sz�ma
    }
    else throw MISSING_FILE;  //ha nem kiv�tel dob�sa
}


bool Admin::Login(std::string name, std::string pass) //bejelentkez�si k�s�rlet, a param�terk�nt �tvett �rt�kek megtal�lhat�k a megfelel� v�ltoz�kban igaz (keres�s tul k�pp)
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

bool Admin::Login() //felhaszn�l�t�l bek�ri a bejelentkez�si nevet �s jelsz�t
{
    std::string name, pass;
    bool ok = false; //visszat�r� v�ltoz�, ill tov�bbi �zenet ki�r�sakor ezt is vizsg�ljuk
    int i = 0; //k�s�rletek sz�ma
    do{
    if (ok == false && i != 0) //ha nem els� pr�b�lkoz�s, hiba�zenet megjelen�t�se
    {
    std::cout << "Hib�s felhaszn�l� n�v vagy jelsz�. Pr�b�lja �jra! M�g " << 3-i << " lehet�s�ge van" << std::endl;
    }
    std::cout << "Adja meg felhasznaloi nevet: "; //n�v bek�r�se
    getline(std::cin, name);

    std::cout << "Adja meg jelszavat: "; //jelsz� bek�r�se
    getline(std::cin, pass);
    std::cout << std::endl;
    ok = Admin::Login(name, pass); //ellen�rz�s
    i++;
    }while(!ok && i < 3); //3 lehet�s�g, vagy amig egy j� p�rost meg nem ad
    return ok;
}
