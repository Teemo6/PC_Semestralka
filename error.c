#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error_arg(void){
    printf("\n");
    printf("Usage:\n\tspamid.exe <spam pattern> <spam count> <ham pattern> <ham count> <test pattern> <test count> <output file>\n\n");
    printf("Example:\n\tspamid.exe spam 10 ham 20 test 50 result.txt\n");
    exit(1);
}

void error_fopen(char *path){
    printf("\n");
    printf("ERROR: Cannot open file.\n");
    printf("File path: %s\n", path);
    exit(1);
}
