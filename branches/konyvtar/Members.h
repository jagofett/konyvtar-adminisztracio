#if !defined MEMBERS_H
#define MEMBERS_H


#include <iostream>
#include <vector>
#include <string>
#include "Konyv.h"
class Books;


class Members //tagokat t�rol� abszrakt oszt�ly (csak a lesz�rmazottakat lehet p�ld�nyos�tani
{

public:

	Members(std::string nev, std::string cim, std::string eler):  _nev(nev), _lakcim(cim), _eler(eler) { //megadott adatok be�ll�t�sa, id n�vel�se
	    _id = nextId++;
	    } //alapadatok beallitasa
	virtual ~Members(){}
	virtual bool Loan_L(Books* mit, std::string datumtol); //k�lcs�nz�s a k�nyvre mutat� pointerrel, mikortol. ezt az adatok betoltesekor alkalmazzuk, nem ellenorizzuk a tagspecifikus adatokat.
	virtual bool Loan(Books* mit, std::string datumtol); //k�lcs�nz�s a k�nyvre mutat� pointerrel, mikortol. ezt felhasznaloi kolcsonzeskor alkalmazzuk ellenorizzuk a tagspecifikus adatokat.
	virtual int Return(int id); //k�nyv visszavitele id alapj�n. ha nem j� az id, kiv�tel dob�sa!
	virtual void list(); //alapadatok list�z�sa
    void list_f(); //alap fejl�c
    void list_det();//r�szletes lista (tag r�szletez�se)
	void Space(const int db, const std::string &mit) const; //db megadott karakter a kimenetre (megjelen�t�shez)
	virtual std::string DateWhen(std::string datum) =0; //tagtipustol fuggoen kiszamolja, hogy egy adott datumu kolcsonzest mikor kell visszahozni
	void Edit(int func, std::string &mire); //tag szerkeszt�se, adott t�pust, adott �rt�kre
	//virtual void spec() =0;
	int GetType() const {return _tid;} //megfelel� tipus megfelelo id-j�val t�r vissza = t�pusid, 1-Hallgat�, 2- professzor, 3-m�s egyetemi polg�r, 4- egy�b
	std::string GetNev() const {return _nev;} //tag nev�nek lek�rdez� met�dusa
	int GetId() const {return _id;} //id lek�rdez�se
	std::string GetEler() const {return _eler;} //el�rhet�s�g lek�rdez�se
	std::string GetCim() const {return _lakcim;} //lakc�m lek�rdez�se
	int GetKolcsSize()const{return _kivett.size();} //tag h�ny k�nyvet k�lcs�nz�tt
	Books* FirstKolcs() const {return _kivett.front();} //els� k�lcs�nz�tt k�nyvre mutat� pointer visszaad�sa
	virtual bool Kolcs(){return _kivett.size()<=_max_konyv;} //annak meg�llap�t�sa, hogy a tag k�lcs�n�zhet-e m�g k�nyvet (oktat�n�l fel�ldefini�lt, mert � b�rmennyit k�lycs�n�zhet
	enum Exception {INVALID_RETURN,INVALID_LOAN};//kiv�telek visszahoz�sra, �s k�lcs�nz�sre
	friend std::ostream& operator<<(std::ostream&,const Members*); //ki�r� oper�tor
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
