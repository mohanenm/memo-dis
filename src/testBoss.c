#include "./Headers/master.h"
#include <unistd.h>
#include <stdlib.h>

char* inputHandler(char* buffer);

void main(int argc, char *args[]){
  init(4,2);
  int wordPos =0;
  int c = 0;
  char* buffer;
  printf("Enter a command(put, get, read, or stop to exit)\n");
  char* command = (char*)inputHandler(buffer);
  while(strcmp(command,"stop") != 0){
    if(strcmp(command,"put") == 0){
      printf("Enter a folder name.\n");
      char* folderName = (char*)inputHandler(buffer);
      printf("Enter a file name.\n");
      char* fileName = (char*)inputHandler(buffer);
      printf("Enter a path to the file.\n");
      char* path = (char*)inputHandler(buffer);
      put(folderName,fileName,path);
      get_all();
      free(path);
      free(fileName);
      free(folderName);
    }
    else if(strcmp(command,"get") == 0){
      printf("Enter a folder name.\n");
      char* folderName = (char*)inputHandler(buffer);
      printf("Enter a file name.\n");
      char* fileName = (char*)inputHandler(buffer);
      get(folderName,fileName);
      free(fileName);
      free(folderName);
    }
    else if(strcmp(command,"read") == 0){
      printf("Enter a folder name.\n");
      char* folderName = (char*)inputHandler(buffer);
      printf("Enter a file name.\n");
      char* fileName = (char*)inputHandler(buffer);
      read_t(folderName,fileName);
      free(fileName);
      free(folderName);
    }
    printf("Enter a command(put, get, read, or stop to exit)\n");
    command = (char*)inputHandler(buffer);

  }
  free(buffer);
   done();
}




char* inputHandler(char* buffer){
  int wordPos =0;
  int c = 0;
  buffer = malloc(sizeof(128));
  while((c = getchar()) != '\n'){
    buffer[wordPos] = c;
    wordPos+=1;
  }
  return buffer;
}
