#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//this file is where we defined the operations that can be preformed



pthread_mutex_t lock;

//idea for dividing up a text file job
//TAKE A LETTER AND DELETE IT
//TODO ADD IF STATEMENT AND ADD VALUE TO WORKER
void *FileJob(void* temp)
{
    pthread_mutex_lock(&lock);
    //printf("\nCopying worker %d\n\n", (((worker*)temp)->tid));
    worker* weezy = malloc(sizeof(worker));
    copyWorker(weezy, (worker*)temp);
    FILE* fp = fopen(weezy->path , "r");
    int counter = 0;
    int pos = 0;
    char* storage = malloc(sizeof(char) + 1 );
    int c = 0;
    while((c = getc(fp)) != EOF){
      if(counter%weezy->total == weezy->tid){
        storage[pos] = c;
        pos+=1;
        char* tempStorage = malloc(sizeof(char)*pos + 1);
        strcpy(tempStorage, storage);
        free(storage);
        storage = malloc(sizeof(char)*pos + 1);
        strcpy(storage,tempStorage);
        free(tempStorage);
      }

      counter+=1;


    }
    //printf("Characters Caught %d\n", strlen(storage) );
    weezy->storage = malloc(sizeof(char)* strlen(storage) + 1);
    //printf("Storage: %s from thread %d \n", storage, weezy->tid);
    strcpy ((char*)weezy->storage,storage);
    //printf("AFTER Thread\n");
    copyWorker(weezy, ((worker*)temp));
    copyStorageString(((worker*)temp),weezy);
    freeWorker(weezy);
    ((worker*)temp)->signal=3;
    fclose(fp);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
