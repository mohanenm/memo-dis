#include <stdio.h>
#include <string.h>
#include <queueStruct.h>
#include <mem-hash.h>

typedef struct SYMBOl{
  unsigned int s;
}SYMBOl;

typedef struct FOLDERNAME{
  SYMBOL S;
  unsigned long X[3];
}FOLDERNAME;

typedef struct folder{
  queue* q;
}folder;
