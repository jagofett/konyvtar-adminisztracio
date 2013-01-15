#if !defined MEMBERS_H
#define MEMBERS_H

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

	Members(std::string nev, std::string cim, std::string eler):  _nev(nev), _lakcim(cim), _eler(eler) {_id = nextId++;} //alapadatok beallitasa
	virtual ~Members();
	virtual bool Loan_L(Books* mit, std::string datumtol); //kölcsönzés a könyvre mutató pointerrel, mikortol. ezt az adatok betoltesekor alkalmazzuk, nem ellenorizzuk a tagspecifikus adatokat.
	virtual int Return(int id);
	virtual void list();
	void Edit();
	enum Exception {INVALID_RETURN};
	friend std::ostream& operator<<(std::ostream&,const Members&);
private:
    static int nextId; //automatikus novelesu id.
    //ugyfeleket azonosito mezok
    int _id; //egyeni azonosito
	std::string _nev;
	std::string _lakcim;
	std::string _eler;
	std::vector<Books*> _kivett; //a kikölcsönzött könyvek listája
	int _kolcs_hossz;	 // kölcsönzés max hossza hossza napokban
	int _max_konyv; //max kolcsonzott konyvek szama

};
#endif // !defined(MEMBERS_H)
