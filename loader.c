#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"

int load_file(hash_table *table, const char *spam_pattern, const size_t *spam_count, int flag){
    size_t i;

    FILE *file = NULL;
    char path[STRING_LENGHT] = {0};
    char content[STRING_LENGHT] = {0};

    /* Nacteni vsech souboru */
    for(i = 1; i <= (*spam_count); i++){
        /* Sestavení cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, spam_pattern, (unsigned long)i, FILE_EXTENSION);

        /* Otevre soubor */
        file = fopen(path, "r");
        if (!file) {
            printf("\nCesta:\t%s", path);
            printf("\nNemohu otevrit soubor, ukoncuji program.\n");
            return EXIT_FAILURE;
        }

        /* Vypise obsah souboru */
        while (fscanf(file, "%s", content) == 1) {
            table_insert(table, content, flag);
        }

        /* Uzavre soubor */
        fclose(file);
    }
    return EXIT_SUCCESS;
}

int output_file(hash_table *table, const char *out_file){
    FILE *file_out = NULL;
}
