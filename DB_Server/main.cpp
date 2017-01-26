#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok("/home/student/SharedMemory/", 1024);

    int shm_id;
    if((shm_id = shmget(key, 40000, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return EXIT_FAILURE;
    }

    void* shm;
    if((shm = shmat(shm_id, 0, 0)) == NULL) {
        perror("shmat");
        return EXIT_FAILURE;
    }

    std::cout << "Serwer rozpoczal prace!" << std::endl;

    char c;
    do {
        std::cout << "Wpisz 'q' i zatwierdz [enter] by zakonczyc dzialanie!" << std::endl;
        std::cin >> c;
    } while(c != 'q');

    shmdt(shm);
    return 0;
}
