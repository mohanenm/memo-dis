#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct worker{
  long tid;
  OPERATION op;
  int signal; //1 means queued, 2 means running, 3 means finished operation
}worker;

FILE* fileWork(worker* worker, int start, int end){

}

worker* initWorker(worker* temp, OPERATION op, long tid){
  temp->op = op;
  printf("Init\n");
  temp->tid = tid;
  temp->signal = 1;
}

void startWorker(worker* temp, int start, int end){
  if(strcmp(temp->op.op, "File") == 0){
    temp->signal = 2;
    //temp->piece = fileWork(temp, start, end);
  }
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
