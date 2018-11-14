#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

#define OPERATIONS  2


dArray operations;
char* buffer;
//Gets Operation and Creates workers able to do the task
void init(){
  FILE* fp;
  createDictionary(&operations, OPERATIONS);
  char* tempWord;
  int count =1;
  int c;
  tempWord = (char*)malloc( (sizeof(char)*count) + 1 );
  //reads ConfigFile
  fp = fopen("./src/config.txt", "r");
  //parses config
  while((c = getc(fp)) != EOF){
    if(c == '\n'){
      if(strcmp(tempWord, "Operation:") == 0){
        count = 1;
      }else{
        count =1;
        addWordToDictionary(&operations, tempWord);
      }
      if(strcmp(tempWord, "Buffer:") == 0){
        count = 1;
      }else{
        count =1;
        addWordToDictionary(&operations, tempWord);
      }
      free(tempWord);
      tempWord = (char*)malloc((sizeof(char)*count) + 1 );
    }else{
      tempWord[count-1] = c;
      count++;
      tempWord = realloc(tempWord, (sizeof(char)*count)+1);
    }
  }
  if(strcmp(operations.val[0].word, "File") == 0){
    buffer = (char*)malloc(sizeof(atoi(operations.val[1].word)));

  }

fclose(fp);
}
