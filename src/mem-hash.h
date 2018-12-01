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
hash* createHashMap(int size){
  hash* result = (hash*)malloc(sizeof(hash));
  result->size = size;
  result->items = (DataItem*)malloc(sizeof(DataItem)*size);

  for(int i = 0; i < size; i++){
    result->items[i].data = (queue*)malloc(sizeof(queue));
    result->items[i].key = -1;
    result->items[i].data = createQueue(1);
    result->items[i].next = (DataItem*)malloc(sizeof(DataItem));
    result->items[i].next = createNullItem();
  }

  return result;
}

void Insert(DataItem* item, hash* map){
  long key = (uintptr_t)item%map->size;
  if(map->items[key].key == -1){
    printf("%ld\n", key);
    copyDataNewHash(&map->items[key], item);
  }else{
    long temp = map->items[key].key;
    DataItem* tempItem = &map->items[key];
    while(temp != -1){
      temp = map->items[key].next->key;
      tempItem = tempItem->next;
    }

    copyDataExistingHash(tempItem, item);
  }
}

void copyDataNewHash(DataItem* old, DataItem* new){
  //old = (DataItem*)realloc(new, sizeof(DataItem*));
  //old->data = malloc( sizeof(queue)*new->data->size);
  old->data = new->data;
}

void copyDataExistingHash(DataItem* old, DataItem* new){
  old->next = (DataItem*)realloc(new, sizeof(DataItem*));
  //free(old->next);
  old->next->data = new->data;
}
