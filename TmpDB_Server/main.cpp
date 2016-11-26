#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

typedef struct SharedMemoryItem{
    char str[256];
    int index;
    int size;
};

int main()
{
    int shm_id;
    const char path[40] = "/home/student/SharedMemory/";
    key_t key = ftok(path, 1024);
    if((shm_id = shmget(key, 40000, IPC_CREAT | 0666)) < 0){
        perror("shmget");
        return EXIT_FAILURE;
    }
     void* shm;
     if((shm = shmat(shm_id, 0, 0)) == NULL) { //wskaźnik do pamięci dzielonej
         perror("shmat");
         return EXIT_FAILURE;
     }
    SharedMemoryItem* item = new SharedMemoryItem;
    void* smPointer = shm;
    int i = 1;
    while(i <  5){
        item->index = i;
        cout << "Podaj wiadomosc: ";
        cin >> item->str;
        item->size = sizeof(*item);

        memcpy(smPointer, item, item->size);

        memcpy(item, smPointer, item->size);
        cout << item->index << ", rozmiar: " << item->size << endl;
        smPointer += item->size;
        cout << smPointer << endl;
        i++;
    }
    i = 1;
    smPointer = shm;
    while(i++ <  5){
        sleep(1);
        memcpy((void*)item, smPointer, ((SharedMemoryItem*)smPointer)->size);
        cout << item->index << ". " << item->str<< endl;
        smPointer += item->size;
    }
    delete item;
    shmdt(shm);
    return 0;
}
