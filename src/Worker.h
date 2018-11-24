#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct worker{
  long tid;
  OPERATION op;
  int signal; //1 means queued, 2 means running, 3 means finished operation
  int total; //total workers in a queue
  char* path;
  void* storage;
}worker;

worker* initWorker(worker* temp, OPERATION op, long tid,int total,char* path){
  temp->op = op;
  temp->tid = tid;
  temp->signal = 1;
  temp->total = total;
  temp->path = malloc(sizeof(char)*strlen(path));
  //printf("%s", path);
  strcpy(temp->path, path);
  return temp;
}


worker* createBlankWorker(){
  worker* temp = (worker*)malloc(sizeof(worker));
  printf("Blank");
  temp->tid =-1;
  temp->signal = -1;
  return temp;
}

worker* createNullWorker(){
  worker* temp = (worker*)malloc(sizeof(worker));
  temp->path = malloc(sizeof(char)+1);
  temp->tid =-2;
  temp->signal = -1;
  return temp;
}

void copyWorker(worker* temp, worker* weezy){
  temp->tid = weezy->tid;
  temp->op = weezy->op;
  temp->signal = weezy->signal;
  temp->total = weezy->total;
  free(temp->path);
  temp->path = malloc(sizeof(char)*strlen(weezy->path) + 1);
  strcpy(temp->path, weezy->path);
}

void copyStorageString(worker* temp, worker* weezy){
  
}

void freeWorker(worker* temp){
  free(temp->path);
  free(temp->storage);
  free(temp);
}
