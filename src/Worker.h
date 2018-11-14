#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct worker{
  long tid;
  OPERATION op;
  int signal;
}worker;


worker* initWorker(worker* temp, OPERATION op, long tid){
  temp->op = op;
  temp->tid
}

void fileWork(worker* ){

}

worker* createBlankWorker(){
  worker* temp = (worker*)malloc(sizeof(worker));
  temp->tid =-1;
  temp->signal = -1;
  return temp;
}
