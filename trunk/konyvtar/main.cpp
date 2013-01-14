#include <iostream>
#include <queue>
#include "Konyv.h"
#include "Admin.h"



using namespace std;

int main()
{
    bool ok = false;
    try{
    Admin p;
    //ok = p.Login();
    /**/ ok = true; /**/
    if (ok){
    deque<Books*> a;
	a.push_back(new Books("Kis Pista", "Ez a cime:", "Kossuth", 2012, 3, 123445));
	a.push_back(new Books("Nagy Gábor", "C++ haladóknak", "Petõfi", 2012, 3, 123445));
	a.push_back(new Books("Nagy Gábor", "Almafase", "Gangsta", 2001, 13, 17627));
    count<< endl;
	for(unsigned int i=0;i<a.size();++i){a[i]->list();}
    a.erase(a.begin()+1);
	for(unsigned int i=0;i<a.size();++i){a[i]->list();}

    }
    return 0;
    }catch(Admin::Exception ex)
    {
        if (ex == Admin::MISSING_FILE){std::cout << "Nem sikerult megnyitni a bejelentkezesi adatokat tartalmazo fajlt, a program leall!";}
        else if (ex == Admin::BAD_INPUT){std::cout << "A bejelentkezesi adatokat tartalmazo fajl hibas adatokat tartalmaz, a program leall!";}
        else{std::cout << "Ismeretlen hiba tortent a bejelentkezes kozben, a program leall!";}
        return 1;
    }
}
