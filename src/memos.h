#include <stdio.h>
#include <string.h>
#include <queueStruct.h>
#include <mem-hash.h>
#include <folder.h>

typedef struct memo{

}memo;


//this method will be changing a memo and putting the new information into
//the directory is either a new memo or an overwrite to an old memo
void Put(folder* direct, memo* ptr ){

}

//returns the entire memo to be edited or just looked at.
//the folder name is the key to the specfic folder
//the key is the hash value accoiated with the memo in question
memo* Get(FOLDERNAME name, key prt){

}
