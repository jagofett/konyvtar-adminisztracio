#if !defined MEMBERS_H
#define MEMBERS_H


#include <iostream>
#include <vector>
#include <string>
#include "Konyv.h"
class Books;


class Members //tagokat tároló abszrakt osztály (csak a leszármazottakat lehet példányosítani
{

public:

	Members(std::string nev, std::string cim, std::string eler):  _nev(nev), _lakcim(cim), _eler(eler) { //megadott adatok beállítása, id növelése
	    _id = nextId++;
	    } //alapadatok beallitasa
	virtual ~Members(){}
	virtual bool Loan_L(Books* mit, std::string datumtol); //kölcsönzés a könyvre mutató pointerrel, mikortol. ezt az adatok betoltesekor alkalmazzuk, nem ellenorizzuk a tagspecifikus adatokat.
	virtual bool Loan(Books* mit, std::string datumtol); //kölcsönzés a könyvre mutató pointerrel, mikortol. ezt felhasznaloi kolcsonzeskor alkalmazzuk ellenorizzuk a tagspecifikus adatokat.
	virtual int Return(int id); //könyv visszavitele id alapján. ha nem jó az id, kivétel dobása!
	virtual void list(); //alapadatok listázása
    void list_f(); //alap fejléc
    void list_det();//részletes lista (tag részletezése)
	void Space(const int db, const std::string &mit) const; //db megadott karakter a kimenetre (megjelenítéshez)
	virtual std::string DateWhen(std::string datum) =0; //tagtipustol fuggoen kiszamolja, hogy egy adott datumu kolcsonzest mikor kell visszahozni
	void Edit(int func, std::string &mire); //tag szerkesztése, adott típust, adott értékre
	//virtual void spec() =0;
	int GetType() const {return _tid;} //megfelelö tipus megfelelo id-jával tér vissza = típusid, 1-Hallgató, 2- professzor, 3-más egyetemi polgár, 4- egyéb
	std::string GetNev() const {return _nev;} //tag nevének lekérdezö metódusa
	int GetId() const {return _id;} //id lekérdezése
	std::string GetEler() const {return _eler;} //elérhetöség lekérdezése
	std::string GetCim() const {return _lakcim;} //lakcím lekérdezése
	int GetKolcsSize()const{return _kivett.size();} //tag hány könyvet kölcsönzött
	Books* FirstKolcs() const {return _kivett.front();} //elsö kölcsönzött könyvre mutató pointer visszaadása
	virtual bool Kolcs(){return _kivett.size()<=_max_konyv;} //annak megállapítása, hogy a tag kölcsönözhet-e még könyvet (oktatónál felüldefiniált, mert ö bármennyit kölycsönözhet
	enum Exception {INVALID_RETURN,INVALID_LOAN};//kivételek visszahozásra, és kölcsönzésre
	friend std::ostream& operator<<(std::ostream&,const Members*); //kiíró operátor
protected:
    static int nextId; //automatikus novelesu id.
    //ugyfeleket azonosito mezok
    int _id; //egyeni azonosito
	std::string _tipus; //tag tipusanak leirasa
	int _tid;           //tag tipus id-je. (adatbetolteskor hasznalt) 1-Student, 2-Prof, 3-Citizen, 4-Others
	std::string _nev;
	std::string _lakcim;
	std::string _eler;
	std::vector<Books*> _kivett; //a kikölcsönzött könyvek listája
	int _kolcs_hossz;	 // kölcsönzés max hossza hossza, 30=hónap, 365=év (a program lekezeli öket automatikusan
	int _max_konyv; //max kolcsonzott konyvek szama


};
#endif // !defined(MEMBERS_H)
