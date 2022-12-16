#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int main(){
    FILE *file = NULL;
    char fileName[MAX_WORD_SIZE] = {0};
    char word[MAX_WORD_SIZE];

    char *tempStr = "ham";
    int tempInt = 1;

    strcpy(fileName, FILE_PATH);
    strcat(fileName, tempStr);
    itoa(tempInt, fileName + strlen(fileName), 10);
    strcat(fileName, FILE_EXTENSION);

    /* Otevře soubor */
    file = fopen(fileName, "r");
    if (!file) {
        printf("\nNemohu otevrit soubor, ukoncuji program.\n");
        return EXIT_FAILURE;
    }

    /* Vypíše obsah souboru */
    while (fgets(word, MAX_WORD_SIZE, file)) {
        printf("%s", word);
    }

    /* Uzavře soubor */
    fclose(file);
    return EXIT_SUCCESS;
}