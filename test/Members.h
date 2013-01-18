#if !defined MEMBERS_H
#define MEMBERS_H


#include <iostream>
#include <vector>
#include <string>
#include "Konyv.h"
class Books;

/**
 * tipust a gyerekei közul valasztjuk ki.
 */
class Members
{

public:

	Members(std::string nev, std::string cim, std::string eler):  _nev(nev), _lakcim(cim), _eler(eler) {
	    _id = nextId++;
	    _kolcs_hossz= 14;
	    _max_konyv=2;
	    _tipus = "";
	    } //alapadatok beallitasa
	virtual ~Members(){}
	virtual bool Loan_L(Books* mit, std::string datumtol); //kölcsönzés a könyvre mutató pointerrel, mikortol. ezt az adatok betoltesekor alkalmazzuk, nem ellenorizzuk a tagspecifikus adatokat.
	virtual bool Loan(Books* mit, std::string datumtol); //kölcsönzés a könyvre mutató pointerrel, mikortol. ezt felhasznaloi kolcsonzeskor alkalmazzuk ellenorizzuk a tagspecifikus adatokat.
	virtual int Return(int id);
	virtual void list(); //alapadatok
    void list_f(); //fejléc
    void list_det();//részletes lista
	void Space(const int db, const std::string &mit) const; //db szóköz a kimenetre
	virtual std::string DateWhen(std::string datum) =0; //tagtipustol fuggoen kiszamolja, hogy egy adott datumu kolcsonzest mikor kell visszahozni
	void Edit();
	virtual void spec() =0;
	int GetType() const {return _tid;}
	std::string GetNev() const {return _nev;}
	int GetId() const {return _id;}
	int GetKolcs()const{return _kivett.size();}
	enum Exception {INVALID_RETURN,INVALID_LOAN};
	friend std::ostream& operator<<(std::ostream&,const Members*);
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
