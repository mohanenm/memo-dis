#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "threadHub.h"
#include "mem-hash.h"

#define OPERATIONS  2


dArray operations;
char* buffer;
queue* Workers;
hash* hashMap;
//Gets Operation and Creates workers able to do the task
void init(){
  FILE* fp;
  createDictionary(&operations, OPERATIONS);
  char* tempWord;
  int count =1;
  int c;
  tempWord = (char*)malloc( (sizeof(char)*count) + 1 );
  //reads ConfigFile
  fp = fopen("./src/config.txt", "r");
  //parses config
  while((c = getc(fp)) != EOF){
    if(c == '\n'){
      if(strcmp(tempWord, "Operation:") == 0){
        count = 1;
      }else{
        count =1;
        addWordToDictionary(&operations, tempWord);
      }
      if(strcmp(tempWord, "Buffer:") == 0){
        count = 1;
      }else{
        count =1;
        addWordToDictionary(&operations, tempWord);
      }
      free(tempWord);
      tempWord = (char*)malloc((sizeof(char)*count) + 1 );
    }else{
      tempWord[count-1] = c;
      count++;
      tempWord = realloc(tempWord, (sizeof(char)*count)+1);
    }
  }
  if(strcmp(operations.val[0].word, "File") == 0){
    buffer = (char*)malloc(sizeof(atoi(operations.val[1].word)));

  }

fclose(fp);
}

void startOperation(int workers, OPERATION op){
  pthread_t threads[workers];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  int rc;
  Workers = createQueue(workers);
  // worker initiliazed
  worker* tempWorker = malloc(sizeof(worker));
  //type of work initialized
  for(int i =0; i < workers; i++){
  // enqueue work in a queue
  // queue takes argument for threads
    enqueue(Workers, initWorker(tempWorker, op, i, workers, "./testFile.txt" ));
    //printf("%s",queueGet(Workers, i-1)->path);
  }
  for(int t = 0; t < workers; t++){
    //rc = pthread_create(&threads[t], &attr, FileJob, queueGet(hashMap->items[((uintptr_t)item)%7].data, t));
    printf("%d\n", queueGet(Workers, t)->tid);
  }
  DataItem* item = createDataItem(Workers);
  for(int t = 0; t < workers; t++){
    //rc = pthread_create(&threads[t], &attr, FileJob, queueGet(hashMap->items[((uintptr_t)item)%7].data, t));
    printf("%d\n", queueGet(Workers, t)->tid);
  }
  hashMap = createHashMap(7);
  //printf("%s\n", item->data->currentWorker->tid);
  Insert(item,hashMap);
  printf("Out of for loop\n" );
  free(tempWorker);
  printf("creating threads\n" );
  //THREADS ARE STARTED BUT FINISH AT DIFFERENT TIMES
  for(int t = 0; t < workers; t++){
    rc = pthread_create(&threads[t], &attr, FileJob, queueGet(hashMap->items[((uintptr_t)item)%7].data, t));
    //printf("%d\n", queueGet(hashMap->items[((uintptr_t)item)%7].data, t)->tid);
  }
  int working = 1;
  printf("Working... \n");
  while(working == 1){
    working = checkSignals(hashMap->items[((uintptr_t)item)%7].data);
  }
  printf("Outside While\n");
  printf("Workers size %d\n", Workers->size);
  printf("%ld\n", ((uintptr_t)item)%7);
  printf("%d\n", hashMap->items[((uintptr_t)item)%7].data->size);
  printf("Rebuilding file... \n");

}

void createDirectory(char* directoryName){

}
