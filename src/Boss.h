#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "threadHub.h"
#include "mem-hash.h"

#define OPERATIONS  2


dArray directories;
queue* Workers;
//Gets Operation and Creates workers able to do the task
// void init(int size){
//   FILE* fp;
//   createDictionary(&directoies, size);
//   char* tempWord;
//   int count =1;
//   int c;
//   tempWord = (char*)malloc( (sizeof(char)*count) + 1 );
//   //reads ConfigFile
//   fp = fopen("./src/config.txt", "r");
//   //parses config
//   while((c = getc(fp)) != EOF){
//     if(c == '\n'){
//       if(strcmp(tempWord, "Directories:") == 0){
//         count = 1;
//       }else{
//         count =1;
//         addWordToDictionary(&directoies, tempWord);
//       }
//       free(tempWord);
//       tempWord = (char*)malloc((sizeof(char)*count) + 1 );
//     }else{
//       tempWord[count-1] = c;
//       count++;
//       tempWord = realloc(tempWord, (sizeof(char)*count)+1);
//     }
//   }
// fclose(fp);
// }

// void startOperation(int workers, OPERATION op){
//   pthread_t threads[workers];
//   pthread_attr_t attr;
//   pthread_attr_init(&attr);
//   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//   int rc;
//   Workers = createQueue(workers);
//   // worker initiliazed
//   worker* tempWorker = malloc(sizeof(worker));
//   //type of work initialized
//   for(int i =0; i < workers; i++){
//   // enqueue work in a queue
//   // queue takes argument for threads
//     enqueue(Workers, initWorker(tempWorker, op, i, workers, "./testFile.txt" ));
//     //printf("%s",queueGet(Workers, i-1)->path);
//   }
//   DataItem* item = createDataItem(Workers);
//   hashMap = createHashMap(7);
//   //printf("%s\n", item->data->currentWorker->tid);
//   Insert(item,hashMap);
//   printf("Out of for loop\n" );
//   free(tempWorker);
//   printf("creating threads\n" );
//   //THREADS ARE STARTED BUT FINISH AT DIFFERENT TIMES
//   for(int t = 0; t < workers; t++){
//     rc = pthread_create(&threads[t], &attr, FileJob, queueGet(hashMap->items[((uintptr_t)item)%7].data, t));
//     freeWorker(dequeue(Workers)->currentWorker);
//   }
//
//
//   int working = 1;
//   printf("Working... \n");
//   while(working == 1){
//     working = checkSignals(hashMap->items[((uintptr_t)item)%7].data);
//   }
//   printf("Outside While\n");
//   printf("Workers size %d\n", Workers->size);
//   printf("%ld\n", ((uintptr_t)item)%7);
//   printf("%d\n", hashMap->items[((uintptr_t)item)%7].data->size);
//   printf("Rebuilding file... \n");
//
// }

void createDirectory(char* directoryName, int size, dArray* directoies, hash* hashMap){
  queue* directory = createQueue(size);
  addWordToDictionary(directoies, directoryName);
  DataItem* tempItem = createDataItem(directory);
  Insert(tempItem, hashMap,directoryName);
}
