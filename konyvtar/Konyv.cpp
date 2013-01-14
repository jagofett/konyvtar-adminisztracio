///////////////////////////////////////////////////////////
//  Konyv.cpp
//  Implementation of the Class Books
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#include <iostream>
#include "Konyv.h"

using namespace std;

int Books::nextId = 1;



void Books::list(){
//cout<< "ID\t" <<  "SZERZO\t" <<  "CIM\t" <<  "KIADO\t" <<  "EVSZAM\t" << "KIADAS\t" <<  "ISBN"<< endl;

cout<< _id << "\t" <<  _szerzo<< "\t" <<  _cim << "\t" <<  _kiado << "\t" <<  _evszam << "\t" <<  _kiadas << ". kiadas\t" <<  _isbn << endl;
}


void Books::Loan(){

}


/**
 * könyv szerkesztése
 */
void Books::Edit(){

}
