#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "error.h"

void load_files(hash_table *table, const char *spam_pattern, const size_t *spam_count, int flag){
    size_t i;

    FILE *file = NULL;
    char path[STRING_LENGHT] = {0};
    char content[STRING_LENGHT] = {0};

    /* Nacteni vsech souboru */
    for(i = 1; i <= (*spam_count); i++){
        /* Sestaveni cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, spam_pattern, (unsigned long)i, FILE_EXTENSION);

        /* Otevre soubor */
        file = fopen(path, "r");
        if (!file) {
            table_free(&table);
            error_fopen(path);
        }

        /* Vypise obsah souboru */
        while (fscanf(file, "%s", content) == 1) {
            table_insert(table, content, flag);
        }

        /* Uzavre soubor */
        fclose(file);
    }
}

void output_file(hash_table *table, const char *out_file){
    FILE *file_out = NULL;
}
