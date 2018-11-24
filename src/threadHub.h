#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//this file is where we defined the operations that can be preformed



pthread_mutex_t lock;

//idea for dividing up a text file job
void *FileJob(void* temp)
{
    pthread_mutex_lock(&lock);
    worker* weezy = copyWorker((worker*)temp);
    FILE* fp = fopen(weezy->path , "r");
    int counter = 0;
    char* storage = malloc(sizeof(char));
    int c = 0;
    while((c = getc(fp)) != EOF){

      if(counter%weezy->total == weezy->tid){
        storage[counter] = c;
        counter+=1;
        char* tempStorage = malloc(sizeof(char)*counter + 1);
        strcpy(tempStorage, storage);
        storage = realloc(storage, sizeof(char)*counter);
        strcpy(storage,tempStorage);
        free(tempStorage);
      }

      counter+=1;

    }

    weezy->storage = (char*)storage;
    pthread_mutex_unlock(&lock);
    ((worker*)temp)->signal=3;
    pthread_exit(NULL);
}
