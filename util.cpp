//Richard Matejka - 1221297844

#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, double *key, char* key2)
{
    int  returnV;

    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop")==0) return 1;
    if (strcmp(Word, "Maximum")==0) return 1;
    if (strcmp(Word, "Minimum")==0) return 1;

    if (strcmp(Word, "PreOrder")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "InOrder")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "PostOrder")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "Read")==0){
        returnV = fscanf(stdin, "%s", key2);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "Write")==0){
        returnV = fscanf(stdin, "%s", key2);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "Search")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "Insert")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "Delete")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "PrintList")==0){
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }

    return 0;
}
