///////////////////////////////////////////////////////////
//  Admin.cpp
//  Implementation of the Class Admin
//  Created on:      28-dec.-2012 19:42:13
//  Original author: Akos
///////////////////////////////////////////////////////////

#include "Admin.h"
#include <fstream>

Admin::Admin() //adatok beolvasása
{
    std::ifstream f; //a bejelentkezesi adatokat tartalmazo fajl

    f.open("pass.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
        while(f.good()) //fajlbeolvasas
        {
            std::string tmp; //ideiglenes fájltárolo

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
        if(nev.size()!= jelszo.size() || nev.size()==0) throw BAD_INPUT; //ha nem egyforma a nevek és jelszavak száma
    }
    else throw MISSING_FILE;  //ha nem kivétel dobása
}


bool Admin::Login(std::string name, std::string pass) //bejelentkezési kísérlet, a paraméterként átvett értékek megtalálhatók a megfelelö változókban igaz (keresés tul képp)
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

bool Admin::Login() //felhasználótól bekéri a bejelentkezési nevet és jelszót
{
    std::string name, pass;
    bool ok = false; //visszatérö változó, ill további üzenet kiírásakor ezt is vizsgáljuk
    int i = 0; //kísérletek száma
    do{
    if (ok == false && i != 0) //ha nem elsö próbálkozás, hibaüzenet megjelenítése
    {
    std::cout << "Hibás felhasználó név vagy jelszó. Próbálja újra! Még " << 3-i << " lehetösége van" << std::endl;
    }
    std::cout << "Adja meg felhasznaloi nevet: "; //név bekérése
    getline(std::cin, name);

    std::cout << "Adja meg jelszavat: "; //jelszó bekérése
    getline(std::cin, pass);
    std::cout << std::endl;
    ok = Admin::Login(name, pass); //ellenörzés
    i++;
    }while(!ok && i < 3); //3 lehetöség, vagy amig egy jó párost meg nem ad
    return ok;
}
