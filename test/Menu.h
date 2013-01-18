///////////////////////////////////////////////////////////
//  Menu.h
//  Implementation of the Class Menu
//  Created on:      28-nov.-2012 18:55:42
//  Original author: Akos
///////////////////////////////////////////////////////////

#if !defined(EA_4325E5CE_61C4_45dd_A673_98C8DBFD5AEA__INCLUDED_)
#define EA_4325E5CE_61C4_45dd_A673_98C8DBFD5AEA__INCLUDED_

#include <vector>
#include <string>
#include "Konyv.h"
#include "Members.h"
#include "Admin.h"

class Menu
{

public:
	Admin *m_Admin;
	Menu();

	virtual ~Menu();
	void Run(std::string type = "main");
	void LoadData();
	void SaveData();
	int GetInteger(const std::string &msg)const;
	void WriteMenu(const std::string type="main") const;
	void ManageBook(std::string type = "list");
	void SearchBook();
	void ManageMember(std::string type ="list");
	void Loan();
	bool Return();
	bool Login();
	Books* idToPoint(const int id);
    enum Exception {MISSING_FILE,BAD_INPUT,AUTH_FALIURE,BAD_AUTHFILE};
    void Space(const int db, const std::string &mit) const{for(int i=0;i<db;i++) {std::cout <<mit;}} //addot számú szóköz kiírása. megjelenítéshez szükséges
    std::string prot(std::string& str); //;->, csere hogy ne lehessen tönkretenni a fájlmentést


private:
    std::vector<Books*> _books;
    std::vector<Members*> _members;

};
#endif // !defined(EA_4325E5CE_61C4_45dd_A673_98C8DBFD5AEA__INCLUDED_)
