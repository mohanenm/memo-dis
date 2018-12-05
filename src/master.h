#include "Boss.h"
#include <unistd.h>

hash* hashMap;
dArray* directories;


//for demo purposes
void createWindow(char* arguments){
  hashMap = createHashMap(1);
  sleep(5);
  char* source = "gnome-terminal  -x sh -c 'cd ./Documents/Code/memo-system/src; ./test.o -m ";
  char* temp = malloc(strlen(source)*sizeof(char) + strlen(arguments));
  strcpy(temp, source);
  char* commands = strcat(temp, arguments);
  int exit_status = system(commands);
}
void put(char* folderName, char* fileName){

}
