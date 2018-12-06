#include "Boss.h"
#include <unistd.h>


typedef struct masterController{
  int folders;
  int FIF; //files in folders
  hash* director;
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

}

void put(char* folderName, char* fileName, char* path){
  if(wordCheck(controller->directories, folderName) == -1){
    //addWordToDictionary(controller->directoies, fileName);
    createDirectory(folderName, controller->directories, controller->director, controller->FIF);
    printf("%s\n",controller->directories->val[0].word);
    if(strcmp(path,"na")!= 0){
      queue* tempQ = malloc(sizeof(queue));
      tempQ = getHash(folderName,controller->director);
      fileToDirectory(fileName,path,tempQ,folderName,getHash(folderName,controller->director)->size);
      //printf("%s\n",(char*)(getWorker(getHash(folderName,controller->director), fileName)->storage));
    }else{
      printf("File already exists.\n");
    }

  }
}

void get_all(){
  //printf("%s\n", getHash("dbangz",controller->director)->name);
}

void done(){
  freeHash(controller->director);
  clearDictionary(controller->directories);
  free(controller);
}
