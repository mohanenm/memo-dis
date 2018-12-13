#include "Boss.h"
#include <unistd.h>


typedef struct masterController{
  int folders;
  int FIF; //files in folders
  hash* director;
  queue* gotFiles; //all the files that have been got are equeued in here
  dArray* directories;
}master;

master* controller;

void init(int folders, int files){
  controller = malloc(sizeof(master));
  controller->directories = malloc(sizeof(dArray));
  createDictionary(controller->directories,folders);
  controller->director = malloc(sizeof(hash));
  controller->director = createHashMap(folders);
  controller->FIF = files;
  controller->folders = folders;
  controller->gotFiles = malloc(sizeof(queue));
  controller->gotFiles = createQueue(folders*files);

}

void put(char* folderName, char* fileName, char* path){
  if(wordCheck(controller->directories, folderName) == -1){
    createDirectory(folderName, controller->directories, controller->director, controller->FIF);
    printf("%s\n",controller->directories->val[0].word);
    if(strcmp(path,"na")!= 0){
      fileToDirectory(fileName,path,getHash(folderName, controller->director),folderName,getHash(folderName, controller->director)->size);
      worker* tempWorker = getWorker(getHash(folderName, controller->director),fileName);
      printf("\nResult: %s\n", tempWorker->name);
    }else{
      printf("File already exists.\n");
    }
  }
}

void get(char* folderName, char* fileName){
  char* result = getFile(fileName, getHash(folderName, controller->director));
  printf("The result is: %s", result);
}

void read_t(char* folderName, char* fileName){
  queue* q = getHash(folderName, controller->director);
  worker* file = getWorker(q, fileName);
  printf("File is: \n%s\n", (char*)file->storage);
}

void get_all(){
  //printf("\n%s\n",(char*)(getWorker(getHash("testFolder",controller->director),"testFile")->storage));
}

void done(){
  freeHash(controller->director);
  clearDictionary(controller->directories);
  clearQueue(controller->gotFiles);
  free(controller);
}
