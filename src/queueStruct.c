#include "queueStruct.h"



void createStringArray(stringArray *currentArray, int size)
{

  currentArray->words = (string*)malloc(sizeof(char*) * size);
  currentArray->size = size;
  for(int i = 0; i < size; i++)
  {
    currentArray->words[i].word = (char*) malloc(sizeof(char) * sizeof("\0"));
    strCopy(currentArray->words->word, (char*)"\0");
  }

}

void addElement(stringArray *array, char *replacement)
{
  char clear[128]= {"\0"};
  for(int i = 0; i < array->size; i++)
    {
      if(strComp(array->words[i].word,(char*) " ") == -1)
	{
	  array->words[i].word = (char*)malloc(sizeof(replacement));
	  strCopy(array->words[i].word, clear);
	  strCopy(array->words[i].word, replacement);
	  return;
	}
    }

  for(int i = 0; i < array->size; i++)
    {
      if(i+1 < array->size)
      {
	strCopy(array->words[i].word, clear);
	strCopy(array->words[i].word, array->words[i+1].word);
      }else
	{
	  strCopy(array->words[i].word, replacement);
	}
    }

}

char* getValstrArr(stringArray *arr, int index)
{
  return arr->words[index].word;
}
