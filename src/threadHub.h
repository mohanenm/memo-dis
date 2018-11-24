#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//this file is where we defined the operations that can be preformed

struct thread_data {
    worker* worker;
    void* work;
}thread_data_t;

//idea for dividing up a text file job
void *FileJob(char* path, worker* worker)
{
    FILE* fp = fopen(path , "r");
    int counter = 0;
    char* storage = malloc(sizeof(char));
    while((c = getc(fp)) != EOF){

      if(count%worker->total == worker->tid){
        //storage = realloc();
      }

      counter+=1;

    }

    pthread_exit(NULL);
}
