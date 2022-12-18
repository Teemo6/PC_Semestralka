#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

void help(){
    printf("Usage:\n   spamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n\n");
    printf("Example:\n   spamid.exe spam 10 ham 20 test 50 result.txt\n\n");
}

void handle_input(int argc, char *argv[]){
    long spam_cnt, ham_cnt, test_cnt;

    /* Kontrola počtu argumentů */
    if(argc < 8){
        help();
        exit(1);
    }

    /* Kontrola intervalu čísel <1; N> */
    spam_cnt = strtol(argv[2], NULL, 0);
    ham_cnt = strtol(argv[4], NULL, 0);
    test_cnt = strtol(argv[6], NULL, 0);

    if(!spam_cnt || !ham_cnt || !test_cnt){
        help();
        exit(1);
    }
}

int main(int argc, char *argv[]){
    int spam_cnt, ham_cnt, test_cnt;
    int i;
    char spam_str[MAX_WORD_SIZE] = {0};
    char ham_str[MAX_WORD_SIZE] = {0};
    char test_str[MAX_WORD_SIZE] = {0};

    FILE *file_in = NULL;
    FILE *file_out = NULL;
    char fileName[MAX_WORD_SIZE] = {0};
    char word[MAX_WORD_SIZE];

    /* Kontrola argumentů */
    handle_input(argc, argv);

    spam_cnt = strtol(argv[2], NULL, 0);
    ham_cnt = strtol(argv[4], NULL, 0);
    test_cnt = strtol(argv[6], NULL, 0);


    /* Výstupní soubor */

    file_out = fopen(argv[7], "w");


    for(i = 1; i <= spam_cnt; i++){
        sprintf(spam_str, "%d", i);

        /* Sestavení cesty k souboru */
        strcpy(fileName, FILE_PATH);
        strcat(fileName, argv[1]);
        strcat(fileName, spam_str);
        strcat(fileName, FILE_EXTENSION);

        /* Otevře soubor */
        file_in = fopen(fileName, "r");
        if (!file_in) {
            printf("\nNemohu otevrit soubor, ukoncuji program.\n");
            return EXIT_FAILURE;
        }

        /* Vypíše obsah souboru */
        while (fgets(word, MAX_WORD_SIZE, file_in)) {
            fprintf(file_out, "\n%s", word);
        }

        /* Uzavře soubor */
        fclose(file_in);
    }

    for(i = 1; i <= ham_cnt; i++){
        sprintf(ham_str, "%d", i);

        /* Sestavení cesty k souboru */
        strcpy(fileName, FILE_PATH);
        strcat(fileName, argv[3]);
        strcat(fileName, ham_str);
        strcat(fileName, FILE_EXTENSION);

        /* Otevře soubor */
        file_in = fopen(fileName, "r");
        if (!file_in) {
            printf("\nNemohu otevrit soubor, ukoncuji program.\n");
            return EXIT_FAILURE;
        }

        /* Vypíše obsah souboru */
        while (fgets(word, MAX_WORD_SIZE, file_in)) {
            fprintf(file_out, "\n%s", word);
        }

        /* Uzavře soubor */
        fclose(file_in);
    }
/*
    for(i = 1; i <= test_cnt; i++){
        sprintf(test_str, "%d", i);

        // Sestavení cesty k souboru
        strcpy(fileName, FILE_PATH);
        strcat(fileName, argv[5]);
        strcat(fileName, test_str);
        strcat(fileName, FILE_EXTENSION);

        // Otevře soubor
        file_in = fopen(fileName, "r");
        if (!file_in) {
            printf("\nNemohu otevrit soubor, ukoncuji program.\n");
            return EXIT_FAILURE;
        }

        // Vypíše obsah souboru
        while (fgets(word, MAX_WORD_SIZE, file_in)) {
            fprintf(file_out, "\n%s", word);
        }

        // Uzavře soubor
        fclose(file_in);
    }
*/
    /* Uzavře výstupní soubor */
    fclose(file_out);

    return EXIT_SUCCESS;
}
