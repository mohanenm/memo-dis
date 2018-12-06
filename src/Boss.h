#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "threadHub.h"
#include "mem-hash.h"



void createDirectory(char* directoryName, dArray* directories, hash* hashMap, int size){
  printf("Inside create Directory\n");
  queue* directory = createQueue(size);
  setQueueName(directory, directoryName);
  addWordToDictionary(directories, directoryName);
  DataItem* tempItem = createDataItem(directory);
  Insert(tempItem, hashMap, directoryName);
}

void fileToDirectory(char* fileName, char* path, queue* q, char* folderName, int soq){
  worker* temp = malloc(sizeof(worker));
  OPERATION* op = createOp("file", 1);
  printf("Inside fileToDirectory\n");
  enqueue(q, initWorker(temp,op,getQueueLength(q),soq,path,fileName));
}
