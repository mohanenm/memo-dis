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
  temp->tid =-2;
  temp->signal = -1;
  return temp;
}

worker* copyWorker(worker* weezy){
  worker* temp = malloc(sizeof(worker));
  temp->tid = weezy->tid;
  temp->op = weezy->op;
  temp->signal = weezy->signal;
  temp->total = weezy->total;
  temp->storage = weezy->storage;
  return temp;
}
