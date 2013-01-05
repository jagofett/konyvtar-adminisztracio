///////////////////////////////////////////////////////////
//  Tag_tipus.h
//  Implementation of the Class Tag_tipus
//  Created on:      28-nov.-2012 18:55:43
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_333192F7_DF4A_4a07_8A0D_E70B847F02F2__INCLUDED_)
#define EA_333192F7_DF4A_4a07_8A0D_E70B847F02F2__INCLUDED_

class Tag_tipus
{

public:
	Tag_tipus();
	virtual ~Tag_tipus();

private:
	/**
	 * A kölcsönzés hossza napokban megadva.
	 */
	int idotartam;
	/**
	 * max kölcsönözhetõ könyvek száma
	 */
	int konyv_db;

};
#endif // !defined(EA_333192F7_DF4A_4a07_8A0D_E70B847F02F2__INCLUDED_)
