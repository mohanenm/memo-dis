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

void put(char* folderName, char* fileName){
  if(wordCheck(controller->directories, folderName) == -1){
    createDirectory(folderName, controller->directories, controller->director, controller->FIF);
    printDictionary(*controller->directories,4);
  }
}
