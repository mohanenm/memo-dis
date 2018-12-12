#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "queueStruct.c"

typedef struct Dict
{
  char *word;
  int amount;
}Dict;

typedef struct DictionArray
{
  Dict* val;
  int size;
  int totalWords;
}dArray;

typedef struct commandLineArgs
{
  int windowSize;
  int wlength;
  int queueSize;
}ARGS;


extern int strComp(char *s, char *t); //returns -2 if not equal -1 if equal
void createDictionary(dArray *temp, int size);
void printDictionary(dArray diction, int windowSize);
void clearDictionary(dArray *diciton);
void addWordToDictionary(dArray *temp, char* word);
void clearQueue(queue* temp);
ARGS* commandLineParser(char* args[], int length);
void freeAll(dArray* dict, char* tempWord, queue* queue);
void sortDictionary(int n, dArray* input);
void removeItemFromDictionary(dArray* temp, char* word);
void addItemToDictionary(dArray* temp, char* word, int wlength);
int nextOpenWord(dArray* dict);

ARGS* commandLineParser(char* args[], int length)
{
  int windowSize = 10;
  int wlength = 6;
  int queueSize= 1000;
  char* memAddress;
  int checker =0;
  ARGS *arguments = (ARGS*)malloc(sizeof(ARGS));
  //printf("In args1");

    for(int i = 0; i < length; i++)
    {
      if(strComp(args[i], (char*)"-w")== -1)
	{
	  windowSize = atoi(args[i+1]);
	}
      if(strComp(args[i],(char*)"-l") == -1)
	{
	  wlength = atoi(args[i+1]);
	}

    }

    //printf("In args");
    arguments->windowSize = windowSize;
    arguments->queueSize = queueSize;
    arguments->wlength = wlength;
    return arguments;
}

void createDictionary(dArray *temp, int size)
{
  temp->val = (Dict*)malloc( (sizeof(char**) + 2*sizeof(int))* size );
  temp->size = size;
  temp->totalWords = -1;
  for(int i = 0; i < size; i++ )
    {
      temp->val[i].word = (char*)malloc(sizeof(char*));
      strcpy(temp->val[i].word, (char*)"\0");
      temp->val[i].amount = 0;
    }

}

void addWordToDictionary(dArray *temp, char* word)
{
  for(int i = 0; i < temp->size; i++)
  {
    if(strComp(temp->val[i].word, (char*)"\0") == -1 )
    {
      temp->val[i].word = (char*)malloc(sizeof(word));
      strCopy(temp->val[i].word, word);
      return;
    }
  }
}

void printDictionary(dArray diction, int windowSize)
{
  int pos=0;
  int highestVal = 0;
  for(int i = 0; i < windowSize; i++)
    {
      for (int j = 0; j < diction.size; j++)
	     {
	        if(diction.val[j].amount >= highestVal)
	        {
	           highestVal = diction.val[j].amount;
	           pos = j;
	        }
	     }
      if(diction.val[pos].amount >= 0)
	     {
         printf("%s:%d \t", diction.val[pos].word, highestVal);
         diction.val[pos].amount = -diction.val[pos].amount;
      }
      highestVal = 0;
    }
    for(int i = 0; i < diction.size; i++)
    {
      if(diction.val[i].amount < 0)
      {
        diction.val[i].amount = - diction.val[i].amount;
      }
    }
  printf("\n");
}

void clearDictionary(dArray *diction)
{
  for(int i = 0; i < diction->size; i++ )
    {
      free(diction->val[i].word);
      diction->val[i].amount = 0;
    }
    free(diction->val);
  //  free(diction);

}

int wordCheck(dArray *diction, char *word)
{
  for(int i = 0; i < diction->size; i++)
    {
      if(strcmp(diction->val[i].word, word) == 0)
	     {
	       return i;
       }
    }
  return -1;
}

void clearQueue(queue* temp)
{
  node* tempNode = temp->head;
  node* freeNode;
  free(temp->name);
  while(tempNode->currentWorker->tid != -2)
  {
    freeNode = tempNode;
    tempNode= tempNode->after;
    printf("freeing worker.\n");
    freeWorker(freeNode->currentWorker);
    free(freeNode);
  }
  //free(temp);
}


void freeAll(dArray* dict, char* tempWord, queue* queue)
{
  clearDictionary(dict);
  clearQueue(queue);
  free(tempWord);
}

void removeItemFromDictionary(dArray* temp, char* word)
{
  int position = -1;
  if((position = wordCheck(temp, word)) != -1)
  {
    --temp->val[position].amount;
    if(temp->val[position].amount == 0)
    {
      free(temp->val[position].word);
      temp->val[position].word = (char*)malloc(sizeof(char*));
      strcpy(temp->val[position].word, "\0");
    }
  }
}

int getValue(dArray* dict, char* key)
{
  for(int i = 0; i < dict->size; i++)
  {
    if(strcmp(dict->val[i].word, key) == 0)
    {
      return dict->val[i].amount;
    }
  }
  return -1;
}




int nextOpenWord(dArray* dict)
{
  for(int i = 0; i < dict->size; i++)
  {
    if(strcmp(dict->val[i].word, (char*)"\0") == 0)
    {
      return i;
    }
  }
  return dict->size;
}



void addItemToDictionary(dArray* temp, char* word, int wlength)
{
  int positionOpen = nextOpenWord(temp);
  int position = wordCheck(temp, word);
  if(position != -1)
  {
    ++temp->val[position].amount;
  }else{
        free(temp->val[positionOpen].word);
        temp->val[positionOpen].word = (char*)malloc(strlen(word)+1);
        strcpy(temp->val[positionOpen].word, word);
        temp->val[positionOpen].amount = 1;
      }
}
