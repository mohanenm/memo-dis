#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OPERATION{
  char* op;
  int lock; //either 1 or 0, 1 means locked 0 means not locked.
}OPERATION;

//SIMPLE A STRUCT WE CAN PASS A STRING INTO.
// TODO SPECIFY THE ARGUMENTS FOR THE OPERATION RATHER THAN PUTTING EVERYTHING IN WORKER
OPERATION* createOp(char* op, int lock){
  OPERATION* returnOp = malloc(sizeof(OPERATION));
  returnOp->op = malloc(sizeof(char)*strlen(op));
  strcpy(returnOp->op, op);
  returnOp->lock = lock;
  return returnOp;
}
#include "Worker.h"
//to make a array of char arrays with out having to use multi
//dimensional array
typedef struct string
{
  char *word;
}string;

typedef struct stringArray
{
  string *words;
  int size;
}stringArray;

typedef struct node
{
  struct node* before;
  worker* currentWorker;
  struct node* after;
}node;


typedef struct queue
{
  node* head;
  node* tail;
  char* name;
  int size;
  int elements;
}queue;

stringArray* getAllElements(queue* temp);
void createStringArray(stringArray *i, int size);
void addElement(stringArray *i, char *word);
void strCopy(char *s, char *t);
int strComp(char *s, char *t);
void enqueue(queue* temp, worker* ele);
worker* queueGet(queue* temp, int index);
queue* createQueue(int size);
node* dequeue(queue* temp);
int getQueueLength(queue* tempQ);

//copies string t onto string s
void strCopy(char *s, char *t)
{
  while(*s++ = *t++)
   ;
}// rewrote from a solution https://clc-wiki.net/wiki/K%26R2_solutions

int strComp(char *s, char *t)
{
  //s = (char*)realloc(s,strlen(t)+1);
  for(; *s == *t; s++, t++)
    {
      if(*s == '\0')
	     return -1;
    }
  return -2;
}// rewrote parts from https://clc-wiki.net/wiki/K%26R2_solutions

queue* createQueue(int size)
{
  queue* returnQueue = (queue*)malloc(sizeof(queue));
  returnQueue->size = size;
  returnQueue->elements = 0;
  returnQueue->name = malloc(sizeof(char)*4 + 1);
  strcpy(returnQueue->name,"none");
  node* nullNode = (node*)malloc(sizeof(node));
  nullNode->currentWorker = createNullWorker();
  nullNode->before = nullNode;
  nullNode->after = nullNode;
  returnQueue->head = nullNode;
  returnQueue->tail = nullNode;
  return returnQueue;
}

void setQueueName(queue* q, char* name){
  q->name = malloc(sizeof(char)*strlen(name)+1);
  strcpy(q->name,name);
}

void enqueue(queue* queue, worker* ele)
{
  node* temp = (node*)malloc(sizeof(node));
  node* nullNode = (node*)malloc(sizeof(node));
  nullNode->currentWorker = malloc(sizeof(worker));
  nullNode->currentWorker->path = malloc(sizeof(char)+1);
  nullNode->currentWorker->name = malloc(sizeof(char)+1);
  copyWorker(nullNode->currentWorker, createNullWorker());
  temp->currentWorker = malloc(sizeof(worker));
  temp->currentWorker->path = malloc(sizeof(char)+1);
  temp->currentWorker->name = malloc(sizeof(char)+1);
  copyWorker(temp->currentWorker, ele);
  if(queue->elements == 0)
    {
      temp->before = nullNode;
      temp->after = nullNode;
      queue->head = temp;
      queue->elements += 1;
      return;
    }
  else if(queue->elements < queue->size)
    {
      if(queue->tail->currentWorker->tid != -2)
	{
    temp->before = queue->tail;
	  temp->after = nullNode;
    queue->tail->after = temp;
	  queue->tail = temp;
    queue->elements++;
	}else
	{
	  temp->before = queue->head;
	  temp->after = nullNode;
    queue->head->after = temp;
	  queue->tail = temp;
    queue->elements++;
	}

    }

}

node* dequeue(queue* temp)
{
  node* returnNode = (node*) malloc(sizeof(node*));
  returnNode = temp->head;
  temp->head = temp->head->after;
  temp->elements -= 1;

  return returnNode;
}


worker* queueGet(queue* temp, int index)
{
  node* tempNode = temp->head;
  for(int i =0; i < index; i++)
  {
    tempNode = tempNode->after;
  }
  return tempNode->currentWorker;
}

int getQueueLength(queue* tempQ)
{
  node* tempNode = tempQ->head;
  int counter = 0;
  while(tempNode->currentWorker->tid != -2)
  {
    counter+=1;
    tempNode = tempNode->after;
  }
  return counter;
}

int checkSignals(queue* tempQ){
  node* tempNode = tempQ->head;
  int total = tempQ->head->currentWorker->total;
  float average = 0.0;
  while(tempNode->currentWorker->tid != -2)
  {
    average += tempNode->currentWorker->signal;
    tempNode = tempNode->after;
  }
  if(average/total == 3){
    return 0;
  }else{
    return 1;
  }
}

worker* getWorker(queue* q, char* name){
  node* tempNode = q->head;
  int counter = 0;
  printf("in worker");
  printf("QueueName: %s", q->name);
  while( strcmp(name, tempNode->currentWorker->name) != 0)
  {
    printf("Name: %s", tempNode->currentWorker->name);
    if(tempNode->currentWorker->tid == -2){
      return tempNode->currentWorker;
    }
    tempNode = tempNode->after;
  }
  return tempNode->currentWorker;
}
