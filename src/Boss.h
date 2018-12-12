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
  OPERATION* op = createOp("put", 1);
  printf("Inside fileToDirectory\n");
  printf("Queue name: %s \t Path: %s \t SizeofQueue: %d\n", "test", path, soq);
  worker* temp2 = initWorker(temp,op,getQueueLength(q),soq,path,fileName);
  enqueue(q, temp2);
  threadHub(temp2,1);
}
