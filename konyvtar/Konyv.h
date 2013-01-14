///////////////////////////////////////////////////////////
//  Konyv.h
//  Implementation of the Class Books
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_2BB6CA00_4C83_4045_A5DC_49A10EC72849__INCLUDED_)
#define EA_2BB6CA00_4C83_4045_A5DC_49A10EC72849__INCLUDED_

class Books
{

public:
	Books(std::string szerzo, std::string cim, std::string kiado, int evszam, int kiadas, int isbn) :  _szerzo(szerzo), _cim(cim), _kiado(kiado), _evszam(evszam), _kiadas(kiadas), _isbn(isbn)
	{
		_szabad = true;
		_id = nextId++;
	}
	virtual ~Books() {}
	void list();
	void Loan();
	void Edit();

private:
	static int nextId;
	//következo azonosito
	/**
	 * konyvet azonosító mezõ
	 */
    int _id;
	std::string _szerzo;
	std::string _cim;
	std::string _kiado;
	/**
	 * kiadási évszám
	 */
	int _evszam;
	/**
	 * kiadás száma
	 */
	int _kiadas;
	/**
	 * ISBN azonosító szám
	 */
	int _isbn;
	/**
	 * az adott könyv kölcsönözhetõ-e?
	 */
	bool _szabad;

};
#endif // !defined(EA_2BB6CA00_4C83_4045_A5DC_49A10EC72849__INCLUDED_)
