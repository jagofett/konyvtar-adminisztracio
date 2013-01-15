#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Date.hpp"
#include "Konyv.h"
#include "Admin.h"
#include "Members.h"




using namespace std;
void LoadData();
void SaveData();
Books* idToPoint(int id);
vector<Books*> k;
vector<Members*> t;

enum Exception {MISSING_FILE,BAD_INPUT};
int main()
{
    setlocale (LC_ALL,"HUN");
    bool ok = false;
    try{
    Admin p;
    //ok = p.Login();
    /**/ ok = true; /**/
    if (ok){
	LoadData();
	//t.push_back(new Members("Nagy Gábor", "Petofi utca 12.", "nagy.gabor@gmail.com"));
	cout << "Tagok: " << t.size() << endl;
    for(unsigned int i=0;i<t.size();++i){t[i]->list();}
    MyDate a("20130110");
    MyDate b(2012,1,15);
    cout <<b.maElter() << " nap";

cout << endl<<endl;
	/*k.push_back(new Books("Kis Pista", "Ez a cime:", "Kossuth", 2012, 3, 123445));
	k.push_back(new Books("Nagy Gábor", "C++ haladoknak", "Petofi", 2012, 3, 123445));
	*/
//k.push_back(new Books("Nagy Gábor", "Almafase", "Gangsta", 22001, 13, 111111111));

    cout << "KONYVEK"<< endl;
	for(unsigned int i=0;i<k.size();++i){k[i]->list();}
    cout<< endl;

    Books* p= idToPoint(6);
    if (p==0){throw BAD_INPUT;} //ha nincs olyan konyv, kivetel dobasa
    t[1]->Loan_L(p, "20130116");

   // k.erase(k.begin()+1); //törles
    SaveData();






    }
    return 0;
    }catch(Admin::Exception ex)
    {
        if (ex == Admin::MISSING_FILE){std::cout << "Nem sikerult megnyitni a bejelentkezesi adatokat tartalmazo fajlt, a program leall!";}
        else if (ex == Admin::BAD_INPUT){std::cout << "A bejelentkezesi adatokat tartalmazo fajl hibas adatokat tartalmaz, a program leall!";}
        else{std::cout << "Ismeretlen hiba tortent a bejelentkezes kozben, a program leall!";}
        return 1;
    }
}
Books* idToPoint(int id){
//cout << "\n\n--ITERATOROK--\n\n";
bool talal = false;
vector<Books*>::iterator it;
for(it=k.begin();it!=k.end();++it)
{
    if ((*it)->GetId()==id){ talal = true; break;}
}
Books *p = 0;
//cout << (p) << endl;
if(talal){p=*it;}
//cout << p << endl;
return p;
}
void LoadData(){
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
            k.push_back(new Books(atoi(id.c_str()), szer, cim, kia, atoi(ev.c_str()), atoi(kiadas.c_str()), atoi(isbn.c_str())));
            }

        }


        f.close();
    }
    else throw MISSING_FILE;  //ha nem sikerült a fájlt megnyitni kivétel dobása*/
    }
    //tagok betöltése
    {
    string nev, cim, eler, db_s, kolcs, date;
    int db, id; //id=kolcsonzott konyv id-je, db az osszes kolcsonzes db-szama
    f.open("tagok.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
        while(f.good()) //fajlbeolvasas
        {
//            f>>id;
            //getline(f, tipus, ';' ); //tipus
            getline(f, nev, ';' ); //nev
            getline(f, cim, ';' ); //cim
            getline(f, eler, ';' ); //elerhetoseg
            getline(f, db_s, ';' ); //kolcsonzesek szama
            Members *tmp = new Members(nev, cim, eler);
            db = atoi(db_s.c_str());
            for(int i=1;i<=db;i++)
            {
                getline(f, kolcs, ';' ); //adott kolcsonzes
                if (i==db){getline(f, date, '\n' );} //adott kolcsonzes datuma
                else {getline(f, date, ';' );} //adott kolcsonzes datuma

                id = atoi(kolcs.c_str());
                Books* p= idToPoint(id);
                if (p==0){throw BAD_INPUT;} //ha nincs olyan konyv, kivetel dobasa
                tmp->Loan_L(p, date);
            }
            if (nev!=""){
            t.push_back(tmp);
            }

        }

        f.close();
    }
    else throw MISSING_FILE;  //ha nem sikerült a fájlt megnyitni kivétel dobása
    }
}
void SaveData(){
    std::ofstream f; //a konyveket tartalmazo fajl
    //könyvek kimentése
    f.open("konyv.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
	for(unsigned int i=0;i<k.size();i++){f<<(*k[i]);}
	f.close();
    }
    else throw MISSING_FILE;  //ha nem kivétel dobása*/

    //tagok kimentese
    f.open("tagok.dat");
    if (f.is_open()) //fajl megnyitasa sikeres?
    {
	for(unsigned int i=0;i<t.size();i++){f<<(*t[i]);}
	f.close();
    }
    else throw MISSING_FILE;  //ha nem kivétel dobása*/
}
