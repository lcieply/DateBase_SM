#include <iostream>
#include "../lib/SMSystem.h"
using namespace sm;

int main() {

    SMSystem system;

    SMType<int> liczba(6);
    SMType<char> znak('k');

    std::cout << "Wartosc liczby przed wstawieniem: " << liczba.val << std::endl;
    std::cout << "Wartosc znaku przed wstawieniem: " << znak.val << std::endl;

    if(system.contains("k1")) {
        std::cout << "Usuwam obiekt pod kluczem k1!\n";
        try {
            system.remove("k1");
        } catch (SMSystemException e){
           std::cout << e.what() << std::endl;
        }
    }

    if(system.contains("k2")) {
        std::cout << "Usuwam obiekt pod kluczem k2!\n";
        try {
            system.remove("k2");
        } catch (SMSystemException e){
            std::cout << e.what() << std::endl;
        }
    }

    //=================================================

    std::cout << "Wstawiam k1!\n";
    system.insert("k1", &liczba);

    std::cout << "Wstawiam k2!\n";
    system.insert("k2", &znak);

    //=================================================

    SMType<int> liczba2;
    system.fetch("k1", liczba2);

    SMType<char> znak2;
    system.fetch("k2", znak2);

    std::cout << "Wartosc liczby po wyjeciu: " << liczba2.val << std::endl;
    std::cout << "Wartosc znaku po wyjeciu: " << znak2.val << std::endl;
    return 0;
}