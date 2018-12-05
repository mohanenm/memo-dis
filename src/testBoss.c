#include "master.h"
#include <unistd.h>
#include <stdlib.h>

hash* hashMap;
void main(int argc, char *args[]){
//  init();
  //OPERATION* op = createOp((char*)"File");
  //startOperation(7, *op);
  long unsigned int address;
  ARGS* arguments = commandLineParser(args,argc);
  if(arguments->checker == 1){
    sscanf(arguments->memAddress, "%lx", &address);
    hashMap = (hash*)(uintptr_t)address;
    printf("%lx\n", (uintptr_t)hashMap);
  }else{
    printf("no hashMap\n");
  }
  char strMemAddress[16];
  ultoa (address,strMemAddress,16);
  char* temp = malloc(sizeof(char)*strlen(strMemAddress)+5);
  strcpy(temp, strMemAddress);
  strcat(temp, " ;'");
  createWindow(temp);
  //sleep(4);
}
