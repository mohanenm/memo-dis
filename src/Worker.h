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
  worker* temp = (worker*)malloc(sizeof(worker)); // CREATE EMPTY WORKER
  temp->tid =-1;
  temp->signal = -1;
  return temp;
}

worker* createNullWorker(){ // NULL WORKER IS WHAT WORK GETS ASSIGNED TO
  worker* temp = (worker*)malloc(sizeof(worker));
  temp->path = malloc(sizeof(char)+1);
  temp->tid =-2;
  temp->signal = -1;
  return temp;
}

// COPY VALUES OF ONE WORK TO ANOTHER
void copyWorker(worker* temp, worker* weezy){
  //printf("Within thread %d\n", weezy->tid);
  temp->tid = weezy->tid;
  temp->op = weezy->op;
  temp->signal = weezy->signal;
  temp->total = weezy->total;
  temp->path = malloc(sizeof(char)*strlen(weezy->path) + 1);
  strcpy(temp->path, weezy->path);
}
//TAKES STORAGE(STRING)
//CAST STORAGE SPACE FOR STRING
void copyStorageString(worker* temp, worker* weezy){
  temp->storage = malloc(sizeof(char)*strlen(((char*)weezy->storage))+1);
  strcpy(((char*)temp->storage), ((char*)weezy->storage));
}
//MAKES SURE ALL POINTERS INSIDE THE STRUCT ARE FREED
void freeWorker(worker* temp){
  free(temp->path);
  free(temp->storage);
  free(temp);
}
