#include <stdio.h>
#include <string.h>
#include <math.h>

#include "loader.h"
#include "error.h"

void load_train(hash_table *table, const char *train_pattern, const size_t *train_count, int flag){
    size_t i;

    FILE *file = NULL;
    char path[STRING_LENGHT] = {0};
    char content[STRING_LENGHT] = {0};

    /* Nacteni vsech souboru */
    for(i = 1; i <= (*train_count); i++){
        /* Sestaveni cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, train_pattern, (unsigned long)i, FILE_EXTENSION);

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

void load_test(hash_table *table, const char *out_file, const char *test_pattern, const size_t *test_count) {
    size_t i;
    entry *e;
    double spam_prob, ham_prob;
    char result[STRING_LENGHT] = {0};

    FILE *file = NULL;
    char path[STRING_LENGHT] = {0};
    char content[STRING_LENGHT] = {0};

    FILE *file_out = NULL;
    file_out = fopen(out_file, "w");

    /* Nacteni vsech souboru */
    for(i = 1; i <= (*test_count); i++){
        /* Sestaveni cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, test_pattern, (unsigned long)i, FILE_EXTENSION);

        /* Otevre soubor */
        file = fopen(path, "r");
        if (!file) {
            table_free(&table);
            error_fopen(path);
        }
        spam_prob = 0;
        ham_prob = 0;

        /* Vypise obsah souboru */
        while (fscanf(file, "%s", content) == 1) {
            e = table_find(table, content);

            if(!e) continue;

            if(e->spam_prob != 0){
                spam_prob += log10(e->spam_prob);
            }

            if(e->ham_prob != 0){
                ham_prob += log10(e->ham_prob);
            }
        }

        if(spam_prob > ham_prob){
            strcpy(result, "S");
        } else {
            strcpy(result, "H");
        }

        sprintf(path, "%s%ld%s", test_pattern, (unsigned long)i, FILE_EXTENSION);
        fprintf(file_out, "%s\t%s\n", path, result);

        /* Uzavre testovy soubor */
        fclose(file);
    }
    /* Uzavre vystupni soubor */
    fclose(file_out);
}
