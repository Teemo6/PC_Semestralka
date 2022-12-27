#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "hash_table.h"

/* Pocet argumentu */
#define ARG_COUNT 8

void help(void){
    printf("Usage:\n\tspamid.exe <spam> <spam-cnt> <ham> <ham-cnt> <test> <test-cnt> <out-file>\n\n");
    printf("Example:\n\tspamid.exe spam 10 ham 20 test 50 result.txt\n\n");
}

void handle_input(int argc, char *argv[]){
    long spam_cnt, ham_cnt, test_cnt;

    /* Kontrola poctu argumentu */
    if(argc < ARG_COUNT){
        help();
        exit(1);
    }

    /* Kontrola intervalu cisel <1; N> */
    spam_cnt = strtol(argv[2], NULL, 0);
    ham_cnt = strtol(argv[4], NULL, 0);
    test_cnt = strtol(argv[6], NULL, 0);

    if(!spam_cnt || !ham_cnt || !test_cnt){
        help();
        exit(1);
    }
}

int main(int argc, char *argv[]){
    size_t spam_cnt, ham_cnt;
    size_t i;
    hash_table *table_spam;

    FILE *file_in = NULL;
    FILE *file_out = NULL;
    char path[STRING_LENGHT] = {0};
    char content[FILE_CHAR_COUNT] = {0};

    /* Hash table experimenty */
    table_spam = table_create();

    /* Konec experimentu */

    /* Kontrola argumentu */
    handle_input(argc, argv);

    spam_cnt = strtol(argv[2], NULL, 0);
    ham_cnt = strtol(argv[4], NULL, 0);

    /* Vystupni soubor */
    file_out = fopen(argv[7], "w");

    /* Nacteni spamu */
    for(i = 1; i <= spam_cnt; i++){
        /* Sestavení cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, argv[1], (unsigned long)i, FILE_EXTENSION);

        /* Otevre soubor */
        file_in = fopen(path, "r");
        if (!file_in) {
            printf("\nCesta:\t%s", path);
            printf("\nNemohu otevrit soubor, ukoncuji program.\n");
            return EXIT_FAILURE;
        }

        fprintf(file_out, "\n\n%ld", (unsigned long)i);

        /* Vypise obsah souboru */
        while (fgets(content, FILE_CHAR_COUNT, file_in)) {
            char *token = strtok(content, " ");
            while(token){
                table_insert(table_spam, token, token);
                fprintf(file_out, "%s ", token);
                token = strtok(NULL, " ");
            }
        }

        /* Uzavre soubor */
        fclose(file_in);
    }

    /* Nacteni hamu */
    for(i = 1; i <= ham_cnt; i++){
        /* Sestaveni cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, argv[3], (unsigned long)i, FILE_EXTENSION);

        /* Otevre soubor */
        file_in = fopen(path, "r");
        if (!file_in) {
            printf("\nCesta:\t%s", path);
            printf("\nNemohu otevrit soubor, ukoncuji program.\n");
            return EXIT_FAILURE;
        }

        fprintf(file_out, "\n\n%ld", (unsigned long)i);

        /* Vypise obsah souboru */
        while (fgets(content, FILE_CHAR_COUNT, file_in)) {
            char *token = strtok(content, " ");
            while(token){
                table_insert(table_spam, token, token);
                fprintf(file_out, "%s ", token);
                token = strtok(NULL, " ");
            }
        }

        /* Uzavre soubor */
        fclose(file_in);
    }
    /* Uzavre vystupni soubor */
    fclose(file_out);

    table_print(table_spam);
    table_free(&table_spam);

    entry *e1, *e2;

    e1 = entry_create("asdasdasd", "a");
    e2 = entry_create("b", "b");

    entry_add(e1, "asdasdasd", "cau");
    entry_add(e1, "asdasdad", "ahoj");
    entry_add(e1, "asdasdasd", "xd");

    entry_print(e1);

    entry_free(&e1);
    entry_free(&e2);



    return EXIT_SUCCESS;
}
