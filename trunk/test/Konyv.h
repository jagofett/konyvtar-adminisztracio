#if !defined BOOKS_H
#define BOOKS_H
#include <string>
#include "Members.h"
class Members; //elker�lendo azon hibat, hogy nem latjak a class definiciojat
class Books //k�nyvet kezel� oszt�ly
{

public:
	Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn); //user �ltal megadott k�nyv l�trehoz�sa (id automatikusan gener�l�dik)
	Books(int id, std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, std::string isbn); //bet�lt�skor haszn�lt konstruktor, id param�terk�nt �tadva
	virtual ~Books() {}
	void list(); //k�nyv alap list�z�sa
	void list_det(); //r�szletes list�z�s
    void list_f(); //fejl�c az alap list�hoz
    void list_f_det(); //fejl�c a r�szletes list�hoz
	bool Loan(std::string datum, Members* ki); //k�lcs�nz�s adott d�tumt�l, adott tag �ltal, ha m�g nem k�lcs�nz�tt a k�nyv, igaz, ha m�r igen hamis a visszat�r�si �rt�k
	void Return(){_ki = 0; _szabad= true;_datum="0";} //k�nyv visszav�tele, a sz�ks�ges param�terek be�ll�t�sa
	bool Search(int mit, std::string& szoveg) ; //k�nyv keres�se adott t�pus alapj�n
	std::string ToLower(std::string mit); //keres�shez haszn�lt seg�dfunkci�, string-et alak�t kisbet�sre
	int GetId()const{return _id;} //k�nyv id-j�nek visszaad�sa
	bool GetSzabad()const{return _szabad;} //k�lcs�n�zhet�s�g visszaad�sa
	Members* GetKi() const {return _ki;} //k�lcs�nz� tagra muutat� pointer visszaad�sa

	std::string GetDate()const{return _datum;} //k�lcs�nz�s kezdet�nek visszaad�sa
	void Space(const int db, const std::string &mit) const{for(int i=0;i<db;i++) {std::cout <<mit;}} //addot karakter addot darabszori ki�r�sa (megjelen�t�sben j�tszik szerepet)
	friend std::ostream& operator<<(std::ostream&,const Books*); //ki�r� oper�tor, a ment�shez fontos

private:
	static int nextId;	//k�vetkezo azonositot tartalmazo valtozo

	/**
	 * konyvet azonos�t� mezok
	 */
    int _id; //a k�nyvet azonos�t� ID
	std::string _szerzo; //szerzo
	static int _sz_len; //szerzohoz tartozo max hossz (kiiras)
	std::string _cim; //c�m
	static int _c_len; //cimhez tartozo max hossz (kiiras)
	std::string _kiado; //kiado neve
	static int _k_len; //kiadohoz tartozo max hossz (kiiras)


	int _evszam; //kiad�si �vsz�m
	int _kiadas; // kiad�s sz�ma
	std::string _isbn; //ISBN azonos�t� sz�m
	bool _szabad; // az adott k�nyv k�lcs�n�zheto-e?
    std::string _datum; //ha k�lcs�nz�tt, akkor mikort�l?
    Members* _ki; //kitol kolcsonoztunk

};
#endif // !defined(BOOKS_H)
