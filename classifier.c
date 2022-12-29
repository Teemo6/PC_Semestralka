#include <stdio.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "error.h"
#include "classifier.h"

void classifier_train(hash_table *table, const char *train_pattern, const size_t *train_count, int flag){
    size_t i;
    char path[STRING_LENGHT], content[STRING_LENGHT];
    FILE *file;

    /* Nacteni vsech souboru */
    for(i = 1; i <= (*train_count); i++){
        /* Sestaveni cesty k souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, train_pattern, (unsigned long)i, FILE_EXTENSION);

        /* Otevre soubor */
        file = fopen(path, "r");

        /* Chyba pri otevirani */
        if(!file) {
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

void compute_probability(hash_table *table){
    size_t i;
    entry *e_last;

    if(!table){
        error_probabilty();
    }

    /* Projdi vsechny polozky tabulky */
    for(i = 0; i < table->size; i++){
        if(table->entries[i]){
            /* Projdi vsechny polozky seznamu */
            e_last = table->entries[i];
            while(e_last->next){
                e_last->prob_entry_spam = ((double)e_last->count_entry_spam + 1) / (double)table->count_spam;
                e_last->prob_entry_ham = ((double)e_last->count_entry_ham + 1) / (double)table->count_ham;
                e_last = e_last->next;
            }
            e_last->prob_entry_spam = ((double)e_last->count_entry_spam + 1) / (double)table->count_spam;
            e_last->prob_entry_ham = ((double)e_last->count_entry_ham + 1) / (double)table->count_ham;
        }
    }
}

void classifier_test(hash_table *table, const char *test_pattern, const size_t *test_count, const char *out_file) {
    size_t i;
    entry *e;
    double spam, ham;
    char result[STRING_LENGHT], path[STRING_LENGHT], content[STRING_LENGHT];
    FILE *file_in, *file_out;
    
    /* Otevre vystupni soubor */
    file_out = fopen(out_file, "w");

    /* Nacteni vsech vstupnich souboru */
    for(i = 1; i <= (*test_count); i++){
        /* Sestaveni cesty ke vstupnimu souboru */
        sprintf(path, "%s%s%ld%s", FILE_PATH, test_pattern, (unsigned long)i, FILE_EXTENSION);

        /* Otevre vstupni soubor */
        file_in = fopen(path, "r");
        if(!file_in) {
            table_free(&table);
            error_fopen(path);
        }

        /* Vynuluje predchozi klasifikaci */
        spam = 0;
        ham = 0;

        /* Klasifikuje slova */
        while (fscanf(file_in, "%s", content) == 1) {
            e = table_find(table, content);

            /* Polozka se v tabulce nenachazi */
            if(!e){
                continue;
            }

            /* Polozka ma spamovou pravdepodobnost */
            if(e->prob_entry_spam != 0){
                spam += log10(e->prob_entry_spam);
            }

            /* Polozka ma hamovou pravdepodobnost */
            if(e->prob_entry_ham != 0){
                ham += log10(e->prob_entry_ham);
            }
        }

        /* Klasifikuje soubor */
        if(spam > ham){
            strcpy(result, "S");
        } else {
            strcpy(result, "H");
        }

        /* Zapis do vystupniho souboru */
        sprintf(path, "%s%ld%s", test_pattern, (unsigned long)i, FILE_EXTENSION);
        fprintf(file_out, "%s\t%s\n", path, result);

        /* Uzavre vstupni soubor */
        fclose(file_in);
    }
    /* Uzavre vystupni soubor */
    fclose(file_out);
}
