#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

#define OPERATIONS  2

typedef struct OPERATION{
  char* op;
}OPERATION;
dArray operations;

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
      if(strcmp(tempWord, "Operations:") == 0){
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
  printf("%s\n", operations.val[0].word);
fclose(fp);
}
