#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OPERATION{
  char* op;
}OPERATION;

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
  queue* returnQueue = (queue*)malloc(16*size);
  returnQueue->size = size;
  returnQueue->elements = 0;
  node* nullNode = (node*)malloc(sizeof(char*)+ sizeof(node*)*2);
  nullNode->currentWorker = createBlankWorker();
  nullNode->before = nullNode;
  nullNode->after = nullNode;
  returnQueue->head = nullNode;
  returnQueue->tail = nullNode;
  return returnQueue;
}

void enqueue(queue* queue, worker* ele)
{
  node* temp = (node*)malloc(sizeof(node*)*2 + sizeof(char*));
  node* nullNode = (node*)malloc(sizeof(node*)*2 + sizeof(char*));
  nullNode->currentWorker = createBlankWorker();
  temp->currentWorker = ele;
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
      if(queue->tail->currentWorker->tid ==-1)
	{
	  temp->before = queue->tail;
	  temp->after = nullNode;
    queue->tail->after = temp;
	  queue->tail = temp;
    queue->elements++;
	  return;
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
  while(tempNode->currentWorker->tid != -1)
  {
    counter+=1;
    tempNode = tempNode->after;
  }
  return counter;
}
