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
else{LoadData();}
cout << "Az adatok betöltése sikeres!" << endl;
}
Menu::~Menu(){
SaveData();
cout << "Az adatok mentése sikeres volt!" << endl;
}




void Menu::Run(string type){

int option = 0;
if (type=="main"){
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
    }
}while(option != 0);
}
if (type=="member") //tagok menu
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
            Run("det");
            break;
    }
}while(option != 0);
}
if (type=="det"){
do{
    WriteMenu("det"); //könyvek kiírása
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
	cout << "--- FÖMENU ---" << endl;
	cout << "Valassz az alabbi opciok kozul!" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Könyvek kezelése:" << endl;
	cout << "\t2 - Tagok kezelése" << endl;
	cout << "\t3 - Kölcsönzés" << endl;
	cout << "\t4 - Visszavétel" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t0 - Mentés és kilépés" << endl;
}
if(type=="book")
{
    cout << endl << endl;
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
    cout << endl << endl;
	cout << "Tagok kezelése" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Tagok listázása" << endl;
	cout << "\t2 - Tag felvétele" << endl;
	cout << "\t3 - Tag törlése" << endl;
	cout << "\t4 - Tag adatainak listázása, szerkesztése" << endl;
	cout << "\t-----------------" << endl;
	cout << "\t0 - Vissza a fömenübe" << endl;
}
if (type == "det"){
    cout << endl << endl;
	cout << "Tag adatainak kezelése" << endl;
    cout << "\t-----------------" << endl;
	cout << "\t1 - Tag adatainak lekérdezése" << endl;
	cout << "\t2 - Tag szerkesztése" << endl;
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
void Menu::ManageBook(string type){ //kesz (TODO kölcsönzés frissiteni!)
if (_books.size()>0){
if (type=="list"){ //könyek listázása
//    cout << "KÖNYVEK"<< endl;
    cout << endl;
    _books[0]->list_f();
    for(unsigned int i=0;i<_books.size();++i){_books[i]->list();}
    Space(140, "-");
    cout<< endl;
}

if(type=="delete"){


    char vsz;
    cout << endl << "-- Könyv törlése --" << endl;
    ManageBook("list");
Clear();

    cout << "Válasszon könyvet a törléshez! Ehhez adja meg a könyvhez tartozó ID-t!" << endl;
    //_id = GetInteger("A választott ID: ");
    int i;

    if(BookId(i)){
        _books[i]->list_f(); _books[i]->list();
        //a könyv kintlévöségének ellenörzése!
        if(!_books[i]->GetSzabad()){
            cout << endl << endl << "A könyv kölcsönözve van, a törlés elött vissza kell venni! Megteszi ezt most? (i - igen, minden más - nem)" << endl;
            cin >> vsz;
            if(tolower(vsz)=='i'){
                try{

                Return(_books[i]->GetKi()); //finomitas a return muvelet alapján
                }catch(Members::Exception ex){cout << "A visszavétel nem sikerült, a törlés nem folytatható!" << endl;}
            }else{cout << "A visszavétel megszakítva, a törlés nem folytatható!" << endl;}
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
if (type=="new") //új könyv hozzáadása
{
    cout << endl <<  "-- Új könyv felvétele --" << endl;
    string szerz, cim, kiado, isbn;
    char vsz;
    int kiadas, ev;
Clear();
    cout << "Adja meg a könyv adatait! (ebben a verzióban az ékezetes betük nem támogatottak!)" << endl; //TODO ékezetes beolvasás!

    cout << "Szerzö: "; getline(cin, szerz);
    cout  << "A könyv címe: "; getline(cin, cim);
    cout  << "A kiadó neve: "; getline(cin , kiado) ;
    ev = GetInteger("A kiadás dátuma: ");
    kiadas = GetInteger("Hányadik kiadás? ");
    Clear();
    cout  << "A könyv ISBN száma: "; getline(cin , isbn) ; //TODO min hossz ISBN. számnak
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

}


/**
 * könyvek keresése
 */
void Menu::SearchBook(){
cout << endl << "-- Köny keresése --" << endl;
cout << "Mi alapján keresel? (1 - Szerzö, 2 - Cím, 3 - ISBN, 4 - azonosító)" << endl;
int vsz, db;
Clear();
vsz = GetInteger("Keresés alapja: ");
string mit;
Clear();
cout << "Írd be a keresendö szöveget! " << endl;
cin >> mit;
if(_books.size()>0){
_books[0]->list_f();
db = 0;
for(int i = 0;i<_books.size();++i)
{
   if (_books[i]->Search(vsz,mit)) {_books[i]->list();db++;};
}
if (db==0) {cout << "FIGYELEM! Nincs találat!" << endl;}
}else {cout << "Nincs egy könyv se!" << endl;}//nincs könyv

}
void Menu::Clear()const{
    cin.clear(); //cin tisztitasa, hogy rendesen müködjön a beolvasas (getline és >> keverése miatt van rá szükség)
    cin.sync();
}

bool Menu::MemberId(int& i){
Clear();
_id = 0;
_id = GetInteger("A választott ID: ");
i = 0;
for(i=0;i<_members.size();++i){if (_id==(_members[i])->GetId()){break;}}
return i<_members.size();
}

bool Menu::BookId(int& i, bool in){
if(in){ //ha a felhasználótól kell bekérni az adatot
Clear();
_id = 0;
_id = GetInteger("A választott ID: ");
}else {_id = i;} //ha paraméterként adott id-t keresünk (fájlbeolvasás)
i = 0;
for(i=0;i<_books.size();++i){if (_id==(_books[i])->GetId()){break;}}
return i<_books.size();
}
/**
 * tagok kezelése, paraméterként a muvelet típusa
 */
void Menu::ManageMember(string type){
if(_members.size()!=0) //ha van tag
{
if (type=="list"){ //tagok listázása

    //fejléc
    cout << endl;
    _members[0]->list_f();
    //az adott adatok kiírása
    for(unsigned int i=0;i<_members.size();++i){_members[i]->list();}
    Space(160, "-");
    cout << endl;

} // listázás vége
if (type=="delete")
{
    char vsz;
    cout << "-- Tag törlése --" << endl;
    ManageMember("list");


    cout << "Válasszon tagot a törléshez! Ehhez adja meg a taghoz tartozo ID-t!" << endl;
//    _id = GetInteger("A választott ID: ");
    int i;
//    for(i=0;i<_members.size();++i){if (_id==(_members[i])->GetId()){break;}}   //a felh. által megadott id keresése
    if(MemberId(i)){
        _members[i]->list_det(); //a törlésre kijelölt tag listázása
        //a tag kölcsönzéseinek ellenörzése!
        if(!_members[i]->GetKolcsSize()==0){
            cout << endl << "A tagnak élö kölcsönzései vannak, ezeket meg kell szüntetni, mielött törölné! Megteszi ezt most?" << endl << "i - igen, minden más - nem : "; //TODO ha a visszavétl kész, ezt megoldani
            Clear();
            cin >> vsz;
            if(tolower(vsz)=='i') //ha a kölcsönzött könyveket vissza kell venni:
            {
                try{
                cout << "Kintlévöségek visszavétele folyamatban." << endl << endl;
                int meret = _members[i]->GetKolcsSize();
                for(int j=0;j<meret;++j){
                    _id = _members[i]->FirstKolcs()->GetId();
                    cout << _id << " ID-jú könyv visszavétele...";

                    int keses = Return(_members[i]);
                    if (keses>0){cout <<endl << "FIGYELEM!"<< endl << keses << " nap késéssel hozták vissza a könyvet!" << endl;}
                    cout << "A könyv visszavéve!" << endl;
                    }
                    cout << endl << "Minden kölcsönzött könyv visszavéve!" << endl;
                    }catch(Members::Exception ex){cout << "A visszavétel nem sikerült, a törlés nem folytatható!" << endl;}
            }else{cout << "Kintlévöségek visszavétele megszakítva, a törlés nem folytatható!" << endl;} //ha nem vesszük vissza a könyveket

        }//élö kölcs visszavételének vége
        if(_members[i]->GetKolcsSize()==0){ // ha  felszabadítottuk a tagot, akkor folytatjuk (vagy nincs kölcsönzése)
        cout << "Biztos törli ezt a tagot? (i - igen, minden más - nem)" << endl;
        cin >> vsz;
        if (tolower(vsz)!='i'){cout << "A müvelet visszavonva!" << endl;}
        else {

            delete _members[i];
            _members.erase(_members.begin()+i);
            cout << "A tag törölve!" << endl;}
        }
    }else{cout << "Hiba! Nincs ilyen ID, a törlés nem lehetséges!" << endl;}

} //törlés vége
if(type=="edit"){ //részletes listázás
    cout << endl << "-- Választott tag adatainak listázása --" << endl;

    ManageMember("list"); //összes tag listázása, hogy lássuk, miböl lehet választani
    cout << "Kérem válasszon egy tagot, akinek további adataira kíváncsi! Az ID-jét adja meg!" << endl;
    Clear();
    int i;

    if(MemberId(i)){
    _members[i]->list_det();
    _id = i; //eltároljuk a privát tagban, hogy hanyadik elemet vizsgáltuk
    }else{cout << "Hiba! Nincs ilyen ID, a listázás nem lehetséges!" << endl;}
}
if(type=="write"){
    if(!(_id<_members.size())){cout << "Kérlek válassz egy ID-t!" << endl;ManageMember("edit");}else{ //helyes ID választás kikényszerítése
    int vsz = 0;
    char v;
    string mod, nev, cim, eler;
    nev = _members[_id]->GetNev();
    cim = _members[_id]->GetCim();
    eler = _members[_id]->GetEler();
    Clear();
    cout << endl << "-- Választott tag adatainak szerkesztése --" << endl;
    _members[_id]->list_det();
    cout << "Melyik adattagot módosítja? 1 - Név, 2 - Lakcím, 3 - Elérhetöség, 4 - Típus" << endl;
    vsz = GetInteger("A választott adattag: ");
    Clear();
    switch(vsz){
    case 1:

        cout << "Mi legyen a tag új neve? ";
        getline(cin, mod);
        Clear();
        cout << "Rögzíti a módosítást? (" << nev << "->" << mod << ") i - igen, minden más - nem" << endl;
        cin >> v;
        Clear();

        break;
    case 2:
        cout << "Mi legyen a tag új lakcíme? ";
        getline(cin, mod);
        Clear();
        cout << "Rögzíti a módosítást? (" << cim<< "->" << mod << ") i - igen, minden más - nem" << endl;
        cin >>v;
        Clear();
        break;
    case 3:
        cout << "Mi legyen a tag új elérhetösége? ";
        getline(cin, mod);
        Clear();
        cout << "Rögzíti a módosítást? (" <<eler << "->" << mod << ") i - igen, minden más - nem" << endl;
        cin >>v;
        Clear();
        break;
    case 4:
        cout << "Mi legyen a tag új típusa?" << endl << "(1 - Egyetemi Hallgato, 2 - Egyetemi Oktato, 3 - Egyéb Egyetemhez tartozo személy, minden más - Mindenki más)" << endl;
        getline(cin, mod);
        Clear();
        cout << "Rögzíti a módosítást? i - igen, minden más - nem" << endl;
        cin >> v;
        Clear();
        break;
    }
if(vsz>=1 && vsz<=4 && tolower(v)=='i'){ //ha érvéseset választott, és elfogadta a változásokat
    if(vsz!=4){
    _members[_id]->Edit(vsz, mod);
    cout << "A módosítás sikerült!" << endl;
    }
    else{ //ha tipust kell változtatni: új példány, a régit ráiránítjuk, és a mögöttes adatét töröljük
        if(_members[_id]->GetKolcsSize()==0){
        Members* tmp;
        int tp = atoi(mod.c_str());
        if (tp == 1){ tmp = new Student(nev, cim, eler);} //hallgato
        else if (tp == 2){ tmp = new Prof(nev, cim, eler);} // tanár
        else if (tp == 3){ tmp = new Citizen(nev, cim, eler);} //egyéb egyetem
        else{ tmp = new Others(nev, cim, eler);} //mindenki más
        if(!tmp->Kolcs()){cout << "Figyelem! A tagnak több könyve van, mint az új típusa engedné!" << endl << "Addig nem lehetséges a kölcsönzés, amíg nem csökken a megengedett alá ez a szám! (" << tmp->MaxKolcs() << " db)" << endl;}
        _members.erase(_members.begin()+_id);
        _members[_id] = tmp;
        cout << "A módosítás sikerült!" << endl;
        }else{cout << endl << "A tagnak élö kölcsönzései vannak! A típusmódosítás csak akkor támogatott, ha nincsenek kölcsönzések!" << endl;}
    }

}else{cout << endl << "Nem történt módosítás!" << endl;}
_members[_id]->list_det();
    }//létezö id vége
} // módossítás vége
}else {cout << "Nincs egy tag sem az adatbázisban, kérlek vegyél fel párat!" << endl;} //ha nincs tag

if (type=="new") //új könyv hozzáadása
{
    cout <<endl << "-- Új tag felvétele --" << endl;
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
    cout << "Adja meg, milyen típusu a tag! (1 - Egyetemi Hallgato, 2 - Egyetemi Oktato, 3 - Egyéb Egyetemhez tartozo személy, 4 - Mindenki más)" << endl;
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
}//új tag vége

}


/**
 * kölcsönzés
 */
void Menu::Loan(){
cout << endl << "-- Könyv kölcsönzése --" << endl;
int i = 0;
int j = 0; //j - tagazonosito, i - könyvazon
char biztos;
_id = -1;
cout << "Kérlek válaszd a tagot, aki kölcsönözni akar! Az ID-jét add meg!" << endl;
ManageMember("list");
if(MemberId(j)){ //ha valós tag

cout << "Kérlek válaszd ki a kölcsönzendö könyvet! Az ID-jét add meg!" << endl;
ManageBook("list");

if(BookId(i)){ //valós ID-t adott meg
    if (_books[i]->GetSzabad()){ //ha szabad a könyv
        //tag adatainak listázása, megerösités kérése a kölcsönzésre
        cout << "Kölcsönzö tag adatai: " << endl;
        _members[j]->list_det();
        cout << endl << "A kölcsönzendö könyv adatai: "<< endl << endl;
        _books[i]->list_f();
        _books[i]->list();
        if(!_members[j]->Kolcs()){cout << endl << endl << "HIBA! A tag elérte a maximális kölcsönözhetö mennyiséget, a kölcsönzés nem lehetséges!" << endl;} //ha nem kölcsönözhet már
        else{
        cout << endl << "Rögzíti a kölcsönzést? (i - igen, minden más  - nem)" << endl;
        Clear();
        cin >> biztos;
        if (tolower(biztos)!='i'){cout << "A kölcsönzés visszavonva!" << endl;}
        else{   //ha megerösített a kölcsönzés, megpróbáljuk végrehajtani

        MyDate* ma = new MyDate();
        string dat = ma->getDate();
        if(!(_members[j]->Loan(_books[i], dat))){cout << "Sikertelen kölcsönzés, a tag nem kölcsönözhet több könyvet!";} //ha nem sikerült a kölcsönzés, túllépte a keretet.
        else{
            cout << "Sikeres kölcsönzés" << endl;
            ManageBook("list");}
        }//kölcsönzés vége
        } //lehetséges kölcsönzés vége
    }else {cout << "Hiba! A könyv már kölcsönözve van! Próbáljon másik könyvet kölcsönözni!" << endl;}

}//book Id check vége
else{cout << "Hiba! Nincs ilyen Könyv-ID, a kölcsönzés nem lehetséges!" << endl;}
}//member ID check vége
else{cout << "Hiba! Nincs ilyen Tag-ID, a kölcsönzés nem lehetséges!" << endl;}
}

/**
 * visszahozatal
 * visszatérési érték hogy történt-e késés
 */
void Menu::Return(){
cout << endl << "-- Könyv visszavétele --" << endl;
int i = 0; // i - könyvazon
_id = -1; //
char biztos; //megerösítés tárolása
cout << "Kérlek válaszd a könyvet, amit visszahoztak! Az ID-jét add meg!" << endl;
ManageBook("list");
if(BookId(i)){ //ha valós könyv
    int keses;
    cout << "Részletes adatok a kölcsönzöröl: " << endl;
    _books[i]->GetKi()->list_det();
    cout << "Rögzíti a visszavételt? (i - igen, minden más  - nem)" << endl;
    Clear();
    cin >> biztos;
    if (tolower(biztos)!='i'){cout << "A müvelet visszavonva! Nem történt visszavétel." << endl;}
    else{
    try{
    keses = Return(_books[i]->GetKi());
    if (keses>0){cout <<endl << "FIGYELEM!"<< endl << keses << " nap késéssel hozták vissza a könyvet!" << endl;}
    cout << "A visszavétel sikerült." << endl;

    }catch(Members::Exception ex){cout << "A visszavétel nem sikerült, a könyv nem található!" << endl;}

    }//visszavétel vége

}//member ID check vége
else{cout << "Hiba! Nincs ilyen Könyv-ID, a visszavétel nem lehetséges!" << endl;}
}

int Menu::Return(Members* mit){
int mennyi;
mennyi = (mit->Return(_id));
return mennyi;
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
        if (tipus!=""){ //ha véletlen nem egy üres sor lenne
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

