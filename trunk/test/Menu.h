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
	Admin *m_Admin; //bejelentkeztet�st v�gz� oszt�llyal kapcsolatot tart� elem (pointer)
	Menu(); //�dv�zl�s, �s alapadatok ki�r�sa, bejelentkeztet�s, adatok bet�lt�se
    void Clear() const; //cin szem�t t�rl�se
	virtual ~Menu(); //adatok ment�se
	void Run(std::string type = "main"); //men�k megjelen�t�se, felhaszn�l�i input-ra v�r�s (melyik men�t v�lasztja)
	void LoadData(); //�sszes adat bet�lt�se, kiv�telek dob�sa, ha s�r�lt a f�jl
	void SaveData(); //�sszes adat kiment�se, kiv�tel dob�sa ha hiba t�rt�nik a f�jlok megnyit�sakor
	bool MemberId(int& i); //felhaszn�l�t�l bek�r egy id-t, majd megkeresi az ehhez tartoz� tagot, ha nem l�tezik, hamis
	bool BookId(int& i, bool in = true); //felhaszn�l�t�l bek�r egy id-t, vagy ha m�sodik param�ternek hamisat adunk, az els�t veszi a keresend� id-nek, majd megkeresi az ehhez tartoz� k�nyvet, ha nem l�tezik, hamis
	int GetInteger(const std::string &msg)const; //eg�sz sz�m bek�r�se a felhaszn�l�t�l, bek�r� sz�veggel
	void WriteMenu(const std::string type="main") const; //men�k �s lehet�s�gek ki�r�sa (f�men�, �s k�l�nb�z� almen�k)
	void ManageBook(std::string type = "list"); //k�nyvek kezel�se (list�z�s, hozz�ad�s, t�rl�s)
	void SearchBook(); //k�nyv keres�se a felhaszn�l� �ltal megadott mez� alapj�n
	void ManageMember(std::string type ="list"); //tagok kezel�se (list�z�s, l�trehoz�s, t�rl�s, m�dos�t�s)
	void Loan(); //k�nyv k�lcs�nz�se adott tag �ltal
	void Return(); //k�nyv visszav�tele, a keretet adja hozz� (sz�veg, adatbek�r�s, ha k�s�s ki�rja)
	int Return(Members* mit); //a konkr�t visszav�tel, egy k�nyvre mutat� pointerre megh�vja a visszavev� fv-t, majd visszat�r a k�s�sel napokban
	bool Login(); //bejelentkez�st v�gz� fv
	//Books* idToPoint(const int id); //param�terk�nt �ttvett id-t alak�t k�nyvre mutat� pointerre (ha tal�l ilyen k�nyvet). az adatbet�lt�sn�l haszn�ljuk
    enum Exception {MISSING_FILE,BAD_INPUT,AUTH_FALIURE,BAD_AUTHFILE};
    void Space(const int db, const std::string &mit) const{for(int i=0;i<db;i++) {std::cout <<mit;}} //addot sz�m� karakter ki�r�sa. megjelen�t�shez sz�ks�ges
    std::string prot(std::string& str); //;->, csere hogy ne lehessen t�nkretenni a f�jlment�st


private:
    std::vector<Books*> _books; //k�nyveket t�rol� vector, ebben dolgozunk a k�nyvekkel
    std::vector<Members*> _members; //tagokat tartalmaz� vektor, itt t�roljuk az egyes k�nyvt�ri tagokat
    int _id; //felhaszn�l� �ltal megadott id

};
#endif // !defined(MENU_H)
