#include <iostream>
#include "Menu.h"

int main()
{
    setlocale (LC_ALL,"");

    try{
    Menu m;
    m.Run();
    }catch(Menu::Exception ex)
    {
        if (ex == Menu::MISSING_FILE){std::cout << "Nem sikerult megnyitni egy fajlt, a program leall!";}
        else if (ex == Menu::BAD_INPUT){std::cout << "Az egyik adatokat tartalmazo fajl hibas adatokat tartalmaz, a program leall!";}
        else if (ex == Menu::AUTH_FALIURE){std::cout << "A bejelentkez�s nem siker�lt, a program le�ll!";}
        else if (ex == Menu::BAD_AUTHFILE){std::cout << "A bejelentkez�si f�jl s�r�lt, a bejelentkez�s nem hajthat� v�gre, a program le�ll!";}
        else{std::cout << "Ismeretlen hiba tortent a futas kozben, a program leall!";}
        return 1;
    }
    return 0;
}
