#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct DataItem {
   queue* data;
   long key;
   struct DataItem* next;
}DataItem;

typedef struct Hash_Map{
  DataItem** items;
  int size;
}hash;


void copyDataNewHash(DataItem* old, DataItem* new);
void copyDataExistingHash(DataItem* old, DataItem* new);

DataItem* createNullItem(){
  DataItem* temp = (DataItem*)malloc(sizeof(DataItem));
  temp->key = -1;
  temp->data = (queue*)malloc(sizeof(queue));
  temp->data = createQueue(1);
  return temp;

}

DataItem* createDataItem( queue* data){
  DataItem* item = malloc(sizeof(DataItem));
  item->data = data;
  return item;
}
hash* createHashMap(int size){
  hash* result = (hash*)malloc(sizeof(hash));
  result->size = size;
  result->items = malloc(sizeof(DataItem)*size);
  for(int i = 0; i < size; i++){
    result->items[i] = malloc(sizeof(DataItem));
  }

  for(int i = 0; i < size; i++){
    result->items[i]->key = -1;
    result->items[i]->data = malloc(sizeof(queue));
    result->items[i]->data = createQueue(1);
    result->items[i]->next = malloc(sizeof(DataItem));
    result->items[i]->next = createNullItem();
  }

  return result;
}

void Insert(DataItem* item, hash* tempMap,char* tmpKey){
  long key = tmpKey[0]%(tempMap->size);
  if(tempMap->items[key]->key == -1){
    printf("%ld\n", key);
    item->key = key;
    setQueueName(item->data, tmpKey);
    copyDataNewHash(tempMap->items[key], item);
  }else{
    long temp = tempMap->items[key]->key;
    DataItem* tempItem = tempMap->items[key];
    while(temp != -1){
      temp = tempMap->items[key]->next->key;
      tempItem = tempItem->next;
    }

    copyDataExistingHash(tempItem, item);
  }
}

queue* getHash(char* key, hash* tempMap){
  long key2 = key[0]%(tempMap->size);
  printf("Current key: %ld \t Current name: %s\n", key2, key);
  if(tempMap->items[key2]->key != -1){
    long temp = tempMap->items[key2]->key;
    queue* tempItem = tempMap->items[key2]->data;
    while(temp != -1){
      if(strcmp(key,tempItem->name) == 0){
        printf("Within tempItem return. Queue name: %s\n", tempItem->name);
        return tempItem;
      }
      temp = tempMap->items[key2]->next->key;
      tempItem = tempMap->items[key2]->next->data;
    }
  }else{
    printf("In Else\n");
    queue* noQueue = createQueue(1);
    noQueue->name = malloc(sizeof(char)*strlen("none")+1);
    strcpy(noQueue->name,"none");
    return noQueue;
  }
}

void copyDataNewHash(DataItem* old, DataItem* temp){
  old->data = temp->data;
  old->key = temp->key;
  printf("In new hash\n");
}

void copyDataExistingHash(DataItem* old, DataItem* new){
  old->next->data = createQueue(new->data->size);
  printf("In existing hash\n");
  for(int i = 0; i< new->data->size; i++){
    enqueue(old->next->data, queueGet(new->data,i));
  }
}

void freeHash(hash* tempMap){
  for(int i = 0; i < tempMap->size; i++){
    long temp = tempMap->items[i]->key;
    DataItem* tempItem = tempMap->items[i];
    DataItem* tempItem2 = malloc(sizeof(DataItem));
    while(temp != -1){
      temp = tempMap->items[i]->next->key;
      //tempItem2 = malloc(sizeof(DataItem));
      tempItem2->data = malloc(sizeof(queue));
      tempItem2->data = tempItem->data;
      tempItem2 = tempItem;
      printf("Freeing. %s\n", tempItem2->data->name);
      clearQueue(tempItem2->data);
      tempItem = tempItem->next;
      //free(tempItem2);
    }
    free(tempMap->items[i]);
  }
  //free(tempMap->items);
  free(tempMap);
}
