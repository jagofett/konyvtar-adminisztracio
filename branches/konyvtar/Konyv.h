#if !defined BOOKS_H
#define BOOKS_H
#include <string>
#include "Members.h"
class Members; //elkerülendo azon hibat, hogy nem latjak a class definiciojat
class Books //könyvet kezelö osztály
{

public:
	Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn); //user által megadott könyv létrehozása (id automatikusan generálódik)
	Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn); //betöltéskor használt konstruktor, id paraméterként átadva
	virtual ~Books() {}
	void list(); //könyv alap listázása
	void list_det(); //részletes listázás
    void list_f(); //fejléc az alap listához
    void list_f_det(); //fejléc a részletes listához
	bool Loan(std::string datum, Members* ki); //kölcsönzés adott dátumtól, adott tag által, ha még nem kölcsönzött a könyv, igaz, ha már igen hamis a visszatérési érték
	void Return(){_ki = 0; _szabad= true;_datum="0";} //könyv visszavétele, a szükséges paraméterek beállítása
	bool Search(int mit, std::string& szoveg) ; //könyv keresése adott típus alapján
	std::string ToLower(std::string mit); //kereséshez használt segédfunkció, string-et alakít kisbetüsre
	int GetId()const{return _id;} //könyv id-jének visszaadása
	bool GetSzabad()const{return _szabad;} //kölcsönözhetöség visszaadása
	Members* GetKi() const {return _ki;} //kölcsönzö tagra muutató pointer visszaadása

	std::string GetDate()const{return _datum;} //kölcsönzés kezdetének visszaadása
	void Space(const int db, const std::string &mit) const{for(int i=0;i<db;i++) {std::cout <<mit;}} //addot karakter addot darabszori kiírása (megjelenítésben játszik szerepet)
	friend std::ostream& operator<<(std::ostream&,const Books*); //kiíró operátor, a mentéshez fontos

private:
	static int nextId;	//következo azonositot tartalmazo valtozo

	/**
	 * konyvet azonosító mezok
	 */
    int _id; //a könyvet azonosító ID
	std::string _szerzo; //szerzo
	static int _sz_len; //szerzohoz tartozo max hossz (kiiras)
	std::string _cim; //cím
	static int _c_len; //cimhez tartozo max hossz (kiiras)
	std::string _kiado; //kiado neve
	static int _k_len; //kiadohoz tartozo max hossz (kiiras)


	int _evszam; //kiadási évszám
	int _kiadas; // kiadás száma
	std::string _isbn; //ISBN azonosító szám
	bool _szabad; // az adott könyv kölcsönözheto-e?
    std::string _datum; //ha kölcsönzött, akkor mikortól?
    Members* _ki; //kitol kolcsonoztunk

};
#endif // !defined(BOOKS_H)
