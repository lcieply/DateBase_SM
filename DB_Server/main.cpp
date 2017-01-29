#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
using namespace boost::interprocess;

int main()
{
    shared_memory_object::remove("SMSystem");
    managed_shared_memory memory(create_only,"SMSystem",65536);
    memory.construct<interprocess_mutex>("mtx")();

    std::cout << "Serwer rozpoczal prace!" << std::endl;

    char c;
    do {
        std::cout << "Wpisz 'q' i zatwierdz [enter] by zakonczyc dzialanie!" << std::endl;
        std::cin >> c;
    } while(c != 'q');

    shared_memory_object::remove("SMSystem");
    return 0;
}
