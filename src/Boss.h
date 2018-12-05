#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "threadHub.h"
#include "mem-hash.h"

#define OPERATIONS  2



void createDirectory(char* directoryName, dArray* directoies, hash* hashMap, int size){
  printf("Inside create Directory\n");
  queue* directory = createQueue(size);
  addWordToDictionary(directoies, directoryName);
  DataItem* tempItem = createDataItem(directory);
  Insert(tempItem, hashMap, directoryName);
}
