///////////////////////////////////////////////////////////
//  Members.cpp
//  Implementation of the Class Members
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#include "Members.h"




 Members::Members(){

}


 Members::~Members(){

}


/**
 * kölcsönzés: figyelni, hogy a könyv kölcsönözhetõ, és a tag még kölcsönözhet, ha
 * sikertelen hamis érték visszaadás
 *
 * tagtípusonként változik a kölcsönzõ mûvelet
 */
bool Members::Loan(Books mit, int datumtol){

	return false;
}


/**
 * ha történt késés, igaz értéket ad vissza
 */
 
bool Members::Return(Books mit){

	return false;
}


void Members::Edit(){

}

