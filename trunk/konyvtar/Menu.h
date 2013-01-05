///////////////////////////////////////////////////////////
//  Menu.h
//  Implementation of the Class Menu
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_4325E5CE_61C4_45dd_A673_98C8DBFD5AEA__INCLUDED_)
#define EA_4325E5CE_61C4_45dd_A673_98C8DBFD5AEA__INCLUDED_

#include "Konyv.h"
#include "Members.h"

class Menu
{

public:
	Admin *m_Admin;
	void Menu();
	virtual void ~Menu();
	void Run();
	void LoadData();
	void SaveData();
	void WriteMenu(string type);
	void ModifyBook(string type = add);
	void SearchBook();
	void ModifyMember(string type);
	void Loan();
	bool Return();
	void Login();

private:
	list<Konyv*> _books;
	list <Members*> _members;

};
#endif // !defined(EA_4325E5CE_61C4_45dd_A673_98C8DBFD5AEA__INCLUDED_)
