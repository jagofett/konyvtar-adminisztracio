#if !defined BOOKS_H
#define BOOKS_H
#include <string>
#include "Members.h"
class Members; //elkerülendo azon hibat, hogy nem latjak a class definiciojat
class Books
{

public:
	Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn);
	Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn);
	virtual ~Books() {}
	void list(); //alap lista
	void list_det(); //részletes lista
    void list_f(); //fejléc
    void list_f_det(); //fejléc
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
	static int nextId;	//következo azonositot tartalmazo valtozo

	/**
	 * konyvet azonosító mezok
	 */
    int _id;
	std::string _szerzo;
	static int _sz_len; //szerzohoz tartozo max hossz
	std::string _cim;
	static int _c_len; //cimhez tartozo max hossz
	std::string _kiado;
	static int _k_len; //kiadohoz tartozo max hossz


	int _evszam; //kiadási évszám
	int _kiadas; // kiadás száma
	int _isbn; //ISBN azonosító szám
	bool _szabad; // az adott könyv kölcsönözheto-e?
    std::string _datum; //ha kölcsönzött, akkor mikortól?
    Members* _ki; //kitol kolcsonoztunk

};
#endif // !defined(BOOKS_H)
