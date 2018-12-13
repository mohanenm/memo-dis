#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "threadHub.h"
#include "mem-hash.h"



void createDirectory(char* directoryName, dArray* directories, hash* hashMap, int size){
  queue* directory = createQueue(size);
  setQueueName(directory, directoryName);
  addWordToDictionary(directories, directoryName);
  DataItem* tempItem = createDataItem(directory);
  Insert(tempItem, hashMap, directoryName);
}

void fileToDirectory(char* fileName, char* path, queue* q, char* folderName, int soq){
  worker* temp = createBlankWorker();
  OPERATION* op = createOp("put", 1);
  worker* temp2 = initWorker(temp,op,soq,soq,path,fileName);
  enqueue(q, temp2);
  threadHub(getWorker(q,fileName),1);
}

char* getFile(char* fileName, queue* q){
  queue* tempQ = createQueue(q->size);
  node* tempNode = q->head;
  char* result;
  while(tempNode->currentWorker->tid != -2){
    if(strcmp(tempNode->currentWorker->name, fileName) != 0){
      enqueue(tempQ, tempNode->currentWorker);
    }else{
      result = malloc(sizeof(char)*strlen((char*)tempNode->currentWorker->storage));
      strcpy(result,(char*)tempNode->currentWorker->storage);
    }
  }
  return result;
}
