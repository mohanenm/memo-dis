#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "threadHub.h"

#define OPERATIONS  2


dArray operations;
char* buffer;
queue* Workers;
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
  worker* tempWorker = malloc(sizeof(worker));
  for(int i =0; i < workers; i++){
    enqueue(Workers, initWorker(tempWorker, op, i, workers, "./testFile.txt" ));
    //printf("%s",queueGet(Workers, i-1)->path);
  }
  printf("Out of for loop\n" );
  free(tempWorker);
  printf("creating threads\n" );
  for(int t = 0; t < workers; t++){
    rc = pthread_create(&threads[t], &attr, FileJob, queueGet(Workers, t));
  }
  int working = 1;
  printf("Working... \n");
  while(working == 1){
    float av = 0.0;
    for(int t = 0; t < workers; t++){
      av += queueGet(Workers, t)->signal;
      }
    if(av/7 == 3.0){
      working = 0;
    }
  }
  printf("Outside While\n");
  //TODO
  printf("Rebuilding file... \n");

}
