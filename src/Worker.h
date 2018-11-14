#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct thread_t{
  long tid;
  OPERATION op;
}worker;



worker* initWorker(worker* temp, OPERATION* op, long tid){

}
