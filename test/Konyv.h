#if !defined BOOKS_H
#define BOOKS_H
#include <string>
#include "Members.h"
class Members; //elker�lendo azon hibat, hogy nem latjak a class definiciojat
class Books
{

public:
	Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn);
	Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn);
	virtual ~Books() {}
	void list(); //alap lista
	void list_det(); //r�szletes lista
    void list_f(); //fejl�c
    void list_f_det(); //fejl�c
	bool Loan(std::string datum, Members* ki);
	void Return(){_ki = 0; _szabad= true;_datum="0";}
	bool Search(int mit, std::string& szoveg) ;
	std::string ToLower(std::string mit);
	int GetId()const{return _id;}
	bool GetSzabad()const{return _szabad;}
	Members* GetKi() const {return _ki;}

	std::string GetDate()const{return _datum;};
	void Space(const int db, const std::string &mit) const{for(int i=0;i<db;i++) {std::cout <<mit;}} //addot karakter addot darabszor
	friend std::ostream& operator<<(std::ostream&,const Books*);

private:
	static int nextId;	//k�vetkezo azonositot tartalmazo valtozo

	/**
	 * konyvet azonos�t� mezok
	 */
    int _id;
	std::string _szerzo;
	static int _sz_len; //szerzohoz tartozo max hossz
	std::string _cim;
	static int _c_len; //cimhez tartozo max hossz
	std::string _kiado;
	static int _k_len; //kiadohoz tartozo max hossz


	int _evszam; //kiad�si �vsz�m
	int _kiadas; // kiad�s sz�ma
	int _isbn; //ISBN azonos�t� sz�m
	bool _szabad; // az adott k�nyv k�lcs�n�zheto-e?
    std::string _datum; //ha k�lcs�nz�tt, akkor mikort�l?
    Members* _ki; //kitol kolcsonoztunk

};
#endif // !defined(BOOKS_H)
