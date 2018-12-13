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
    if(((worker*)temp)->op->lock == 1){
      pthread_mutex_lock(&lock);
    }
    //printf("Inside FileJob.%s\n", ((worker*)temp)->path);
    //
    worker* weezy = malloc(sizeof(worker));
    weezy->op = malloc(sizeof(OPERATION));
    weezy->op->op = malloc(sizeof(char)+1);
    printf("\nCopyied worker %ld\n\n", (((worker*)temp)->tid));
    copyWorker(weezy, (worker*)temp);
    FILE* fp = fopen(((worker*)temp)->path , "r");
    int pos = 0;
    char* storage = malloc(sizeof(char));
    int c = 0;
    while((c = getc(fp)) != EOF){
        storage[pos] = c;
        pos+=1;
        storage = realloc(storage, sizeof(char)*pos + 1);

    }
    pos=0;
    weezy->storage = (char*)malloc(sizeof(char)*strlen(storage)+ 1);
    //printf("Storage: %s from thread %ld \n", storage, weezy->tid);
    strcpy ((char*)weezy->storage,storage);
    //printf("AFTER Thread\n");
    copyStorageString(((worker*)temp),weezy);
    //freeWorker(weezy);
    //free(storage);
    //printf("Inside thread %s\n", (char*)((worker*)temp)->storage);
    ((worker*)temp)->signal=3;
    fclose(fp);
    if(((worker*)temp)->op->lock == 1){
      pthread_mutex_unlock(&lock);
      ((worker*)temp)->op->lock = 0;
    }
    pthread_exit(NULL);
}



void threadHub(worker* thread,int size){
  pthread_t threads[size];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  int rc;
  void* status;

    if(strcmp(thread->op->op,"put") ==0 ){
      printf("thread operation is put.\n ");
      thread->op->lock = 1;
      rc = pthread_create(&threads[0], &attr, FileJob, thread);
    }
    int count =0;
    pthread_join(threads[0], &status);
    while(thread->signal != 3){
      count+=1;
    }

  pthread_attr_destroy(&attr);


}
