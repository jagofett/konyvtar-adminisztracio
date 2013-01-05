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
	void Books();
	virtual void ~Books();
	void Loan();
	void Edit();

private:
	/**
	 * konyvet azonosító mezõ
	 */
	string id;
	string szerzo;
	string cim;
	string kiado;
	/**
	 * kiadási évszám
	 */
	int evszam;
	/**
	 * kiadás száma
	 */
	int kiadas;
	/**
	 * ISBN azonosító szám
	 */
	int isbn;
	/**
	 * az adott könyv kölcsönözhetõ-e?
	 */
	bool kolcsonozheto;

};
#endif // !defined(EA_2BB6CA00_4C83_4045_A5DC_49A10EC72849__INCLUDED_)
