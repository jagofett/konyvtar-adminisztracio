#if !defined MEMBERS_H
#define MEMBERS_H


#include <iostream>
#include <vector>
#include <string>
#include "Konyv.h"
class Books;

/**
 * tipust a gyerekei k�zul valasztjuk ki.
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
	virtual bool Loan_L(Books* mit, std::string datumtol); //k�lcs�nz�s a k�nyvre mutat� pointerrel, mikortol. ezt az adatok betoltesekor alkalmazzuk, nem ellenorizzuk a tagspecifikus adatokat.
	virtual bool Loan(Books* mit, std::string datumtol); //k�lcs�nz�s a k�nyvre mutat� pointerrel, mikortol. ezt felhasznaloi kolcsonzeskor alkalmazzuk ellenorizzuk a tagspecifikus adatokat.
	virtual int Return(int id);
	virtual void list(); //alapadatok
    void list_f(); //fejl�c
    void list_det();//r�szletes lista
	void Space(const int db, const std::string &mit) const; //db sz�k�z a kimenetre
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
	std::vector<Books*> _kivett; //a kik�lcs�nz�tt k�nyvek list�ja
	int _kolcs_hossz;	 // k�lcs�nz�s max hossza hossza, 30=h�nap, 365=�v (a program lekezeli �ket automatikusan
	int _max_konyv; //max kolcsonzott konyvek szama


};
#endif // !defined(MEMBERS_H)
