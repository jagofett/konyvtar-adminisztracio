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
	 * konyvet azonos�t� mez�
	 */
	string id;
	string szerzo;
	string cim;
	string kiado;
	/**
	 * kiad�si �vsz�m
	 */
	int evszam;
	/**
	 * kiad�s sz�ma
	 */
	int kiadas;
	/**
	 * ISBN azonos�t� sz�m
	 */
	int isbn;
	/**
	 * az adott k�nyv k�lcs�n�zhet�-e?
	 */
	bool kolcsonozheto;

};
#endif // !defined(EA_2BB6CA00_4C83_4045_A5DC_49A10EC72849__INCLUDED_)
