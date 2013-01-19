///////////////////////////////////////////////////////////
//  Menu.h
//  Implementation of the Class Menu
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "Konyv.h"
#include "Members.h"
#include "Admin.h"

class Menu
{

public:
	Admin *m_Admin; //bejelentkeztetést végzö osztállyal kapcsolatot tartó elem (pointer)
	Menu(); //üdvözlés, és alapadatok kiírása, bejelentkeztetés, adatok betöltése
    void Clear() const; //cin szemét törlése
	virtual ~Menu(); //adatok mentése
	void Run(std::string type = "main"); //menük megjelenítése, felhasználói input-ra várás (melyik menüt választja)
	void LoadData(); //összes adat betöltése, kivételek dobása, ha sérült a fájl
	void SaveData(); //összes adat kimentése, kivétel dobása ha hiba történik a fájlok megnyitásakor
	bool MemberId(int& i); //felhasználótól bekér egy id-t, majd megkeresi az ehhez tartozó tagot, ha nem létezik, hamis
	bool BookId(int& i, bool in = true); //felhasználótól bekér egy id-t, vagy ha második paraméternek hamisat adunk, az elsöt veszi a keresendö id-nek, majd megkeresi az ehhez tartozó könyvet, ha nem létezik, hamis
	int GetInteger(const std::string &msg)const; //egész szám bekérése a felhasználótól, bekérö szöveggel
	void WriteMenu(const std::string type="main") const; //menük és lehetöségek kiírása (fömenü, és különbözö almenük)
	void ManageBook(std::string type = "list"); //könyvek kezelése (listázás, hozzáadás, törlés)
	void SearchBook(); //könyv keresése a felhasználó által megadott mezö alapján
	void ManageMember(std::string type ="list"); //tagok kezelése (listázás, létrehozás, törlés, módosítás)
	void Loan(); //könyv kölcsönzése adott tag által
	void Return(); //könyv visszavétele, a keretet adja hozzá (szöveg, adatbekérés, ha késés kiírja)
	int Return(Members* mit); //a konkrét visszavétel, egy könyvre mutató pointerre meghívja a visszavevö fv-t, majd visszatér a késésel napokban
	bool Login(); //bejelentkezést végzö fv
	//Books* idToPoint(const int id); //paraméterként áttvett id-t alakít könyvre mutató pointerre (ha talál ilyen könyvet). az adatbetöltésnél használjuk
    enum Exception {MISSING_FILE,BAD_INPUT,AUTH_FALIURE,BAD_AUTHFILE};
    void Space(const int db, const std::string &mit) const{for(int i=0;i<db;i++) {std::cout <<mit;}} //addot számú karakter kiírása. megjelenítéshez szükséges
    std::string prot(std::string& str); //;->, csere hogy ne lehessen tönkretenni a fájlmentést


private:
    std::vector<Books*> _books; //könyveket tároló vector, ebben dolgozunk a könyvekkel
    std::vector<Members*> _members; //tagokat tartalmazó vektor, itt tároljuk az egyes könyvtári tagokat
    int _id; //felhasználó által megadott id

};
#endif // !defined(MENU_H)
