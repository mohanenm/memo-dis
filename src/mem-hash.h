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
  DataItem* items;
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
  item->data = createQueue(data->size);
  for(int i = 0; i < data->size; i++){
    enqueue(item->data, queueGet(data, i));
  }
  return item;
}
hash* createHashtempMap(int size){
  hash* result = (hash*)malloc(sizeof(hash));
  result->size = size;
  result->items = (DataItem*)malloc(sizeof(DataItem)*size);

  for(int i = 0; i < size; i++){
    result->items[i].key = -1;
    result->items[i].data = malloc(sizeof(queue));
    result->items[i].next = (DataItem*)malloc(sizeof(DataItem));
    result->items[i].next = createNullItem();
  }

  return result;
}

void Insert(DataItem* item, hash* tempMap,char* tmpKey){
  long key = tmpKey[0]%tempMap->size;
  if(tempMap->items[key].key == -1){
    printf("%ld\n", key);
    item->key = key;
    setQueueName(item->data, tmpKey);
    copyDataNewHash(&tempMap->items[key], item);
  }else{
    long temp = tempMap->items[key].key;
    DataItem* tempItem = &tempMap->items[key];
    while(temp != -1){
      temp = tempMap->items[key].next->key;
      tempItem = tempItem->next;
    }

    copyDataExistingHash(tempItem, item);
  }
}

queue* getHash(char* key, hash* temptempMap){
  long key2 = key[0]%tempMap->size;
  printf("Current key: %ld \t Current name: %s\n", key2, key);
  if(tempMap->items[key2].key != -1){
    long temp = tempMap->items[key2].key;
    DataItem* tempItem = tempMap->items[key2];
    while(temp != -1){
      if(strcmp(key,tempItem->data->name) == 0){
        printf("Within tempItem return. Queue name: %s\n", tempItem->data->name);
        return tempItem->data;
      }
      temp = tempMap->items[key2].next->key;
      tempItem = tempItem->next;
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
  old->data = createQueue(temp->data->size);
  setQueueName(old->data, temp->data->name);
  old->key = temp->key;
  printf("In new hash\n");
  for(int i = 0; i< temp->data->size; i++){
    enqueue(old->data, queueGet(temp->data,i));
  }
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
    long temp = tempMap->items[i].key;
    DataItem* tempItem = &tempMap->items[i];
    DataItem* tempItem2;
    while(temp != -1){
      temp = tempMap->items[i].next->key;
      tempItem2 = tempItem->next;
      clearQueue(tempItem->data);
      free(tempItem);
      tempItem = tempItem2;
      free(tempItem2);
    }
  }
  free(tempMap);
}
